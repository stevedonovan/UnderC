# UnderC 64-bit Modernization Plan

## Goal

Remove the remaining 32-bit and x86-specific architectural assumptions from
UnderC while preserving its C++98-era interpreted language and existing public
embedding behavior. A completed modernization should allow the maintained
runtime, reflection interface, native-call bridge, and callback paths to work
correctly on supported 64-bit hosts without pointer truncation, 32-bit x86 code
generation, or stale fixed-width layout descriptions.

This work does not require runnable 16- or 32-bit VM words on a 64-bit host.
Such configurations may remain compile-only checks unless a separate design
provides a pointer-handle representation that does not narrow host addresses.

## Current baseline

The normal build already defaults `UNDERC_VM_BITS` to the host pointer width,
uses pointer-sized VM transport on a 64-bit host, and uses the host ABI widths
for interpreted `int`, `long`, enum, and pointer objects. Default-on libffi
handles ordinary scalar, pointer, and reference calls into native code.

The remaining legacy behavior is concentrated in:

- callbacks and native stubs generated from interpreted functions;
- native C++ class imports and object-by-value calls;
- bit-field and class layout;
- the public UCRI bytecode representation;
- fixed-width metadata and offsets;
- old compiler name-mangling and Windows-only compatibility code.

## Phase 1: Establish the supported ABI contract

Before changing runtime behavior, document and enforce the configurations that
are expected to execute correctly.

### Implementation

- Define a runtime invariant that `sizeof(VMWord) >= sizeof(void *)` whenever
  interpreted code is executed.
- Add a configure-time or initialization-time failure for a narrower VM word,
  while retaining narrower configurations as explicitly named compile-only
  checks if they remain useful.
- Document the supported host architectures and native ABIs. Initially this
  should cover the platforms exercised by CI rather than claiming arbitrary
  compiler ABI compatibility.
- Treat `UCL_LIBFFI=OFF` as legacy mode. Either restrict it to verified targets
  or remove it after the libffi paths cover all supported calls.
- Record which public interfaces are stable. In particular, distinguish the C
  embedding API in `ucdl.h`/`ucembed.h` from the implementation-facing UCRI
  structures in `ucri.h`.

### Acceptance criteria

- Unsupported pointer-narrowing configurations fail clearly before execution.
- README and CMake option descriptions agree about runnable configurations.
- CI includes the default 64-bit native-ABI build and any intentionally
  retained compatibility builds.

## Phase 2: Replace the x86 callback generator

The highest-risk remaining component is `generate_native_stub()` in
`src/directcall.cpp`. It emits raw 32-bit x86 machine code and assumes registers
and stack behavior such as `eax`, `ecx`, and `esp`.

### Implementation

- Introduce a callback descriptor containing the interpreted `Function`, its
  signature, method/static state, calling convention, and lifetime state.
- Generate native callbacks with libffi closures (`ffi_closure_alloc`,
  `ffi_prep_closure_loc`) rather than handwritten machine code.
- Marshal callback arguments using the same type mapping used for calls into
  native code. Consolidate the mapping so native calls and callbacks cannot
  drift apart.
- Support hidden object pointers for methods without assuming an x86
  `thiscall` register.
- Return scalar, pointer, reference, and floating-point results according to
  libffi's ABI description.
- Track closure ownership and release executable closure memory during
  interpreter shutdown or function invalidation.
- Route `uc_compile_fn()`, `XFunction::fun()`, interpreted virtual-method
  exports, and every other native callback consumer through the new closure
  implementation.
- Remove the x86 emitter helpers and their fixed four-byte immediates after all
  callers have migrated.

### Acceptance criteria

- A host can call an interpreted free function through a native function
  pointer on every supported 64-bit platform.
- A host can call an interpreted non-static method through a generated callback
  with the correct object pointer.
- Integer, pointer, float, double, and mixed-argument callback tests pass.
- Callback tests cover zero arguments, more than six arguments, and recursive
  host/interpreter calls.
- AddressSanitizer and UndefinedBehaviorSanitizer report no callback lifetime,
  alignment, or calling-convention faults.

## Phase 3: Complete ABI-aware native calls

The libffi dispatcher currently sends native functions returning C++ objects
through `legacy_callfn()`. Native C++ class imports therefore retain historical
compiler-specific calling conventions.

### Implementation

- Separate portable C ABI interoperability from compiler-specific C++ ABI
  interoperability in the import model and diagnostics.
- Add libffi structure descriptions for supported plain structs passed and
  returned by value.
- Replace size-based guesses such as `t.size() < 3*sizeof(int)` with explicit
  ABI classifications or libffi aggregate descriptions.
- Model hidden return storage explicitly where the selected ABI uses an sret
  pointer.
- Model object pointer, constructor, destructor, and method calls through a
  per-ABI adapter rather than scattered `cdecl`, `stdcall`, and `thiscall`
  flags.
- Limit native C++ imports to ABI adapters that are implemented and tested.
  Reject unsupported class signatures instead of silently using the legacy
  bridge.
- Decide whether non-trivial objects passed or returned by value are in scope.
  If they are not, expose pointer/reference-based interop as the supported
  alternative and diagnose by-value declarations.
- Remove the six-argument and word-only fallback dispatcher once libffi covers
  every supported signature, or isolate it behind an explicitly unsupported
  legacy build option.

### Acceptance criteria

- Portable C functions can pass and return supported aggregates by value.
- Supported native C++ methods, constructors, and destructors work on each
  declared ABI.
- Unsupported object signatures produce deterministic load-time diagnostics.
- No default 64-bit execution path reaches `legacy_callfn()`.

## Phase 4: Make object and bit-field layout ABI-aware

Class layout is currently produced by a custom allocator with historical
four-byte bit-field allocation and special-case double alignment. This can
diverge from native compiler layout even when primitive widths are correct.

### Implementation

- Introduce a target-layout description containing primitive sizes and
  alignments, pointer alignment, aggregate alignment, and bit-field rules.
- Replace `class_dword_align` and `Allocator::dword_align()` terminology with
  byte alignment expressed by the target-layout description.
- Track both size and alignment for every interpreted type.
- Place fields using `align_up(offset, field_alignment)` and round aggregate
  size to aggregate alignment.
- Implement bit-field allocation units according to the selected ABI,
  including declared base type, zero-width fields, packing boundaries, and
  overflow into the next allocation unit.
- Make base-class placement, virtual-table pointer placement, arrays, unions,
  and nested aggregates use the same layout engine.
- Keep any historical packed layout only as an explicit compatibility mode,
  not as an implicit default.
- Expose size, alignment, and field offset through tests or reflection so layout
  can be compared directly with host-compiled equivalents.

### Acceptance criteria

- Interpreted and host-compiled test structures have matching `sizeof`,
  alignment, and member offsets for supported layouts.
- Tests cover mixed-width fields, pointers, doubles, arrays, inheritance,
  unions, packing, and bit-fields crossing allocation-unit boundaries.
- Native functions can safely consume pointers to supported interpreted plain
  aggregates.

## Phase 5: Repair the UCRI bytecode interface

`XInstruction` in `src/ucri.h` still advertises a packed 32-bit instruction
with an 8-bit opcode and 22-bit data field. The runtime instruction is now
native-sized, so `XFunction::pcode()` can expose an incompatible view.

### Implementation

- Stop returning runtime instruction memory as `XInstruction *` unless the
  public type is exactly the runtime representation.
- Prefer an opaque instruction iterator or snapshot API with accessors for
  opcode, address mode, operand kind, signed value, and pointer value.
- Represent pointer operands as `uintptr_t` or opaque handles rather than
  integer offsets.
- Add an API version or structure-size field if a plain C-compatible record is
  retained.
- Update disassembly, profiling, breakpoint, and external reflection consumers
  to use the same accessor layer.
- Remove comments and public constants that still promise 22-bit direct
  offsets or 32-bit instruction records.

### Acceptance criteria

- UCRI clients can inspect bytecode correctly on 32- and 64-bit hosts without
  casting internal instruction storage.
- Pointer-bearing instructions round-trip without truncation.
- The public representation remains compatible across optimization levels.

## Phase 6: Widen offsets, sizes, and frame metadata

Symbol offsets, allocator results, object sizes, and frame word counts are
widely stored as `int`. This does not normally truncate host pointers now, but
it limits data spaces and preserves assumptions from the old fixed 32-bit
model.

### Implementation

- Inventory every field named or used as an address, byte offset, size, slot
  count, instruction offset, or allocation result.
- Use `size_t` for byte sizes and allocation counts, `ptrdiff_t` for signed
  byte offsets, and a dedicated VM slot-count type for stack/frame counts.
- Widen `Entry::size`, allocator offsets, table offsets, class member offsets,
  `FBlock` frame counts, line-number instruction offsets, and matching UCRI
  accessors where required.
- Keep serialized or externally visible formats fixed-width only when their
  bounds are validated explicitly.
- Replace arithmetic that mixes byte counts, VM-word counts, and element counts
  with named conversion helpers.
- Add checked conversions wherever an external API must continue returning
  `int` for compatibility.

### Acceptance criteria

- The build is clean under conversion and sign-conversion diagnostics selected
  for the migration.
- Tests exercise offsets above the old 22-bit boundary without corruption.
- Size computations reject overflow before allocation or code generation.
- Byte offsets and VM slot counts are not interchangeable without an explicit
  conversion.

## Phase 7: Decouple type metadata from a packed 32-bit word

`Type` is deliberately encoded in one `uint32_t`. This is not currently a host
pointer truncation bug, but it imposes old limits, including two bits of pointer
depth and a 16-bit auxiliary table index.

### Implementation

- Replace raw `uint32_t` comparison and zeroing through `reinterpret_cast`
  with ordinary field initialization and semantic equality.
- Expand pointer depth to a checked integer type.
- Replace the 16-bit auxiliary index with an appropriately sized stable type or
  direct interned type identifier.
- Add explicit hashing if compact type keys are needed for maps or caches.
- Preserve the current type semantics without relying on compiler bit-field
  layout or object aliasing behavior.
- Add tests for deeply nested pointers and more type-table entries than the
  current 16-bit index permits.

### Acceptance criteria

- `Type` behavior no longer depends on occupying exactly four bytes.
- Type equality is semantic and passes strict-aliasing/UB sanitizers.
- Pointer depth and type-table capacity have documented, checked bounds.

## Phase 8: Isolate historical platform subsystems

Several optional areas retain Win32 types, structured exceptions, old compiler
name mangling, and historical GUI/thread behavior. They should not obscure the
architecture guarantees of the maintained runtime.

### Implementation

- Put Windows GUI, Win32 thread wrappers, and structured-exception translation
  behind explicit platform targets and feature options.
- Audit Windows handles and message parameters for `LONG`/`DWORD` versus
  pointer-sized `LONG_PTR`, `DWORD_PTR`, `WPARAM`, and `LPARAM` usage.
- Replace or scope the GCC 2/MinGW-era name-mangling implementation. Prefer
  explicit `extern "C"` exports for portable interop.
- Define named C++ ABI manglers only for compiler versions that are tested.
- Mark unvalidated class-import, hardware-fault, GUI, and native-callback
  facilities experimental until their platform tests pass.
- Remove obsolete architecture comments once they no longer describe code.

### Acceptance criteria

- The maintained console/library build contains no dependency on Win32-only
  assumptions on non-Windows systems.
- A 64-bit Windows build passes handle-width and callback tests.
- Native imports either use a verified mangling/ABI adapter or require explicit
  unmangled symbols.

## Testing and CI strategy

Add tests with each phase rather than treating testing as a final migration
step.

- Run default 64-bit builds on GCC and Clang with libffi enabled.
- Add a 64-bit Windows compiler job when Windows support is claimed.
- Run AddressSanitizer and UndefinedBehaviorSanitizer builds.
- Add `-Wconversion`, `-Wsign-conversion`, and pointer/integer cast diagnostics
  selectively during offset migration.
- Retain 16- and 32-bit VM compile checks, but label them non-runnable on a
  wider host.
- If a real 32-bit runner is available, test a native 32-bit host separately
  from a narrowed VM running inside a 64-bit process.
- Build tests around ABI matrices: scalar calls, pointers/references, variadic
  calls, aggregates, methods, callbacks, and object returns.
- Compare interpreted layout against small host-compiled probe structures.
- Test the installed embedding and UCRI headers, not only in-tree internals.

## Recommended delivery order

1. Enforce the pointer-width runtime invariant and document supported ABIs.
2. Replace generated x86 callbacks with libffi closures.
3. Eliminate default-path use of the legacy native dispatcher.
4. Introduce the target layout engine and correct bit-fields/classes.
5. Replace the stale UCRI instruction representation.
6. Widen offsets, sizes, and frame counters.
7. Redesign packed `Type` metadata.
8. Validate or isolate historical Windows and name-mangling subsystems.

Each phase should land with its tests and documentation. Compatibility shims
may remain temporarily, but they should have explicit names, build flags, and
removal criteria so they cannot silently become the default path again.

## Completion criteria

The modernization is complete when:

- no supported 64-bit execution path emits or executes 32-bit x86 callback
  code;
- native calls and callbacks use ABI-aware marshalling;
- unsupported C++ object interoperability is rejected explicitly;
- interpreted aggregate layout matches the declared host ABI;
- reflection does not expose a false 32-bit instruction representation;
- pointer-bearing values use pointer-width or opaque representations;
- byte sizes and offsets are not constrained by legacy `int` storage without a
  documented external-format reason;
- the default build passes its runtime, embedding, ABI, layout, and sanitizer
  test suites on every supported 64-bit platform.
