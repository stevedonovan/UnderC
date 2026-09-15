/* directcall.cpp
 * Direct access to native code, exported 'builtin' functions
 * UnderC C++ interpreter
 * Steve Donovan, 2001
 * This is GPL'd software, and the usual disclaimers apply.
 * See LICENCE
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <new>
#include <vector>
#ifdef _WIN32
# include <io.h>
#else
# include <unistd.h>
# ifdef UCL_SYSV_X86_64
#  include <sys/mman.h>
# endif
#endif
#include "common.h"
#include "opcodes.h"
#include "directcall.h"
#include "mangle.h"
#include "hard_except.h"
#include "os.h"
#include "ex_vfscanf.h"
#include "main.h"
#include <map>
#ifdef __GNUC__
# include <cxxabi.h>
#endif
#ifdef UCL_LIBFFI
#include <ffi.h>
#include <vector>
#include "function.h"
#include "signature.h"
# ifdef UCL_SYSV_X86_64
// The assembly object contains both legacy entry points.  Sanitizer linkers
// may retain the whole object even though libffi mode only needs neither.
extern "C" void underc_sysv_callback_invoke() {}
# endif
#endif

#ifdef _WCON
#include "uc_graphics.h"
int exec(char *, int, bool);  // in twl.cpp
#define fprintf wcon_fprintf
#define fgets wcon_fgets
#else
#define fprintf con_fprintf
#define fgets con_fgets
#define wcon_fscanf con_fscanf
#endif

void* _copy_body(char* buff); // debug

// from lexer.cpp!
void uc_hash_cmd(char *s);
void uc_macro_subst(const char *str, char *buff, int sz);

// *add 1.2.4 uc_exec(), uc_result() from main.cpp
int _uc_exec(char* s, void* cntxt, char* filename, int line);
void _uc_result(int ret, char *output, int sz, char* filename, int* line);

int _uc_exec_1(char* s) { return _uc_exec(s,0,0,0); }

void __mangle(); //*DEBUG*

// Keep the interpreted API portable even though Microsoft's CRT prefixes the
// process-pipe functions with underscores.
static FILE *uc_popen(const char *command, const char *mode)
{
#ifdef _WIN32
 return _popen(command,mode);
#else
 return popen(command,mode);
#endif
}

static int uc_pclose(FILE *stream)
{
#ifdef _WIN32
 return _pclose(stream);
#else
 return pclose(stream);
#endif
}

// The remaining character-output functions have to come from the same C
// runtime as the rest of the stdio builtins: the FILE handles handed out by
// _get_std_stream() belong to the host runtime and cannot be passed to a
// separately imported C library.  putc() is a macro in C, so it is wrapped.
static int uc_fputs(const char *s, FILE *stream)  { return fputs(s,stream); }
static int uc_putc(int ch, FILE *stream)          { return fputc(ch,stream); }
static int uc_putchar(int ch)                     { return putchar(ch); }

typedef void (*UCExitFunction)();
typedef std::vector<UCExitFunction> UCExitFunctionList;
static UCExitFunctionList uc_exit_functions;
static bool uc_exit_dispatch_registered = false;

static void uc_run_exit_functions()
{
 while (!uc_exit_functions.empty()) {
   UCExitFunction fn = uc_exit_functions.back();
   uc_exit_functions.pop_back();
   if (fn) fn();
 }
}

static int uc_atexit(UCExitFunction fn)
{
 if (!fn) return -1;
 if (!uc_exit_dispatch_registered) {
   if (::atexit(uc_run_exit_functions) != 0) return -1;
   uc_exit_dispatch_registered = true;
 }
 uc_exit_functions.push_back(fn);
 return 0;
}

static char *uc_gcvt(double value, int digits, char *buffer)
{
 if (!buffer) return NULL;
 sprintf(buffer,"%.*g",digits,value);
 return buffer;
}

static int uc_access(const char *file, int mode)
{
#ifdef _WIN32
 return ::_access(file,mode);
#else
 return ::access(file,mode);
#endif
}

// from tokens.cpp; exported as uc_include_path()
int _uc_include_path(const char *fname, char* buff, int sz);

extern void* gObjectReturnPtr;

typedef int (* CALL_FUN)(int, int);
#define STDCALL __stdcall
typedef int (*CALLFN) (void);

// The MSVC branch below is written in 32-bit (_M_IX86) inline assembler, which
// the x64 compiler rejects outright.  Restrict it to 32-bit MSVC; every other
// configuration (MSVC x64 included) uses the portable fallback further down or
// the libffi / SysV bridges.
#if !defined(__GNUC__) && defined(_M_IX86)

static void legacy_callfn(CALLFN fn, VMWord args[], int argc, void *optr, int flags, void *buff)
{
   int sz = sizeof(int)*argc;
  __asm {
    mov ecx, argc
    mov ebx, args
    // push the arguments onto the stack, backwards
a_loop:
    cmp ecx,0
    jz a_out
    mov eax, [ebx + 4*ecx]
    push eax
    dec ecx
    jmp a_loop

a_out:
    mov ecx,optr // thiscall calling convention (MS only)
    call fn
    // Cleanup stack ptr if this was a cdecl call
    mov ecx, flags
    test ecx,DC_CDECL
    jz  a_over
    add  esp,sz
a_over:
    test ecx,DC_RET_OBJ
    jz a_again
// these cases are peculiar to GCC
    cmp ecx,DC_RET_VAL
    jl  a_skip
    mov ebx, gObjectReturnPtr
    mov [ebx],eax
    mov [ebx+4],edx
    jmp a_finish
a_skip:
	sub  esp,4
a_again:
    mov ebx,buff
    test ecx,DC_QWORD
    jnz  a_dbl
    mov  dword ptr[ebx],eax
    jmp a_finish
a_dbl:
    fstp qword ptr[ebx]
a_finish:
  }
}


// 'bare' inline functions w/ no usual prolog/epilog!
#define PROC(name) __declspec(naked) void name() { __asm {
#define ENDP }}

static ArgBlock *pArgs;  // only used for type info below!

// *fix 1.2.6 don't use edi! ecx is always safe.
PROC(copy_array)
// edi contains ptr to ArgBlock, eax contains no of args
  pop [ecx]pArgs.ret_addr   // return addr!
  mov [ecx]pArgs.esi_ptr, esi
  mov [ecx]pArgs.no, eax
  lea esi,[ecx]pArgs.values
 l1:
  pop edx
  dec eax
  mov [esi + 4*eax],edx
  cmp eax,0
  jnz l1
  mov esi,[ecx]pArgs.esi_ptr
  push [ecx]pArgs.ret_addr
  ret
ENDP

#elif defined(UCL_SYSV_X86_64)

extern "C" void underc_sysv_call(void *function, const uint64_t integer_args[6],
                                  const uint64_t sse_args[8],
                                  const uint64_t *stack_args, size_t stack_count,
                                  unsigned int sse_count, uint64_t *integer_result,
                                  uint64_t *sse_result);

static bool sysv_sse_type(const Type& type)
{
  return !type.is_ref_or_ptr() && (type.is_single() || type.is_double());
}

static uint64_t sysv_argument_bits(const Type& type, VMWord *raw, int& slots)
{
  uint64_t bits = 0;
  slots = 1;
  if (type.is_double()) {
    memcpy(&bits,raw,sizeof(double));
    slots = vm_word_count(sizeof(double));
  } else if (type.is_single()) {
    memcpy(&bits,raw,sizeof(float));
  } else {
    bits = static_cast<uint64_t>(raw[0]);
  }
  return bits;
}

static void legacy_callfn(CALLFN fn, VMWord args[], int argc, void *optr, int,
                          void *buff, Function *function)
{
  if (!function) throw Exception("native call has no signature metadata");
  if (function->return_type().is_object())
    throw Exception("native objects by value require libffi; use a pointer or reference");

  uint64_t integer_args[6] = {0,0,0,0,0,0};
  uint64_t sse_args[8] = {0,0,0,0,0,0,0,0};
  std::vector<uint64_t> stack_args;
  unsigned int integer_count = 0;
  unsigned int sse_count = 0;
  if (optr) integer_args[integer_count++] = reinterpret_cast<uintptr_t>(optr);

  VMWord *raw = args + 1;
  int consumed = 0;
  Signature::iterator type = function->signature()->begin();
  for (; type != function->signature()->end(); ++type) {
    if (type->is_object())
      throw Exception("native objects by value require libffi; use a pointer or reference");
    int slots = 1;
    uint64_t bits = sysv_argument_bits(*type,raw + consumed,slots);
    consumed += slots;
    if (sysv_sse_type(*type) && sse_count < 8) sse_args[sse_count++] = bits;
    else if (!sysv_sse_type(*type) && integer_count < 6) integer_args[integer_count++] = bits;
    else stack_args.push_back(bits);
  }
  while (consumed < argc) {
    uint64_t bits = static_cast<uint64_t>(raw[consumed++]);
    if (integer_count < 6) integer_args[integer_count++] = bits;
    else stack_args.push_back(bits);
  }

  uint64_t integer_result = 0, sse_result = 0;
  underc_sysv_call(reinterpret_cast<void *>(fn),integer_args,sse_args,
                   stack_args.empty() ? NULL : &stack_args[0],stack_args.size(),
                   sse_count,&integer_result,&sse_result);
  Type result_type = function->return_type();
  if (result_type.is_double()) memcpy(buff,&sse_result,sizeof(double));
  else if (result_type.is_single()) memcpy(buff,&sse_result,sizeof(float));
  else *reinterpret_cast<VMWord *>(buff) = static_cast<VMWord>(integer_result);
}

#else

static void legacy_callfn(CALLFN fn, VMWord args[], int argc, void *optr, int flags, void *buff)
{
  VMWord a[6] = {0, 0, 0, 0, 0, 0};
  for (int i = 0; i < argc && i < 6; ++i) a[i] = args[i + 1];
  if (flags & DC_QWORD) {
    double *d = reinterpret_cast<double *>(a);
    double result = argc == 0 ? (reinterpret_cast<double (*)()>(fn))()
      : argc == 1 ? (reinterpret_cast<double (*)(double)>(fn))(d[0])
      : (reinterpret_cast<double (*)(double, double)>(fn))(d[0], d[1]);
    *reinterpret_cast<double *>(buff) = result;
    return;
  }
  VMWord result = 0;
  switch (argc + (optr ? 1 : 0)) {
    case 0: result = (reinterpret_cast<VMWord (*)()>(fn))(); break;
    case 1: result = optr ? (reinterpret_cast<VMWord (*)(void *)>(fn))(optr) : (reinterpret_cast<VMWord (*)(VMWord)>(fn))(a[0]); break;
    case 2: result = optr ? (reinterpret_cast<VMWord (*)(void *, VMWord)>(fn))(optr, a[0]) : (reinterpret_cast<VMWord (*)(VMWord, VMWord)>(fn))(a[0], a[1]); break;
    case 3: result = optr ? (reinterpret_cast<VMWord (*)(void *, VMWord, VMWord)>(fn))(optr, a[0], a[1]) : (reinterpret_cast<VMWord (*)(VMWord, VMWord, VMWord)>(fn))(a[0], a[1], a[2]); break;
    case 4: result = (reinterpret_cast<VMWord (*)(VMWord, VMWord, VMWord, VMWord)>(fn))(a[0], a[1], a[2], a[3]); break;
    case 5: result = (reinterpret_cast<VMWord (*)(VMWord, VMWord, VMWord, VMWord, VMWord)>(fn))(a[0], a[1], a[2], a[3], a[4]); break;
    case 6: result = (reinterpret_cast<VMWord (*)(VMWord, VMWord, VMWord, VMWord, VMWord, VMWord)>(fn))(a[0], a[1], a[2], a[3], a[4], a[5]); break;
    default: throw Exception("native calls with more than six arguments are unsupported");
  }
  *reinterpret_cast<VMWord *>(buff) = result;
}
// *fix 1.2.9 sorted out a nasty in the above code! We were
// testing against EDX  and trying to move stuff from [ECX]

// I know this looks like portable code, but it isn't!
void copy_array(int sz, ArgBlock *xargs)
{
  int k,i;
  VMWord *args = xargs->values;
  VMWord *p = reinterpret_cast<VMWord *>(&xargs) + 1;
  xargs->no = sz;
  // *fix 1.2.0L Copy these args backwards!
  for(k = sz-1,i=0; k >= 0; k--,i++)
    args[i] = p[k];
}

#endif

#ifdef UCL_LIBFFI
namespace {

union FFIValue {
  VMWord word;
  void *pointer;
  signed char schar_value;
  unsigned char uchar_value;
  short short_value;
  unsigned short ushort_value;
  int int_value;
  unsigned int uint_value;
  long long_value;
  unsigned long ulong_value;
  float float_value;
  double double_value;
};

struct FFIAggregateType {
  ffi_type type;
  std::vector<ffi_type *> elements;
  FFIAggregateType()
  {
    memset(&type,0,sizeof(type));
    type.type = FFI_TYPE_STRUCT;
  }
};

typedef std::map<Class *,FFIAggregateType *> FFIAggregateMap;
FFIAggregateMap ffi_aggregate_types;

ffi_type *ffi_type_for(const Type& type);

ffi_type *ffi_aggregate_type_for(const Type& type)
{
  Class *aggregate_class = type.as_class();
  FFIAggregateMap::iterator found = ffi_aggregate_types.find(aggregate_class);
  if (found != ffi_aggregate_types.end()) return &found->second->type;
  if (!aggregate_class->simple_struct() || aggregate_class->is_union())
    throw Exception("only plain non-union aggregates may be passed by value");

  FFIAggregateType *aggregate = new FFIAggregateType;
  ffi_aggregate_types[aggregate_class] = aggregate;
  EntryList fields;
  aggregate_class->list_entries(fields,FIELDS | NON_STATIC | DO_PARENT);
  for (EntryList::iterator field = fields.begin(); field != fields.end(); ++field) {
    if ((*field)->is_bitfield())
      throw Exception("bit-field aggregates cannot be passed by value");
    Type field_type = (*field)->type;
    int repetitions = 1;
    if (field_type.is_array()) {
      repetitions = (*field)->size;
      field_type.strip_array();
      field_type.decr_pointer();
    }
    for (int i = 0; i < repetitions; ++i)
      aggregate->elements.push_back(ffi_type_for(field_type));
  }
  aggregate->elements.push_back(NULL);
  aggregate->type.elements = &aggregate->elements[0];
  return &aggregate->type;
}

ffi_type *ffi_type_for(const Type& type)
{
  if (type.is_ref_or_ptr() || type.is_function()) return &ffi_type_pointer;
  if (type.is_object()) return ffi_aggregate_type_for(type);
  if (type.is_void()) return &ffi_type_void;
  if (type.is_double()) return &ffi_type_double;
  if (type.is_single()) return &ffi_type_float;
  if (type.is_bool() || type.is_char())
    return type.is_unsigned() ? &ffi_type_uchar : &ffi_type_schar;
  if (type.is_short())
    return type.is_unsigned() ? &ffi_type_ushort : &ffi_type_sshort;
  if (type.is_long())
    return type.is_unsigned() ? &ffi_type_ulong : &ffi_type_slong;
  return type.is_unsigned() ? &ffi_type_uint : &ffi_type_sint;
}

void set_ffi_value(FFIValue& value, const Type& type, VMWord *raw, int& slots)
{
  slots = 1;
  if (type.is_ref_or_ptr() || type.is_function())
    value.pointer = vm_to_ptr(raw[0]);
  else if (type.is_double()) {
    value.double_value = *reinterpret_cast<double *>(raw);
    slots = vm_word_count(sizeof(double));
  } else if (type.is_single())
    value.float_value = *reinterpret_cast<float *>(raw);
  else if (type.is_bool() || type.is_char()) {
    if (type.is_unsigned()) value.uchar_value = static_cast<unsigned char>(raw[0]);
    else value.schar_value = static_cast<signed char>(raw[0]);
  } else if (type.is_short()) {
    if (type.is_unsigned()) value.ushort_value = static_cast<unsigned short>(raw[0]);
    else value.short_value = static_cast<short>(raw[0]);
  } else if (type.is_long()) {
    if (type.is_unsigned()) value.ulong_value = static_cast<unsigned long>(raw[0]);
    else value.long_value = static_cast<long>(raw[0]);
  } else if (type.is_unsigned()) value.uint_value = static_cast<unsigned int>(raw[0]);
  else value.int_value = static_cast<int>(raw[0]);
}

void store_ffi_result(const FFIValue& result, const Type& type, void *buff)
{
  VMWord *word = reinterpret_cast<VMWord *>(buff);
  *word = 0;
  if (type.is_ref_or_ptr() || type.is_function()) *word = vm_from_ptr(result.pointer);
  else if (type.is_void()) return;
  else if (type.is_double()) *reinterpret_cast<double *>(buff) = result.double_value;
  else if (type.is_single()) *reinterpret_cast<float *>(buff) = result.float_value;
  else if (type.is_bool() || type.is_char())
    *word = type.is_unsigned() ? result.uchar_value : result.schar_value;
  else if (type.is_short())
    *word = type.is_unsigned() ? result.ushort_value : result.short_value;
  else if (type.is_long())
    *word = type.is_unsigned() ? static_cast<VMWord>(result.ulong_value)
                               : static_cast<VMWord>(result.long_value);
  else *word = type.is_unsigned() ? result.uint_value : result.int_value;
}

struct CallbackDescriptor {
  Function *function;
  ffi_cif cif;
  ffi_closure *closure;
  void *entry;
  std::vector<ffi_type *> argument_types;
  CallbackDescriptor() : function(NULL), closure(NULL), entry(NULL) {}
};

typedef std::list<CallbackDescriptor *> CallbackList;
CallbackList callback_list;

void append_callback_value(std::vector<VMWord>& words, const Type& type, void *value)
{
  if (type.is_ref_or_ptr() || type.is_function())
    words.push_back(vm_from_ptr(*reinterpret_cast<void **>(value)));
  else if (type.is_double()) {
    VMWord slots[vm_word_count(sizeof(double))];
    memset(slots,0,sizeof(slots));
    memcpy(slots,value,sizeof(double));
    for (int i = 0; i < vm_word_count(sizeof(double)); ++i) words.push_back(slots[i]);
  } else if (type.is_single()) {
    VMWord word = 0;
    memcpy(&word,value,sizeof(float));
    words.push_back(word);
  } else if (type.is_bool() || type.is_char())
    words.push_back(type.is_unsigned() ? *reinterpret_cast<unsigned char *>(value)
                                       : *reinterpret_cast<signed char *>(value));
  else if (type.is_short())
    words.push_back(type.is_unsigned() ? *reinterpret_cast<unsigned short *>(value)
                                       : *reinterpret_cast<short *>(value));
  else if (type.is_long())
    words.push_back(type.is_unsigned() ? static_cast<VMWord>(*reinterpret_cast<unsigned long *>(value))
                                       : static_cast<VMWord>(*reinterpret_cast<long *>(value)));
  else
    words.push_back(type.is_unsigned() ? *reinterpret_cast<unsigned int *>(value)
                                       : *reinterpret_cast<int *>(value));
}

void ffi_callback(ffi_cif *, void *result, void **arguments, void *user_data)
{
  CallbackDescriptor *descriptor = static_cast<CallbackDescriptor *>(user_data);
  Function *function = descriptor->function;
  ArgBlock block;
  memset(&block,0,sizeof(block));
  unsigned int argument_index = 0;
  if (function->is_method()) block.OPtr = static_cast<char *>(*reinterpret_cast<void **>(arguments[argument_index++]));

  std::vector<VMWord> words;
  Signature::iterator type = function->signature()->begin();
  for (; type != function->signature()->end(); ++type, ++argument_index)
    append_callback_value(words,*type,arguments[argument_index]);
  if (words.size() > sizeof(block.values)/sizeof(block.values[0]))
    return;
  block.no = static_cast<int>(words.size());
  for (size_t i = 0; i < words.size(); ++i) block.values[words.size()-i-1] = words[i];

  Type return_type = function->return_type();
  int flags = Engine::ARGS_PASSED;
  if (function->is_method()) flags |= Engine::METHOD_CALL;
  if (return_type.is_double()) flags |= Engine::RETURN_64;
  else if (!return_type.is_void()) flags |= Engine::RETURN_32;
  if (Engine::stub_execute(function->fun_block(),flags,&block) != OK) return;

  if (return_type.is_void()) return;
  if (return_type.is_double()) *reinterpret_cast<double *>(result) = block.ret2;
  else if (return_type.is_ref_or_ptr() || return_type.is_function())
    *reinterpret_cast<void **>(result) = vm_to_ptr(block.ret1);
  else if (return_type.is_single()) {
    VMWord word = block.ret1;
    memcpy(result,&word,sizeof(float));
  } else if (return_type.is_bool() || return_type.is_char()) {
    if (return_type.is_unsigned()) *reinterpret_cast<unsigned char *>(result) = static_cast<unsigned char>(block.ret1);
    else *reinterpret_cast<signed char *>(result) = static_cast<signed char>(block.ret1);
  } else if (return_type.is_short()) {
    if (return_type.is_unsigned()) *reinterpret_cast<unsigned short *>(result) = static_cast<unsigned short>(block.ret1);
    else *reinterpret_cast<short *>(result) = static_cast<short>(block.ret1);
  } else if (return_type.is_long()) {
    if (return_type.is_unsigned()) *reinterpret_cast<unsigned long *>(result) = static_cast<unsigned long>(block.ret1);
    else *reinterpret_cast<long *>(result) = static_cast<long>(block.ret1);
  } else if (return_type.is_unsigned()) *reinterpret_cast<unsigned int *>(result) = static_cast<unsigned int>(block.ret1);
  else *reinterpret_cast<int *>(result) = static_cast<int>(block.ret1);
}

} // namespace
#endif

void callfn(NFBlock *native, VMWord args[], int argc, void *optr, void *buff)
{
#ifndef UCL_LIBFFI
# ifdef UCL_SYSV_X86_64
  legacy_callfn(native->pfn,args,argc,optr,native->flags,buff,native->function);
# else
  legacy_callfn(native->pfn,args,argc,optr,native->flags,buff);
# endif
#else
  Function *function = native->function;
  Signature *signature = function->signature();
  Type return_type = function->return_type();

  if ((native->flags & DC_RET_OBJ) && !return_type.is_object())
    throw Exception("invalid native object-return metadata");
  if (return_type.is_object() && return_type.size() > 64 * 1024)
    throw Exception("native aggregate return exceeds the 64 KiB return buffer");

  VMWord *raw = args + 1;
  void *object_result_destination = NULL;
  const bool indirect_object_result = return_type.is_object() && function->return_object() != NULL;
  if (indirect_object_result) {
    if (argc < 1) throw Exception("native aggregate return has no destination");
    object_result_destination = vm_to_ptr(*raw++);
    if (!object_result_destination)
      throw Exception("native aggregate return destination is null");
    --argc;
  }

  unsigned int declared = signature->size();
  int declared_slots = 0;
  bool has_aggregate_argument = false;
  Signature::iterator slot_type = signature->begin();
  for (; slot_type != signature->end(); ++slot_type) {
    if (slot_type->is_object()) {
      has_aggregate_argument = true;
      declared_slots += vm_word_count(slot_type->size());
    }
    else if (slot_type->is_double() && !slot_type->is_ref_or_ptr())
      declared_slots += vm_word_count(sizeof(double));
    else ++declared_slots;
  }
  // Aggregate layout is interpreted through the import scheme below and may
  // include ABI-specific staging.  Scalar signatures, including bool/enum
  // promotions, must have an exact and deterministic VM-slot count.
  if (!has_aggregate_argument && !indirect_object_result &&
      ((!signature->stdarg() && argc != declared_slots) ||
       (signature->stdarg() && argc < declared_slots))) {
    char slot_error[128];
    sprintf(slot_error,"native call has %d VM argument slots; signature requires %d",
            argc,declared_slots);
    throw Exception(slot_error);
  }

  unsigned int capacity = declared + (optr ? 1 : 0) + argc;
  std::vector<ffi_type *> arg_types;
  std::vector<FFIValue> values(capacity);
  std::vector< std::vector<VMWord> > aggregate_values(capacity);
  std::vector<void *> value_ptrs;
  arg_types.reserve(capacity);
  value_ptrs.reserve(capacity);

  unsigned int value_index = 0;
  if (optr) {
    values[value_index].pointer = optr;
    arg_types.push_back(&ffi_type_pointer);
    value_ptrs.push_back(&values[value_index].pointer);
    ++value_index;
  }

  int consumed = 0;
  Signature::iterator it = signature->begin();
  for (; it != signature->end(); ++it) {
    int slots = 1;
    if (it->is_object()) {
      slots = vm_word_count(it->size());
      aggregate_values[value_index].resize(slots);
      memset(&aggregate_values[value_index][0],0,slots * sizeof(VMWord));
      memcpy(&aggregate_values[value_index][0],raw + consumed,it->size());
    } else {
      set_ffi_value(values[value_index],*it,raw + consumed,slots);
    }
    consumed += slots;
    arg_types.push_back(ffi_type_for(*it));
    value_ptrs.push_back(it->is_object()
      ? static_cast<void *>(&aggregate_values[value_index][0])
      : static_cast<void *>(&values[value_index]));
    ++value_index;
  }

  // A variadic tail has no declared type information in the historical VM.
  // Preserve every remaining VM word as a machine-width integer argument.
  while (signature->stdarg() && consumed < argc) {
    values[value_index].word = raw[consumed++];
    arg_types.push_back(sizeof(VMWord) == 8 ? &ffi_type_sint64 : &ffi_type_sint32);
    value_ptrs.push_back(&values[value_index].word);
    ++value_index;
  }

  ffi_cif cif;
  ffi_status status;
  unsigned int fixed_count = declared + (optr ? 1 : 0);
  ffi_type **types = arg_types.empty() ? NULL : &arg_types[0];
  void **arguments = value_ptrs.empty() ? NULL : &value_ptrs[0];
  if (signature->stdarg())
    status = ffi_prep_cif_var(&cif,FFI_DEFAULT_ABI,fixed_count,arg_types.size(),
                              ffi_type_for(return_type),types);
  else
    status = ffi_prep_cif(&cif,FFI_DEFAULT_ABI,arg_types.size(),
                          ffi_type_for(return_type),types);
  if (status != FFI_OK) throw Exception("libffi could not prepare native call");

  FFIValue result;
  memset(&result,0,sizeof(result));
  std::vector<VMWord> aggregate_result;
  void *result_pointer = &result;
  if (return_type.is_object()) {
    aggregate_result.resize(vm_word_count(return_type.size()));
    memset(&aggregate_result[0],0,aggregate_result.size() * sizeof(VMWord));
    result_pointer = &aggregate_result[0];
  }
  ffi_call(&cif,FFI_FN(native->pfn),result_pointer,arguments);
  if (return_type.is_object()) {
    memcpy(object_result_destination ? object_result_destination : gObjectReturnPtr,
           result_pointer,return_type.size());
    *reinterpret_cast<VMWord *>(buff) = vm_from_ptr(
      object_result_destination ? object_result_destination : gObjectReturnPtr);
  } else
    store_ffi_result(result,return_type,buff);
#endif
}

using namespace Parser;

//namespace { // private stuff
typedef std::list<Handle> HandleList;
HandleList lib_list;
Handle s_lib = NULL;

void *_get_std_stream(int i)
 {
  switch(i) {
   case 1: return stdin;
   case 2: return stdout;
   case 3: return stderr;
   case 4: return _str_in;   //See ex_vfscanf.cpp for this hack!
   case 5: return _str_out;
  }
  return stdout;
 }

void __break(int icode)
// use this builtin when debugging the system;
// *add 1.2.1 (Eric) Now takes an integer argument
{
 int i = 10; // set your breakpoint here!
}

// Sig is a hack that directly manipulates the Parser state so that when
// start_function() is called, it believes that a prototype has been found.

Sig& Sig::operator << (Type t)
{
 const char *name;
 if(m_arg_name) { name = m_arg_name; m_arg_name = NULL; }
 else name = "*";
 Parser::state.add_to_arg_list(t,name,NULL);
 return *this;
}

Sig& Sig::operator << (const char *arg_name)
{
 m_arg_name = arg_name;
 return *this;
}

void Sig::set_const(bool t)
{
  Parser::state.member_is_const = t;
}


void dissemble(PFBlock fb); // from dissem.cpp

int _dissem(FBlock *pfb) {
  try {
    dissemble(pfb);
   } catch(...) {
     return 0;
   }
   return 1;
}

typedef std::map<void *,int> PointerMap;
PointerMap mPtrMap;
bool gPtrCheckStart = false;

void *_new(int sz)
{
#ifdef _WIN32
  void *ptr = (void *)new char[sz];
#else
  void *ptr = malloc(sz);
#endif

if (Parser::debug.ptr_check) mPtrMap[ptr] = 1;
// cerr << "new " << sz << ' ' << ptr << endl;
return ptr;
}
// do note that "builtin" wrappers reverse their arg lists,
// so these guys are done backwards. (They will _never_ be called
// directly)
void *_new_vect(int n,int sz)
{
#ifdef _WIN32
  void *p = (void *)new char[sz*n];
#else
 void *p = malloc(sz*n);
#endif
 // *fix 1.5.0 The count must be recorded for every array, not only when the
 // pointer checker is on: CCALLV reads it back to drive the constructor and
 // destructor loops.  Without it alloc_size() fell back to 1, so only element
 // zero of a "new T[n]" was ever constructed.
 mPtrMap[p] = n;
 return p;
}

void _delete(char *ptr,int sz)
{
  if (Parser::debug.ptr_check && Builtin::alloc_size(ptr) == 0) {
      if (! Parser::debug.suppress_link_errors && gPtrCheckStart)
	     cerr << (void *)ptr << " is not allocated by us!\n";
  } else {
// *fix 1.5.0 Retire the entry before the block goes away.  A stale count left
// behind here is found again once the allocator recycles the address, and the
// ctor/dtor loops would then run over the wrong number of elements.
  mPtrMap.erase(ptr);
// *ch 1.2.9 patch
// *fix 1.5.0 the block comes from new char[], so it takes delete[]
#ifdef _WIN32
  delete [] ptr;
#else
 free(ptr);
#endif
  }
}

// *change 1.1.0 Overallocation to make room for the VMT now done by builtins...
// *fix 1.5.0 The hidden slot is one VM word, not one int.  VMT() in engine.h
// reads it at (char *)obj - sizeof(VMWord), so reserving sizeof(int) left the
// slot four bytes short on a 64-bit build, and "*VMT(mOP) = vtable" wrote
// across the front of the heap block.  The two have to agree; both say VMWord.
void* _new_ex(int sz)
{
 VMWord *p = (VMWord *)_new(sz+sizeof(VMWord));
 if (p == NULL) return NULL;
 *p = 0;   // to flag the VMT as NOT being created...
 return p+1;
}

void* _new_vect_ex(int n, int sz)
{
 // Elements sit at a stride of sz, and Class::size() already counts the hidden
 // VMT word for a class that has one, so element i's VMT slot is its own
 // leading word and only the word in front of element zero is strictly extra.
 // The per-element word kept here is slack at the tail of the block; it is
 // retained deliberately so the layout stays no tighter than it was in 1.2.9.
 VMWord *p = (VMWord *)_new_vect(n,sz + (int)sizeof(VMWord));
 if (p == NULL) return NULL;
 *p = 0;
 void *obj = p+1;
 // *fix 1.5.0 Key the count on the pointer the VM actually holds.  _new_vect
 // recorded it against the block base, but CCALLV and delete[] both see
 // base + one word, so that lookup never matched.
 mPtrMap[obj] = n;
 return obj;
}

void _delete_ex(char *ptr, int sz)
{
  if (ptr != NULL) {
    mPtrMap.erase(ptr);               // the object-pointer key
    _delete(ptr-sizeof(VMWord),sz);   // _delete drops the block-base key
  }
}

// *ch 1.2.9 patch
#ifndef _WIN32
void* operator new(size_t sz)
{
  void *p = malloc(sz);
  if (p == NULL) throw std::bad_alloc();
  return p;
}

void operator delete(void *p) throw()
{
 free(p);
}

void* operator new[](size_t sz)
{
  void *p = malloc(sz);
  if (p == NULL) throw std::bad_alloc();
  return p;
}

void operator delete[](void *p) throw()
{
  free(p);
}

#endif

const int CDECL = Function::CDECL;

namespace Builtin {

void add(const Sig& sig,const char *name, CALLFN fn, bool is_stdarg = false, int ftype=CDECL);

// this is used to find out how big allocated object arrays were....
int alloc_size(void *p)
{
 PointerMap::iterator pmi = mPtrMap.find(p);
 if (pmi != mPtrMap.end()) return pmi->second;
 // issue here is that when we're checking ALL alloc ptrs get an entry in this map!
 if (Parser::debug.ptr_check) return 0;
 else return 1;
}

// *add 0.9.4 Pointer sanity check if #opt p+
void bad_ptr_check(void *data)
{
  if (data == NULL)
      throw BadPointer("NULL pointer");
  // other checks (dangling, invalid, etc) go here....
}

typedef int (*TWOFN)(int,int);

int _wrap(char *name)
{
 Function *pf = Function::lookup(name);
 if (pf == NULL) return 0;
 TWOFN pfn = (TWOFN)generate_native_stub(pf);
 return (*pfn)(10,20);
}

// *add 1.0.0 These exported functions support the fast specialization map<string,int>
// You can of course use any other associative container for this implementation.

typedef std::map<string,int> MSI;
typedef MSI *PMSI;
typedef MSI::iterator IMSI;
typedef IMSI *PIMSI;

struct StrPair {
     string first;
     int second;
};
typedef StrPair* PSP;

void* _map_create()
{ return new MSI;    }

void  _map_destroy(void *pm)
{ delete PMSI(pm);}

int   _map_size(void *pm)
{ return PMSI(pm)->size(); }

int*  _map_find(const string& key,void *pm) {
   MSI::iterator msi = PMSI(pm)->find(key);
   return msi != PMSI(pm)->end() ? &msi->second : 0;
}

int*  _map_insert(const string& key,int val,void *pm) {
  int& res = (*PMSI(pm))[key] = val;
  return &res;
}

// *ad 1.2.9 corresponding iterator stuff
void* _map_iter_ep(void* pm, int which)
{
    MSI::iterator it;
    if (which==0) it = PMSI(pm)->begin();
            else  it = PMSI(pm)->end();
    return new IMSI(it);
}

void* _map_iter_find(void* pm, const string& key)
{
    MSI::iterator it = PMSI(pm)->find(key);
    return new IMSI(it);
}

int  _map_iter_equal(void* i1, void* i2)
{
  return *PIMSI(i1) == *PIMSI(i2);
}

void _map_iter_fetch(void* pi, void* dat)
{
  PSP(dat)->first =  (*PIMSI(pi))->first;
  PSP(dat)->second = (*PIMSI(pi))->second;
}

void _map_iter_next(void* pi, int wdir)
{
  ++(*PIMSI(pi));
}

void* _native_stub(FBlock *pfb)
{
//*fix 1.2.3a The function may well be NULL...
   if (pfb == NULL) return NULL;
   if (pfb->function->builtin()) return pfb->native_addr();
   else return generate_native_stub(pfb->function);
}

// *add 1.2.5 range checking: _range_check
int _range_check(int sz, int i)
{
    if (i >= sz || i < 0) {
        char buff[80];
        if (i >= sz) sprintf(buff,"Range Error: %d >= %d",i,sz);
               else  sprintf(buff,"Range Error: %d < 0",i);
#ifdef _WIN32
        throw RangeError(buff);
#else
        throw_range_error(buff);
#endif
    }
    return i;
}

static int mRangeCheck;

double sin(double x) { return ::sin(x); }
double cos(double x) { return ::cos(x); }
double tan(double x) { return ::tan(x); }
double exp(double x) { return ::exp(x); }
double log(double x) { return ::log(x); }
double sqrt(double x ) { return ::sqrt(x); }
double atan2(double x,double y) { return ::atan2(x,y); }
double pow(double x,double y) { return ::pow(x,y); }
const char* strstr(const char*s1,const char*s2) { return ::strstr(s1,s2); }
const char* strchr(const char*s,int c) { return ::strchr(s,c); }
const char* strrchr(const char*s,int c) { return ::strrchr(s,c); }
int _fprint_double(void *stream, double value)
{
  static char format[] = "%g";
  return ::fprintf(static_cast<FILE *>(stream),format,value);
}
#if defined(UCL_LIBFFI) || defined(UCL_SYSV_X86_64)
int _ffi_sum8(int a, int b, int c, int d, int e, int f, int g, int h)
{ return a+b+c+d+e+f+g+h; }
int _ffi_order8(int a, int b, int c, int d, int e, int f, int g, int h)
{ return a+2*b+4*c+8*d+16*e+32*f+64*g+128*h; }
#endif

void init()
{
 Type t_ccp = t_char_ptr;
 Type t_int_ptr = t_int;
 t_ccp.make_const();
 t_int_ptr.incr_pointer();
 Signature *exit_signature = new Signature(t_void);
 Type exit_function(exit_signature);
 exit_function.incr_pointer();

 add(Sig(t_void_ptr) << t_void_ptr,     "_native_stub",(CALLFN)_native_stub);
 add(Sig(t_void_ptr) << t_int,          "_new",(CALLFN)&_new);
 add(Sig(t_void_ptr) << t_int << t_int, "_new_vect",(CALLFN)&_new_vect);
 add(Sig(t_void) << t_char_ptr << t_int,"_delete",(CALLFN)&_delete);
 add(Sig(t_void_ptr) << t_int,          "_new_ex",(CALLFN)&_new_ex);
 add(Sig(t_void_ptr) << t_int << t_int, "_new_vect_ex",(CALLFN)&_new_vect_ex);
 add(Sig(t_void) << t_char_ptr << t_int,"_delete_ex",(CALLFN)&_delete_ex);

 add(Sig(t_double) << t_double,"sin",(CALLFN)&sin);
 add(Sig(t_double) << t_double,"cos",(CALLFN)&cos);
 add(Sig(t_double) << t_double,"tan",(CALLFN)&tan);
 add(Sig(t_double) << t_double << t_double,"atan2",(CALLFN)&atan2);
 add(Sig(t_double) << t_double << t_double,"pow",(CALLFN)&pow);
 add(Sig(t_double) << t_double,"exp",(CALLFN)&exp);
 add(Sig(t_double) << t_double,"log",(CALLFN)&log);
 add(Sig(t_double) << t_double,"sqrt",(CALLFN)&sqrt);
 add(Sig(t_double) << t_ccp,"atof",(CALLFN)&atof);
 add(Sig(t_long) << t_ccp,"atoi",(CALLFN)&atoi);
 add(Sig(t_char_ptr) << t_int << t_char_ptr << t_int, "itoa", (CALLFN)&_itoa);
 add(Sig(t_int) << t_void,"rand",(CALLFN)&rand);
 add(Sig(t_int) << t_void_ptr << t_double,
     "_fprint_double",(CALLFN)&_fprint_double);
 add(Sig(t_char_ptr) << t_ccp,"getenv",(CALLFN)&getenv);
 add(Sig(t_int) << t_ccp,"system",(CALLFN)&system);
 add(Sig(t_char_ptr) << t_double << t_int << t_char_ptr,
     "_gcvt",(CALLFN)&uc_gcvt);
 add(Sig(t_int) << exit_function,"atexit",(CALLFN)&uc_atexit);
 add(Sig(t_int) << t_ccp << t_int,"_access",(CALLFN)&uc_access);
#if defined(UCL_LIBFFI) || defined(UCL_SYSV_X86_64)
 add(Sig(t_int) << t_int << t_int << t_int << t_int
                << t_int << t_int << t_int << t_int,
     "_ffi_sum8",(CALLFN)&_ffi_sum8);
 add(Sig(t_int) << t_int << t_int << t_int << t_int
                << t_int << t_int << t_int << t_int,
     "_ffi_order8",(CALLFN)&_ffi_order8);
#endif

 add(Sig(t_char_ptr) << t_char_ptr << t_ccp,"strcpy",(CALLFN)&strcpy);
 add(Sig(t_char_ptr) << t_char_ptr << t_ccp << t_int,"strncpy",(CALLFN)&strncpy);
 add(Sig(t_char_ptr) << t_char_ptr << t_ccp,"strcat",(CALLFN)&strcat);
 add(Sig(t_int) << t_ccp << t_ccp,"strcmp",(CALLFN)&strcmp);
 add(Sig(t_char_ptr) << t_ccp,"strdup",(CALLFN)&_strdup);
 add(Sig(t_char_ptr) << t_char_ptr << t_ccp,"strtok",(CALLFN)&strtok);
 add(Sig(t_char_ptr) << t_char_ptr << t_char_ptr,"strstr",(CALLFN)&strstr);
 add(Sig(t_char_ptr) << t_char_ptr << t_int,"strchr",(CALLFN)&strchr);
 add(Sig(t_char_ptr) << t_char_ptr << t_int,"strrchr",(CALLFN)&strrchr);
 add(Sig(t_int) << t_ccp,"strlen",(CALLFN)&strlen);
 add(Sig(t_void_ptr) << t_void_ptr << t_void_ptr << t_int,
      "memmove",(CALLFN)&memmove);

 add(Sig(t_void_ptr) << t_void_ptr << t_int, "_str_cpy", (CALLFN)&str_cpy);
 add(Sig(t_int) << t_int, "_str_eof", (CALLFN)&str_eof);

 // stdio builtins (first entry used to get stdin, etc)
 add(Sig(t_void_ptr) << t_int,"_get_std_stream",(CALLFN)&_get_std_stream);
 add(Sig(t_int) << t_ccp,"puts",(CALLFN)&puts);
 add(Sig(t_int) << t_ccp,"printf",(CALLFN)&printf,true);
 add(Sig(t_int) << t_ccp << t_ccp,"sprintf",(CALLFN)&sprintf,true);
 // *change 1.2.3 GCC has finally persuaded me not to export puts().
 // add(Sig(t_char_ptr) << t_char_ptr,"gets",(CALLFN)&gets);
 add(Sig(t_char_ptr) << t_char_ptr << t_int << t_void_ptr,"fgets",(CALLFN)&fgets);
 add(Sig(t_int) << t_void_ptr << t_ccp,"fprintf",(CALLFN)&fprintf,true);
 add(Sig(t_int) << t_void_ptr << t_ccp,"fscanf",(CALLFN)&fscanf,true);
 add(Sig(t_int) << t_int << t_void_ptr, "ungetc",(CALLFN)&ungetc,true);

 add(Sig(t_int) << t_void_ptr << t_ccp,"wcon_fscanf",(CALLFN)&wcon_fscanf,true);

 add(Sig(t_int) << t_void_ptr << t_int << t_int << t_void_ptr,"fread",(CALLFN)&fread);
 add(Sig(t_int) << t_void_ptr << t_int << t_int << t_void_ptr,"fwrite",(CALLFN)&fwrite);
 add(Sig(t_int) << t_void_ptr,"feof",(CALLFN)&feof);
 add(Sig(t_void_ptr) << t_char_ptr << t_char_ptr,"fopen",(CALLFN)&fopen);
 add(Sig(t_int) << t_void_ptr, "fclose",(CALLFN)&fclose);
 add(Sig(t_int) << t_void_ptr, "fflush",(CALLFN)&fflush);
 add(Sig(t_void_ptr) << t_ccp << t_ccp, "popen",(CALLFN)&uc_popen);
 add(Sig(t_int) << t_void_ptr, "pclose",(CALLFN)&uc_pclose);
 add(Sig(t_int) << t_char_ptr << t_char_ptr, "rename", (CALLFN)&rename);
 add(Sig(t_int) << t_void_ptr, "fgetc", (CALLFN)&fgetc);
 add(Sig(t_int) << t_int << t_void_ptr, "fputc", (CALLFN)&fputc);
 add(Sig(t_int) << t_ccp << t_void_ptr, "fputs", (CALLFN)&uc_fputs);
 add(Sig(t_int) << t_int << t_void_ptr, "putc", (CALLFN)&uc_putc);
 add(Sig(t_int) << t_int, "putchar", (CALLFN)&uc_putchar);
 add(Sig(t_int) << t_void_ptr << t_long << t_int, "fseek", (CALLFN)&fseek);
 add(Sig(t_long) << t_void_ptr, "ftell", (CALLFN)&ftell);

 add(Sig(t_void) << t_ccp,"uc_cmd",(CALLFN)&uc_hash_cmd);
 add(Sig(t_void) << t_ccp << t_char_ptr << t_int,"uc_macro_subst",(CALLFN)&uc_macro_subst);
 add(Sig(t_int) << t_void_ptr, "_dissem",(CALLFN)&_dissem);
 //add(Sig(t_void), "_init_lib",(CALLFN)&Parser::init_lib);
 // *add 1.2.5 range checking: _range_check
 add(Sig(t_int) << t_int << t_int,"_range_check",(CALLFN)&_range_check);

 // *add 1.2.4 uc_exec(), uc_result()
 add(Sig(t_int) << t_ccp,"uc_exec",(CALLFN)&_uc_exec_1);
 add(Sig(t_int) << t_ccp << t_void_ptr << t_ccp << t_int,"uc_exec",(CALLFN)&_uc_exec);
 add(Sig(t_void) << t_int << t_char_ptr << t_int << t_char_ptr << t_void_ptr,"uc_result_pos",(CALLFN)&_uc_result);
 add(Sig(t_void_ptr) << t_char_ptr,"copy_body",(CALLFN)&_copy_body);

 // *add 1.2.6 uc_include_path() will find a system file using the UC include paths.
 add(Sig(t_int) << t_ccp << t_char_ptr << t_int,"uc_include_path",(CALLFN)&_uc_include_path);

// These support the specialization map<string,int> (see <map> in the pocket library)
 add(Sig(t_void_ptr) << t_void,                           "_map_create",  (CALLFN)&_map_create);
 add(Sig(t_void)    << t_void_ptr,                        "_map_destroy", (CALLFN)&_map_destroy);
 add(Sig(t_int)     << t_void_ptr,                        "_map_size",    (CALLFN)&_map_size);
 add(Sig(t_int_ptr) << t_void_ptr << t_void_ptr,          "_map_find",    (CALLFN)&_map_find);
 add(Sig(t_int_ptr) << t_void_ptr << t_int << t_void_ptr, "_map_insert",  (CALLFN)&_map_insert);
 // *add 1.2.9 iterator support for the fast specialization
 add(Sig(t_void_ptr) << t_void_ptr << t_int,              "_map_iter_ep", (CALLFN)&_map_iter_ep);
 add(Sig(t_void_ptr) << t_void_ptr << t_void_ptr,         "_map_iter_find",(CALLFN)&_map_iter_find);
 add(Sig(t_int)      << t_void_ptr << t_void_ptr,         "_map_iter_equal",(CALLFN)&_map_iter_equal);
 add(Sig(t_void)     << t_void_ptr << t_void_ptr,         "_map_iter_fetch",(CALLFN)&_map_iter_fetch);
 add(Sig(t_void)     << t_void_ptr << t_int,              "_map_iter_next", (CALLFN)&_map_iter_next);

 add(Sig(t_void) << t_int,"__break",(CALLFN)__break);
 add(Sig(t_void) << t_void,"__mangle",(CALLFN)__mangle);

 // UCW Graphics
 #ifdef _WCON
 //unsigned long ucw_rgb(int r, int g, int b);
 //void ucw_set_colour(UCWin win, unsigned long clr, bool fg);

 add(Sig(t_int) << t_char_ptr << t_int << t_int << t_int << t_int,
         "ucw_create_window",(CALLFN)&ucw_create_window);
 add(Sig(t_int) << t_int << t_char_ptr,"ucw_title",(CALLFN)&ucw_title);
 add(Sig(t_int) << t_int << t_char_ptr,"ucw_cmd",(CALLFN)&ucw_cmd);
 add(Sig(t_int) << t_int << t_int << t_int << t_int << t_int,"ucw_size_window",(CALLFN)&ucw_size_window);
 add(Sig(t_int) << t_int << t_int << t_int,"ucw_move_to",(CALLFN)&ucw_move_to);
 add(Sig(t_int) << t_int << t_int << t_int,"ucw_line_to",(CALLFN)&ucw_line_to);
 add(Sig(t_int) << t_int << t_char_ptr,"ucw_text_out",(CALLFN)&ucw_text_out);
 add(Sig(t_int) << t_int << t_char_ptr << t_int,"ucw_font",(CALLFN)&ucw_font);
 add(Sig(t_int) << t_int << t_float << t_float << t_float,"ucw_fcolour",(CALLFN)&ucw_fcolour);
 add(Sig(t_int) << t_int << t_float << t_float << t_float,"ucw_bcolour",(CALLFN)&ucw_bcolour);
 add(Sig(t_int) << t_int << t_int << t_int << t_int << t_int,"ucw_rectangle",(CALLFN)&ucw_rectangle);
 add(Sig(t_int) << t_int << t_int << t_int << t_int << t_int,"ucw_ellipse",(CALLFN)&ucw_ellipse);
 add(Sig(t_int) << t_char_ptr << t_int << t_bool,"exec",(CALLFN)&exec);
 add(Sig(t_long) << t_int << t_int << t_int,"ucw_rgb",(CALLFN)&ucw_rgb);
 add(Sig(t_void) << t_int << t_long << t_int,"ucw_set_colour",(CALLFN)&ucw_set_colour);
#endif

 Function* pf = Function::lookup("_range_check");
 mRangeCheck = NFBlock::create(pf,(CALLFN)pf->fun_block()->native_addr());
}

//---------------------- adding builtin functions ---------------------------
// We keep a map of imported functions to quickly tell what they are imported as!
typedef std::map<CALLFN,FBlock *> ClassImportMap;
ClassImportMap mImportMap;

// *hack 1.2.0 The optimized Win32 MS build blows up here occaisionally - no idea why!
#pragma optimize( "", off )
static FBlock *_pfb;
static Function *_pfn;
static int _kount = 0;
void insert_ptr_map(CALLFN fn, Function *pfn)
{
  try {
  _pfn = pfn;
  _pfb = pfn->fun_block();
  mImportMap[fn] = _pfb;
  } catch(...) {
     ++_kount;
  }
}
#pragma optimize( "", on )

void add(const Sig& sig,const char *name, CALLFN fn, bool is_stdarg, int ftype)
// Builtin::add() assumes that the Signature has been collected in the proper way.
// It's usually called from state.declare_function(), but also from add_dll_function().
// In both cases the class Sig acts as a interface to the common signature stuff.
{
 Function *pfn = state.start_function(sig.m_type,name,true,ftype);
 FunctionContext *fe = pfn->context();
 int nargs = pfn->fun_block()->nargs;
 if (is_stdarg) pfn->stdarg(true);

 Parser::code().emit_native_function_call(pfn,fn);


#ifdef __GNUC__
 mImportMap[fn] = pfn->fun_block();
#else
 insert_ptr_map(fn,pfn);
#endif

 fe->finalize();
 state.pop_context(); // usually done by block-end!
}

// *add 1.2.5 Offset of range checking function
int range_check_function()
{
  return mRangeCheck;
}

FBlock *import_vmethod(CALLFN fn, PFBlock pfb)
// this is passed a native routine, and a UC function block which acts as a prototype
// for the _anonymous method import_
{
  Parser::set_function_code(true);  // enter function code context
  UCContext& code = Parser::code();
  Function *pf = pfb->function;
  FBlock *fb;
  try {
	fb = FBlock::create(pfb->entry,NULL);
	mImportMap[fn] = fb;
    code.emit_native_function_call(pf,fn);
    code.emit_return(pf->return_type());

	fb->finalize(0);
  } catch(...) { error("error when importing function"); }
  Parser::set_function_code(false); // go back to static code context
  return fb;
}

//----------------------- importing functions and methods from DLLs -------------


FBlock *imported_fblock_from_function(void *pfn)
{
  return mImportMap[(CALLFN)pfn];
}


CALLFN lookup_self_link(PClass pc, const string& name);  // later in this module...


// *add    1.2.3  Support for uc_import() - the UseAddr modifier
static void* mDirectAddr = NULL;

void set_direct_import(void* p)
{
// A Two-Part Hack.
// It's NB to call this function with a NULL argument afterwards to reset the state.
  if (p) {
      // (1)the current DLL handle needs to be non-NULL, but doesn't have to be sensible
      // This is just to force Parser::declare_function() to call add_dll_function()
      // below
      set_dll_handle((void*)-1);
      // (2)The modifier flag will be passed to add_dll_function(), so we give it
      // a special value so it will pick up the pointer directly....
      Parser::state.modifier = UseAddr;
      mDirectAddr = p;
  } else {
      set_current_lib_file(0);
      mDirectAddr = NULL;
  }
}

bool add_dll_function(Function *pfn, int modifier, string& name)
{
  PClass pc = pfn->class_context();
  CALLFN proc;

#ifdef UCL_LIBFFI
  // Direct host imports use the maintained compiler ABI adapter even when no
  // dynamic-library directive established a historical import scheme.
  if (modifier == UseAddr && !pfn->import_scheme())
    pfn->import_scheme(Import::create_scheme(2));
#endif

  // *change 0.9.4  Need explicit extern "C" now - (used to simply be class context)
  // *add    1.1.4  Implicit self-link for those systems which need it...
  if (modifier == UseAddr) proc = (CALLFN) mDirectAddr;
#ifdef CANNOT_SELF_LINK
  else if (get_dll_handle()==IMPLICIT_LINK) {
    name = pfn->name(); // *fix 1.2.4 pass back name in case we can't find
    proc = lookup_self_link(pc,name);
  }
#endif
  else if(! Parser::in_extern_C()) { // mangled C++ name
#ifndef UCL_LEGACY_CPP_IMPORTS
    name = "?C++ imports are disabled; use extern C or UCL_LEGACY_CPP_IMPORTS";
    return false;
#else
    proc = (CALLFN)Import::load_method_entry(pfn,name);
	if (name=="") name = "?" + pfn->name();
#endif
  } else { // extern "C"
    name = pfn->name();
    if (modifier == Stdcall) name = "_" + name + "@" + itos(pfn->signature()->byte_size());
    proc = (CALLFN)get_proc_address(s_lib,name.c_str());
  }
  if (!proc) return false;

  if (pc != NULL) pc->set_imported();

  Sig ssig(pfn->return_type());
  Signature *sig = pfn->signature();
  Signature::iterator tli;
  for(tli = sig->begin(); tli != sig->end(); ++tli) ssig << (Type)*tli;
  ssig.set_const(sig->is_const());  // *fix 1.1.0  Must respect constness of signature!

  // *fix 1.2.3 Important also to mke the signature reflect any extra unnamed arguments....
 if (sig->stdarg()) ssig << t_void;  // the convention used by the parser...


// *fix 1.1.0 We can now distinguish between ordinary cdecl method calls (GCC)
// and so-called '__thiscall' calls (MS)
// *add 1.2.3 Note that direct imports into the DLL are NOT stdcall under Linux!
  int calling_convention = Function::CDECL;
  if (modifier == Stdcall || modifier == Api
#ifdef _WIN32
      || modifier == UseAddr
#endif
   )
      calling_convention = Function::_STDCALL;

  if(pfn->is_method()) {
    if (pc->import_scheme()->uses_stdmethod()) calling_convention = Function::STDMETHOD;
  }

  add(ssig,(char*)pfn->name().c_str(),proc,false,calling_convention);

  return true;
}



//----------------------- generating native stubs -------------------------
#ifndef UCL_LIBFFI
#if defined(UCL_SYSV_X86_64)

struct LegacyCallbackResult {
  uint64_t integer_value;
  uint64_t sse_value;
};

struct LegacyCallbackDescriptor {
  Function *function;
  void *entry;
  size_t allocation_size;
  LegacyCallbackDescriptor() : function(NULL), entry(NULL), allocation_size(0) {}
};

typedef std::list<LegacyCallbackDescriptor *> LegacyCallbackList;
static LegacyCallbackList legacy_callback_list;

extern "C" void underc_sysv_callback_entry();

static void legacy_append_callback_value(std::vector<VMWord>& words,
                                         const Type& type, uint64_t bits)
{
  if (type.is_double()) {
    VMWord slots[vm_word_count(sizeof(double))];
    memset(slots,0,sizeof(slots));
    memcpy(slots,&bits,sizeof(double));
    for (int i = 0; i < vm_word_count(sizeof(double)); ++i) words.push_back(slots[i]);
  } else if (type.is_single()) {
    VMWord word = 0;
    memcpy(&word,&bits,sizeof(float));
    words.push_back(word);
  } else {
    words.push_back(static_cast<VMWord>(bits));
  }
}

extern "C" void underc_sysv_callback_invoke(void *opaque,
                                             const uint64_t integer_args[6],
                                             const uint64_t sse_args[8],
                                             const uint64_t *stack_args,
                                             LegacyCallbackResult *result)
{
  LegacyCallbackDescriptor *descriptor = static_cast<LegacyCallbackDescriptor *>(opaque);
  Function *function = descriptor->function;
  ArgBlock block;
  memset(&block,0,sizeof(block));
  unsigned int integer_index = 0, sse_index = 0, stack_index = 0;
  if (function->is_method())
    block.OPtr = reinterpret_cast<char *>(static_cast<uintptr_t>(integer_args[integer_index++]));

  std::vector<VMWord> words;
  Signature::iterator type = function->signature()->begin();
  for (; type != function->signature()->end(); ++type) {
    uint64_t bits;
    if (sysv_sse_type(*type) && sse_index < 8) bits = sse_args[sse_index++];
    else if (!sysv_sse_type(*type) && integer_index < 6) bits = integer_args[integer_index++];
    else bits = stack_args[stack_index++];
    legacy_append_callback_value(words,*type,bits);
  }
  if (words.size() > sizeof(block.values)/sizeof(block.values[0])) return;
  block.no = static_cast<int>(words.size());
  for (size_t i = 0; i < words.size(); ++i) block.values[words.size()-i-1] = words[i];

  Type return_type = function->return_type();
  int flags = Engine::ARGS_PASSED;
  if (function->is_method()) flags |= Engine::METHOD_CALL;
  if (return_type.is_double()) flags |= Engine::RETURN_64;
  else if (!return_type.is_void()) flags |= Engine::RETURN_32;
  if (Engine::stub_execute(function->fun_block(),flags,&block) != OK) return;
  if (return_type.is_double()) memcpy(&result->sse_value,&block.ret2,sizeof(double));
  else if (return_type.is_single()) memcpy(&result->sse_value,&block.ret1,sizeof(float));
  else result->integer_value = static_cast<uint64_t>(block.ret1);
}

void *generate_native_stub(Function *pfn)
{
  if (!pfn || pfn->signature()->stdarg()) return NULL;
  if (pfn->return_type().is_object())
    throw Exception("interpreted objects by value require libffi callbacks");
  Signature::iterator type = pfn->signature()->begin();
  for (; type != pfn->signature()->end(); ++type)
    if (type->is_object())
      throw Exception("interpreted objects by value require libffi callbacks");

  for (LegacyCallbackList::iterator existing = legacy_callback_list.begin();
       existing != legacy_callback_list.end(); ++existing)
    if ((*existing)->function == pfn) return (*existing)->entry;

  LegacyCallbackDescriptor *descriptor = new LegacyCallbackDescriptor;
  descriptor->function = pfn;
  descriptor->allocation_size = static_cast<size_t>(sysconf(_SC_PAGESIZE));
  descriptor->entry = mmap(NULL,descriptor->allocation_size,PROT_READ | PROT_WRITE,
                           MAP_PRIVATE | MAP_ANONYMOUS,-1,0);
  if (descriptor->entry == MAP_FAILED) {
    delete descriptor;
    throw Exception("could not allocate x86-64 callback trampoline");
  }

  unsigned char code[] = {
    0x49,0xBA, 0,0,0,0,0,0,0,0,       // movabs descriptor,%r10
    0x49,0xBB, 0,0,0,0,0,0,0,0,       // movabs callback entry,%r11
    0x41,0xFF,0xE3                      // jmp *%r11
  };
  uint64_t descriptor_address = reinterpret_cast<uintptr_t>(descriptor);
  uint64_t callback_address = reinterpret_cast<uintptr_t>(&underc_sysv_callback_entry);
  memcpy(code + 2,&descriptor_address,sizeof(descriptor_address));
  memcpy(code + 12,&callback_address,sizeof(callback_address));
  memcpy(descriptor->entry,code,sizeof(code));
  if (mprotect(descriptor->entry,descriptor->allocation_size,PROT_READ | PROT_EXEC) != 0) {
    munmap(descriptor->entry,descriptor->allocation_size);
    delete descriptor;
    throw Exception("could not make x86-64 callback trampoline executable");
  }
  __builtin___clear_cache(static_cast<char *>(descriptor->entry),
                          static_cast<char *>(descriptor->entry) + sizeof(code));
  legacy_callback_list.push_back(descriptor);
  return descriptor->entry;
}

#else
// Basically this is a mad (and v. limited) x86 macro assembler.

typedef unsigned long ulong;
typedef char *pchar;
typedef short *& pshort;
typedef ulong *& pulong;

// Disable some silly warnings:
// truncation of const value and 'int' to 'short'.
#pragma warning(disable:4309)
#pragma warning(disable:4305)

void emit1(pchar& pc, char ch)      {  *pc++ = ch; }
void emit2(pchar& pc, short s)      {  *pshort(pc)++ = s; }
void emit4(pchar& pc, ulong l)      {  *pulong(pc)++ = l;}
void pushc(pchar& pc, ulong val)    { emit1(pc,0x68); emit4(pc,val); }
void pushv(pchar& pc, void *ptr)    { emit2(pc,0x35FF); emit4(pc,(ulong)ptr); }
void popv(pchar& pc, void *ptr)     { emit2(pc,0x058F); emit4(pc,(ulong)ptr); }
void callf(pchar& pc, void *pfn) {
  emit1(pc,0xBA);   emit4(pc,(ulong)pfn);     // mov edx, offset copy array
  emit2(pc,0xD2FF);                                   // call edx
}
void mov_acc(pchar& pc, ulong val)  { emit1(pc,0xB8);   emit4(pc,val);  }    // mov eax,...
void mov_ptr(pchar& pc, void *val)  { emit1(pc,0xB9);   emit4(pc,(ulong)val);  } // mov ecx..
void copy_acc(pchar& pc, void *ptr) { emit1(pc,0xA1);   emit4(pc,(ulong)ptr);  }
void copy_cx(pchar& pc, void *ptr)  { emit2(pc,0x0D89); emit4(pc,(ulong)ptr); }
void sub_esp(pchar& pc, int val)    { emit2(pc,0xEC81);   emit4(pc,(ulong)val); }
void push_qword(pchar& pc, void *ptr) { emit2(pc,0x05DD); emit4(pc,(ulong)ptr); }
void ret(pchar& pc)                 { emit1(pc,(char)0xC3);   }

void *generate_native_stub(Function *pfn)
{
// The stub must copy the arguments by calling copy_array(), and then calls Engine::execute().
  char cde_buff[200];
  Signature *sig = pfn->signature();

  int no_args = sig->byte_size()/sizeof(int);
  void *rra = new ulong;
  // copy_array fills in OPtr/no, but it is only called when the callback
  // actually takes arguments.  A zero-argument callback would otherwise reach
  // Engine::execute with an uninitialized argument count and push that many
  // words off the end of values[].
  ArgBlock *xargs = new ArgBlock;
  memset(xargs,0,sizeof(ArgBlock));
  int flags = Engine::ARGS_PASSED;
  char *pc = cde_buff;
  // *fix 1.1.4     Plain function callbacks are often cdecl...but think about this!
  // *change 1.2.3  Functions export as cdecl, unless __stdcall is used;
  //                MS methods don't and GCC methods do; determined by is_cdecl().
  bool fun_is_cdecl;
  if (pfn->is_method()) {
      fun_is_cdecl = pfn->is_cdecl();
  } else
      fun_is_cdecl = pfn->export_as_cdecl();

  popv(pc,rra);                                                    // save return addr
  if (pfn->is_method())  {
      if (pfn->class_context()->import_scheme()->uses_stdmethod()) // is this a stdmethod call?
           copy_cx(pc,&xargs->OPtr);                                // obj ptr was in ecx
      else {
         popv(pc,&xargs->OPtr);                                     // obj ptr was on the stack
         no_args++;                                                // as an _extra_ arg
	  }
      flags = flags | Engine::METHOD_CALL;
  }
  Type rt = pfn->return_type();
  if (rt.is_double()) flags = flags | Engine::RETURN_64; else
  if (!rt.is_void()) flags = flags | Engine::RETURN_32;
  if (no_args > 0) {
  // two different strategies here, depending on the compiler
#ifndef __GNUC__
    mov_ptr(pc,xargs);
    mov_acc(pc,no_args);                                          // call copy_array
    callf(pc,(void *)&copy_array);
  // copy_array mucks w/ ESP by explicitly popping the arguments;
  // cdecl calls assume that caller will sort out ESP.

   if (fun_is_cdecl)
     sub_esp(pc, sizeof(int)*no_args);                            // restore esp if cdecl
  #else
    pushc(pc,(unsigned long)xargs);
    pushc(pc,no_args);
    callf(pc,(void *)&copy_array);
    sub_esp(pc, -8);                  // because copy_array is cdecl...
    if (! fun_is_cdecl)              // if we're NOT cdecl then clean up like a good boy!
      sub_esp(pc, -sizeof(int)*no_args);

  #endif
  }
  pushc(pc,(ulong)xargs);
  pushc(pc,flags);
  pushc(pc,(ulong)pfn->fun_block());
  callf(pc,(void *)&Engine::stub_execute);                        // and call the stack engine!
  if (flags & Engine::RETURN_32) copy_acc(pc,&xargs->ret1);       // put result in eax, if needed
  else
  if (flags & Engine::RETURN_64)  push_qword(pc,&xargs->ret2);    // or onto fp stack *add 1.1.1
  pushv(pc,rra);                                                  // restore return addr & return
  ret(pc);

  // and copy the code block into a page the host will let us execute; the
  // C++ heap is no-execute on every current desktop OS, so the historical
  // new char[] here faulted as soon as the native caller entered the stub.
  size_t sz = static_cast<size_t>(pc - cde_buff);
  void *entry = alloc_executable(cde_buff,sz);
  if (entry == NULL) throw Exception("could not allocate a native callback stub");
  return entry;
}
#endif
#else
void *generate_native_stub(Function *pfn)
{
  if (!pfn || pfn->signature()->stdarg()) return NULL;
  if (pfn->return_type().is_object())
    throw Exception("interpreted objects by value cannot be exported as callbacks");

  for (CallbackList::iterator existing = callback_list.begin();
       existing != callback_list.end(); ++existing)
    if ((*existing)->function == pfn) return (*existing)->entry;

  CallbackDescriptor *descriptor = new CallbackDescriptor;
  descriptor->function = pfn;
  if (pfn->is_method()) descriptor->argument_types.push_back(&ffi_type_pointer);
  Signature::iterator type = pfn->signature()->begin();
  for (; type != pfn->signature()->end(); ++type) {
    if (type->is_object()) {
      delete descriptor;
      throw Exception("interpreted objects by value cannot be callback arguments");
    }
    descriptor->argument_types.push_back(ffi_type_for(*type));
  }
  ffi_type **arguments = descriptor->argument_types.empty() ? NULL : &descriptor->argument_types[0];
  if (ffi_prep_cif(&descriptor->cif,FFI_DEFAULT_ABI,descriptor->argument_types.size(),
                   ffi_type_for(pfn->return_type()),arguments) != FFI_OK) {
    delete descriptor;
    throw Exception("libffi could not prepare interpreted callback");
  }
  descriptor->closure = static_cast<ffi_closure *>(ffi_closure_alloc(sizeof(ffi_closure),&descriptor->entry));
  if (!descriptor->closure ||
      ffi_prep_closure_loc(descriptor->closure,&descriptor->cif,ffi_callback,descriptor,
                           descriptor->entry) != FFI_OK) {
    if (descriptor->closure) ffi_closure_free(descriptor->closure);
    delete descriptor;
    throw Exception("libffi could not allocate interpreted callback");
  }
  callback_list.push_back(descriptor);
  return descriptor->entry;
}
#endif

void release_native_stubs(Function *pfn)
{
  if (!pfn) return;
#ifdef UCL_LIBFFI
  CallbackList::iterator callback = callback_list.begin();
  while (callback != callback_list.end()) {
    if ((*callback)->function == pfn) {
      ffi_closure_free((*callback)->closure);
      delete *callback;
      callback = callback_list.erase(callback);
    } else ++callback;
  }
#elif defined(UCL_SYSV_X86_64)
  LegacyCallbackList::iterator callback = legacy_callback_list.begin();
  while (callback != legacy_callback_list.end()) {
    if ((*callback)->function == pfn) {
      munmap((*callback)->entry,(*callback)->allocation_size);
      delete *callback;
      callback = legacy_callback_list.erase(callback);
    } else ++callback;
  }
#else
  (void)pfn;
#endif
}


// *add 1.1.4 The Linux tool chain currently doesn't allow you to link to self,
//            so we have to explicitly specify self-exports.
#ifndef CANNOT_SELF_LINK
 static const int sNoSelfLink = false;
#else
 static const int sNoSelfLink = true;
#endif

//-------------------- shared library management ----------------
static string s_file;

bool set_current_lib_file(char *file)
{
 if (!file) {
   s_lib = NULL;
   cleanup_ordinal_lookup();
 } else {
// *add 1.1.2 Linking to #self finds the actual full path of UC pgm
  // *fix 1.1.4 It's now #pragma dlink $self,etc! (otherwise argues with prepro)
  if (file[0]=='#') file[0] = '$';
  bool explicit_link = true;
  if (strcmp(file,"$self")==0) {// self-linking case!
// *ch 1.2.9 patch
#ifdef _WIN32
    file = Main::uc_exec_name();
#else
    static char empty_self[] = "";
    file = empty_self;
#endif
	explicit_link = ! sNoSelfLink;
  } else
    if (strcmp(file,"$caller")==0) {
      file = NULL;
    }
  // *add 1.1.2 Try looking in the UC_LIB directory!
   string sfile = file ? file : "$caller";
   if (explicit_link) {
     s_lib = load_library(file);
     if (!s_lib) {
	   sfile = Main::uc_lib_dir() + sfile;
	   s_lib = load_library(sfile.c_str());
	 }
   } else s_lib = IMPLICIT_LINK;
   lib_list.push_back(s_lib);
   if (!s_lib) return false;
// *fix 1.1.4 Subsequent #lib where the loaded DLL is the same - don't reset!
   if (sfile != s_file) {
	   Import::reset(true);
	   s_file = sfile;
   }
 }
 return true;
}

string get_current_lib_file()
{ return s_file; }

void unload_library(Handle hlib)
{
    set_dll_handle(hlib);
	Import::reset(false);
    if (hlib != IMPLICIT_LINK && hlib != NULL) {
        free_library(hlib);
        cleanup_ordinal_lookup();
    }
}

// *fix 1.2.4 if passed NULL (i.e. no current DLL _importing_ taking place)
// this function will try to unload the last handle loaded.
void unload_lib(Handle hlib)
{
  if (hlib == NULL) {
    hlib = lib_list.back();
  }
  unload_library(hlib);
  lib_list.remove(hlib);
  s_lib = NULL;
}

void *get_dll_handle() { return (void *)s_lib; }

void set_dll_handle(void *dl)
{
	s_lib = (Handle)dl;
}

// Looking up DLL entries through legacy ordinal/address maps or UC3 symbols.
typedef std::map<string,uintptr_t> SIMap;
static SIMap *s_ord_lookup;
static bool s_lookup_is_ordinal;
static bool s_lookup_is_symbol;

bool using_ordinal_lookup()
{ return s_ord_lookup != NULL; }

uintptr_t lookup_ordinal(const char *name)
{
    SIMap::iterator simi = s_ord_lookup->find(name);
    if (simi != s_ord_lookup->end()) return simi->second;
    else return 0;
}

// *change 1.2.2 (Eric) imp file format is now more relaxed;
// (a) ignore any line that begins with a "# ", and
// (b) everything after the mangled name
// *add 1.2.4 Will look in UC LIB directory a la .DLLs
// *add 1.2.4 UC2 type means that value is not ordinal but address
// UC3 stores symbol names only and resolves them in the current process.
uintptr_t convert_ordinal(char *buf)
{
  if (s_lookup_is_ordinal)
    return static_cast<uintptr_t>(strtoull(buf,NULL,10));
  return static_cast<uintptr_t>(strtoull(buf,NULL,16));
}

bool lookup_is_ordinal()
{ return s_lookup_is_ordinal; }

static string demangled_function_name(const char *symbol)
{
#ifdef __GNUC__
  int status = 0;
  char *demangled = abi::__cxa_demangle(symbol,NULL,NULL,&status);
  if (status != 0 || !demangled) {
    free(demangled);
    return "";
  }
  char *arguments = demangled;
  while (*arguments && *arguments != '(') ++arguments;
  if (*arguments) *arguments = '\0';
  string result(demangled);
  free(demangled);
  return result;
#else
  return "";
#endif
}

const char *lookup_symbol_alias(const char *name)
{
  static string match;
  match = "";
  if (!s_lookup_is_symbol || !s_ord_lookup) return NULL;
  const string wanted = demangled_function_name(name);
  if (wanted == "") return NULL;
  for (SIMap::const_iterator entry = s_ord_lookup->begin();
       entry != s_ord_lookup->end(); ++entry) {
    if (demangled_function_name(entry->first.c_str()) == wanted) {
      if (match != "") return NULL; // An overloaded name is not a safe alias.
      match = entry->first;
    }
  }
  return match == "" ? NULL : match.c_str();
}

bool generate_ordinal_lookup(const char *index_file)
{
  string magic,compiler;
  char buf[1024];
  char name[1024];
  ifstream in;
  const bool self_manifest = strcmp(index_file,"self.imp") == 0 ||
                             strcmp(index_file,"uclr/self.imp") == 0;
  string sfile;
  if (self_manifest) {
    sfile = Main::uc_lib_dir() + "uclr/self.imp";
    in.open(sfile.c_str());
  } else {
    in.open(index_file);
    if (! in || in.eof()) {
      sfile = Main::uc_lib_dir() + index_file;
      in.open(sfile.c_str());
    }
  }
  if (! in || in.eof()) {
    cerr << "cannot find '" << (self_manifest ? sfile : string(index_file)) << "'\n";
    return false;
  }
  in >> buf;
  magic = buf;
  in >> buf;
  compiler = buf;
  if (magic != "UC1" && magic != "UC2" && magic != "UC3") return false;
  s_lookup_is_ordinal = magic == "UC1";
  s_lookup_is_symbol = magic == "UC3";
  if (! Import::set_scheme(compiler)) return false;
  delete s_ord_lookup;
  s_ord_lookup = new SIMap;
  // *fix 1.2.3a (Eric) Attempted to read ordinal twice
  while (! in.eof()) {
    buf[0] = '\0';
    in >> buf;
    if (*buf && *buf != '#') {
      if (s_lookup_is_symbol) {
        (*s_ord_lookup)[buf] = 0;
      } else {
        in >> name;
        (*s_ord_lookup)[name] = convert_ordinal(buf);
      }
    }
    in.getline(buf,sizeof(buf));
  }
  return true;
}

void cleanup_ordinal_lookup()
{
    delete s_ord_lookup;
    s_ord_lookup = NULL;
}

// *fix 1.2.3 Under Win32, it is a Bad Idea to try free the process handle.
void finis()
{
 uc_run_exit_functions();
#ifdef UCL_LIBFFI
 for(CallbackList::iterator callback = callback_list.begin(); callback != callback_list.end(); ++callback) {
     ffi_closure_free((*callback)->closure);
     delete *callback;
 }
 callback_list.clear();
 for(FFIAggregateMap::iterator aggregate = ffi_aggregate_types.begin();
     aggregate != ffi_aggregate_types.end(); ++aggregate)
     delete aggregate->second;
 ffi_aggregate_types.clear();
#elif defined(UCL_SYSV_X86_64)
 for(LegacyCallbackList::iterator callback = legacy_callback_list.begin();
     callback != legacy_callback_list.end(); ++callback) {
     munmap((*callback)->entry,(*callback)->allocation_size);
     delete *callback;
 }
 legacy_callback_list.clear();
#endif
 Handle process_handle = get_process_handle();
 HandleList::iterator ili;
 for(ili = lib_list.begin(); ili != lib_list.end(); ++ili) {
      Handle lib = *ili;
      if (lib != process_handle)
         unload_library(lib);
 }
}

CALLFN lookup_self_link(PClass pc,const string& name) { return NULL; }



}  // namespace Builtin
