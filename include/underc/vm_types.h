#ifndef UNDERC_VM_TYPES_H
#define UNDERC_VM_TYPES_H

#include <stdint.h>
#include <stddef.h>

// The VM word follows the host ABI: a 32-bit host runs a 32-bit VM and a
// 64-bit host a 64-bit one.  The build system states this explicitly, but the
// installed headers are also included by consumer projects that never see the
// interpreter's own compile definitions, so derive the same answer here rather
// than making every consumer restate it.
#ifndef UNDERC_VM_BITS
# if defined(__SIZEOF_POINTER__)
#  define UNDERC_VM_BITS (__SIZEOF_POINTER__ * 8)
# elif defined(_WIN64) || defined(__LP64__) || defined(_LP64)
#  define UNDERC_VM_BITS 64
# else
#  define UNDERC_VM_BITS 32
# endif
#endif

#if UNDERC_VM_BITS == 16
typedef int16_t VMWord;
typedef uint16_t VMUWord;
#elif UNDERC_VM_BITS == 32
typedef int32_t VMWord;
typedef uint32_t VMUWord;
#elif UNDERC_VM_BITS == 64
typedef int64_t VMWord;
typedef uint64_t VMUWord;
#else
# error "UNDERC_VM_BITS must be 16, 32, or 64"
#endif

// VMWord is the execution/instruction slot and must be able to transport a
// target pointer.  Object integer widths are a separate ABI choice.  The
// default follows the compiler host ABI; the opt-out retains the historical
// configurable-VM experiment where all ordinary integer objects are VM-wide.
#ifdef UCL_DISABLE_NATIVE_ABI
typedef VMWord VMInt;
typedef VMUWord VMUInt;
typedef VMWord VMLong;
typedef VMUWord VMULong;
#else
typedef int VMInt;
typedef unsigned int VMUInt;
typedef long VMLong;
typedef unsigned long VMULong;
#endif

typedef size_t VMByteSize;
typedef ptrdiff_t VMByteOffset;
typedef size_t VMSlotCount;
typedef ptrdiff_t VMFrameSlots;

// Conversions are centralized so every pointer-bearing VM path uses the
// selected VM representation instead of an accidental host int or long.
inline VMWord vm_from_ptr(const void *ptr)
{ return static_cast<VMWord>(reinterpret_cast<uintptr_t>(ptr)); }

inline void *vm_to_ptr(VMWord value)
{ return reinterpret_cast<void *>(static_cast<uintptr_t>(static_cast<VMUWord>(value))); }

inline const void *vm_to_const_ptr(VMWord value)
{ return reinterpret_cast<const void *>(static_cast<uintptr_t>(static_cast<VMUWord>(value))); }

// constexpr so these can size fixed arrays - MSVC, unlike GCC/Clang, has no
// variable-length-array extension.
constexpr inline int vm_word_count(int byte_count)
{ return (byte_count + sizeof(VMWord) - 1) / sizeof(VMWord); }

constexpr inline VMSlotCount vm_slot_count(VMByteSize byte_count)
{ return (byte_count + sizeof(VMWord) - 1) / sizeof(VMWord); }

inline bool vm_checked_add(VMByteSize left, VMByteSize right, VMByteSize& result)
{
  if (right > static_cast<VMByteSize>(-1) - left) return false;
  result = left + right;
  return true;
}

inline VMByteSize vm_align_up(VMByteSize value, VMByteSize alignment)
{
  if (alignment <= 1) return value;
  VMByteSize remainder = value % alignment;
  return remainder ? value + alignment - remainder : value;
}

inline bool vm_can_transport_host_pointers()
{ return sizeof(VMWord) >= sizeof(void *); }

// The host ABI decides how a double is aligned inside an aggregate, and that
// is not always alignof(double): 32-bit MSVC aligns it to 8, while the i386
// System V ABI aligns it to 4 even though the compiler reports 8 as its
// preferred alignment.  Measure the real struct rule rather than guess it.
struct VMDoubleAlignmentProbe { char lead; double member; };

inline int vm_host_aggregate_double_alignment()
{ return static_cast<int>(offsetof(VMDoubleAlignmentProbe,member)); }

inline int vm_default_object_alignment()
{
#ifdef UCL_DISABLE_NATIVE_ABI
  return sizeof(VMWord);
#else
  // On a 32-bit host a pointer is narrower than the widest aggregate member
  // alignment, so capping the pack alignment at sizeof(void *) would lay out
  // and size every double-bearing struct differently from the host compiler.
  int pointer_alignment = static_cast<int>(sizeof(void *));
  int double_alignment = vm_host_aggregate_double_alignment();
  return double_alignment > pointer_alignment ? double_alignment : pointer_alignment;
#endif
}

#endif
