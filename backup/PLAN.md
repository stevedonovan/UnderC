# Plan for ISO C90 conformance

## Objective

Make UnderC's `.c` language mode a conforming hosted implementation of
ISO/IEC 9899:1990 (C90), including the corrected requirements from the
applicable ISO defect reports. Preserve the historical C++ interpreter and
UnderC extensions, but keep them outside strict C90 mode.

Conformance means more than accepting representative syntax. The completed
implementation must:

- accept every strictly conforming C90 program within documented translation
  limits;
- diagnose every violation for which C90 requires a diagnostic;
- implement C90 execution semantics and observable behavior;
- provide all required hosted headers, types, macros, and library functions;
- define and document implementation-defined and locale-specific behavior;
- avoid defining `__STDC__` as `1` until all completion gates in this plan pass.

This plan does not include C95 amendments or C99-and-newer features. They may
remain extensions in non-strict mode if they do not alter strict C90 behavior.

## Current baseline

UnderC currently uses one C++-oriented lexer, parser, type system, and VM for
both `.c` and `.cpp` files. C mode changes structure/union/enum tag lookup and
enum conversion behavior, but it is not an independent ISO C implementation.

Useful C90-like facilities already exist: scalar arithmetic, pointers, arrays,
structures, unions, enums, typedefs, prototypes, `...` function parameters,
most statements, aggregate initialization, bit-field machinery, linkage
declarations, and a traditional preprocessor. These need specification-driven
tests before being counted as conforming.

Known gaps include:

- missing `signed` and `auto` keywords;
- `register` and `volatile` being discarded by preprocessing instead of
  represented and enforced;
- no old-style function definitions and incomplete declarator grammar;
- incomplete integer constant expressions, initializers, array handling,
  bit-fields, storage classes, linkage, and C namespace rules;
- C++ leakage into C mode, including `bool`, references, classes, overloads,
  namespaces, exceptions, templates, `new`/`delete`, C++ casts, and C++-only
  implicit conversions;
- fixed tokenizer/parser limits below or insufficiently documented against
  the C90 translation limits;
- bundled headers and runtime functions that do not constitute the complete
  hosted C90 library.

Additional current language and runtime limitations previously documented in
the root README are tracked here so the README can remain a current usage
overview:

- The C++ dialect does not implement full ISO C++98 template or standard
  library semantics. Out-of-class member-template definitions are absent;
  `mutable`, `inline`, `typename`, and `volatile` are discarded rather than
  modeled with their standard meanings. Modern C++ language generations are
  outside the current dialect.
- A VM word narrower than the host pointer cannot represent the host address
  space and is therefore compile-check-only on that host.
- `UCL_DISABLE_NATIVE_ABI=ON` makes interpreted `int`, ordinary enum, and
  `long` objects use the VM width, so structures containing those fields are
  not compatible with native C/C++ layout.
- The portable CMake target covers the console implementation; the Windows
  GUI and graphics sources are not part of that target.
- Interpreted const/non-const container overloads are not distinguished
  reliably. VM-width `vector::front`/`back` value returns are unreliable, and
  generic-map lookup and mapped-value access are not validated for every type.
  The native `map<string,int>` specialization is disabled unless
  `UNDERC_USE_NATIVE_MAP_SPECIALIZATION` is defined.
- The native-call bridge has a finite supported signature/argument shape and
  narrower-VM runtime configurations cannot safely transport host pointers.

The detailed audit that motivated this work is in
[`LANGUAGE_SUPPORT.md`](LANGUAGE_SUPPORT.md).

## Design rules

1. Add an explicit language-dialect value rather than growing the existing
   `debug.c_mode` Boolean. At minimum distinguish `C90_STRICT`,
   `C90_EXTENSIONS`, and the existing C++ dialect.
2. Make `.c` select strict C90 for batch compilation. Provide an explicit CLI
   or `#opt` switch for historical permissive C behavior; do not silently
   accept C++ constructs in strict mode.
3. Share implementation code where semantics really match, but give C90 its
   own grammar entry points, constraint checks, and type-conversion policy.
4. Represent qualifiers and storage classes in the type/symbol model. Never
   implement a keyword by deleting it in the preprocessor.
5. Add a regression before fixing each defect. Keep positive compilation,
   runtime, required-diagnostic, and extension-rejection tests distinct.
6. Preserve interactive recovery, but never let interactive redeclaration
   rules weaken strict batch translation.
7. Treat native ABI interoperability as an implementation-defined property;
   C abstract-machine behavior must not accidentally depend on the host C++
   compiler's choices.

## Phase 0: establish the conformance harness

- Obtain a legally usable copy of the C90 specification and create a clause
  matrix covering lexical elements, syntax, constraints, semantics, library,
  diagnostics, environment, and translation limits. Record defect-report
  interpretations used by the project.
- Extend CTest with four test classes:
  `c90-compile-pass`, `c90-runtime-pass`, `c90-diagnostic-pass`, and
  `c90-reject-extension`.
- Make the runner verify exit status, standard output, standard error, and
  diagnostic source location. A required-diagnostic test passes only when a
  diagnostic is emitted, not merely when execution later fails.
- Add differential tests against at least two established C90 compilers in
  strict/pedantic mode. Use these to find disagreements, not as the normative
  definition of C90.
- Integrate an independently maintained C90 validation suite if its licence
  permits redistribution. Keep any non-redistributable suite in an optional
  CI job with documented setup.
- Add sanitizer builds for the host implementation and deterministic VM tests
  for both native ABI and experimental object-layout configurations.
- Establish a baseline report with every matrix row marked `pass`, `fail`,
  `untested`, `implementation-defined`, or `not applicable`.

Exit criteria:

- The harness can prove acceptance, rejection, runtime output, and required
  diagnostics independently.
- Every C90 clause has an owner and at least one planned test.

## Phase 1: isolate the C90 front end

- Replace C/C++ keyword erasure in `src/uc_tokens.cpp` with dialect-aware token
  classification. Add tokens for `auto`, `register`, `signed`, and `volatile`.
- In strict C90 mode, reserve exactly the C90 keywords and reject C++ keywords
  where the grammar cannot interpret them as ordinary C identifiers.
- Split the grammar at the translation-unit, declaration, declarator,
  statement, and expression levels. A dedicated `c90_translation_unit` should
  reuse only productions whose constraints and semantics match C90.
- Implement all four C namespaces correctly: labels; tags; structure/union
  members; and ordinary identifiers. Preserve their distinct scopes and
  linkage behavior.
- Separate interactive module reload/redefinition policy from strict
  translation-unit symbol rules.
- Ensure parser errors unwind all declaration, scope, tag, parameter, and
  initializer state before another interactive translation starts.

Exit criteria:

- No C++-only construct is accepted in strict C90 mode unless C90 treats its
  spelling as an identifier.
- Existing C++ regressions continue to pass unchanged.
- Parser generation has no unclassified conflicts in the new C90 grammar.

## Phase 2: implement the complete C90 declaration model

- Represent and validate storage-class specifiers: `typedef`, `extern`,
  `static`, `auto`, and `register`, including where each is permitted and when
  combinations are invalid.
- Represent `const` and `volatile` independently at every pointer-indirection
  level. Enforce qualification conversions, modifiable-lvalue rules, and
  volatile accesses in code generation.
- Implement all valid C90 type-specifier combinations, including `signed`,
  `signed int`, `signed char`, `unsigned` forms, and `long double`. Reject
  invalid duplicates and combinations with a required diagnostic.
- Replace the current declarator shortcuts with the complete recursive C90
  declarator and abstract-declarator grammar: pointers, arrays, functions,
  parenthesized declarators, and arbitrary valid nesting.
- Support prototype and old-style function definitions, identifier lists,
  default argument promotions, and compatible-type/composite-type rules.
- Implement tentative definitions, internal/external/no linkage, declaration
  compatibility, incomplete types, and completion of arrays and tagged types.
- Complete structure/union layout, named and unnamed bit-fields, zero-width
  bit-fields, alignment, member namespace, flexible prohibition, and recursive
  completeness constraints.
- Complete enumeration constraints and C90-compatible enum representation.
- Remove the present one- or two-dimensional array shortcuts and support every
  fixed-size C90 array rank with correct element type and layout.

Exit criteria:

- Every declaration and declarator syntax/constraint row in the clause matrix
  has positive and negative coverage.
- Type compatibility is symmetric, deterministic, and tested across separate
  declarations and translation units.

## Phase 3: expressions, conversions, and constant evaluation

- Implement the C90 integer model explicitly: ranks, signedness, integral
  promotions, usual arithmetic conversions, representability, and conversion
  of constants with decimal/octal/hexadecimal bases and `U`/`L` suffixes.
- Audit character constants, string literals, escape sequences, adjacent
  string concatenation, floating constants, and `sizeof` result/type.
- Complete lvalue, modifiable-lvalue, function/array conversion, pointer
  compatibility, null pointer constant, conditional operator, assignment, and
  function-call constraints.
- Replace limited constant folding with a C90 integral constant-expression
  evaluator used consistently by enum values, case labels, bit-field widths,
  array bounds, and preprocessor expressions.
- Implement initialization for scalars, arrays, structures, and unions,
  including brace elision, zero initialization, string-to-character-array
  rules, excess-element diagnostics, and static-storage constant-expression
  requirements.
- Verify operator precedence, associativity, short-circuiting, sequence points,
  side effects, signed/unsigned behavior, shifts, division/remainder, and
  pointer arithmetic. Preserve undefined behavior as undefined, but never let
  host implementation accidents corrupt the interpreter itself.

Exit criteria:

- Expression results match the documented UnderC implementation choices and
  C90 semantics for all defined cases in the matrix.
- Constraint violations reliably produce source-located diagnostics.

## Phase 4: statements, functions, and program execution

- Validate all C90 statement grammar and constraints: labels, compound
  statements, expression statements, selection, all loops, `goto`,
  `continue`, `break`, and `return`.
- Enforce C90 declaration placement within a block in strict mode. Declaration
  after statement and declaration in a `for` initializer may remain extensions
  only in permissive mode.
- Implement block, function, prototype, and file scope precisely, including
  label function scope and parameter scope.
- Complete function calling for prototyped, unprototyped, old-style, and
  variadic functions, with the correct promotions and return conversions.
- Implement static, automatic, and allocated storage duration; initialization
  before program start; recursive calls; and cleanup at normal termination.
- Support multiple translation units with correct external linkage, tentative
  definition coalescing, and one program-wide namespace. Define how `#l`,
  reload, and interactive execution map onto that model without weakening
  batch conformance.
- Audit `main` forms, `argc`/`argv`, environment startup, `exit`, `atexit`, and
  return-from-`main` behavior.

Exit criteria:

- Multi-file test programs link and execute with C90-compatible behavior.
- All statement, scope, linkage, storage-duration, and function-call matrix
  rows pass.

## Phase 5: complete preprocessing and translation phases

- Implement the C90 translation phases in the required order: source character
  mapping and line splicing, comment replacement, preprocessing tokens,
  directive execution and macro expansion, string-literal concatenation, and
  final token conversion/translation.
- Complete object-like and function-like macro replacement, argument
  prescan/rescan, recursion suppression, `#`, `##`, empty replacement lists,
  whitespace behavior, and diagnostics. Do not add variadic macros to strict
  C90 mode.
- Complete `#if` integer expressions and `defined`, conditional nesting,
  `#include`, `#line`, `#error`, and implementation-defined `#pragma`
  behavior. Unknown directives must follow C90 diagnostic requirements.
- Define the required predefined macros with correct forms and values. Keep
  UnderC-specific macros reserved and documented.
- Remove unsafe fixed buffers where possible. Where translation limits remain,
  meet or exceed every C90 minimum and diagnose exhaustion without memory
  corruption.
- Test trigraphs, backslash-newline splicing, comments, header names,
  preprocessing numbers, universal source input policy, and source/output line
  tracking. C++ `//` comments may be a permissive extension but must not be
  treated as comments in strict C90 mode.

Exit criteria:

- The preprocessing clause matrix and minimum translation-limit tests pass.
- Macro expansion is deterministic and memory-safe under sanitizer builds.

## Phase 6: provide the complete hosted C90 library

- Inventory every required C90 header and public name. Implement or correctly
  bridge: `assert.h`, `ctype.h`, `errno.h`, `float.h`, `limits.h`, `locale.h`,
  `math.h`, `setjmp.h`, `signal.h`, `stdarg.h`, `stddef.h`, `stdio.h`,
  `stdlib.h`, `string.h`, and `time.h`.
- Match required declarations, macro/function dual forms, types, qualifiers,
  return values, error behavior, and namespace visibility. Remove incompatible
  placeholder declarations.
- Implement `va_list` and variadic access according to the VM call-frame ABI,
  rather than assuming the host's `va_list` representation.
- Define `errno`, floating-point characteristics, integer limits, `size_t`,
  `ptrdiff_t`, `clock_t`, `time_t`, `FILE`, `fpos_t`, signals, locale state,
  and multibyte conversion behavior consistently with the interpreter object
  model.
- Complete formatted I/O conversion parsing and semantics, including widths,
  precision, lengths, assignment suppression, counts, errors, and stream state.
- Audit all memory/string functions for overlap, bounds, unsigned-character
  comparison, null termination, and return-pointer behavior.
- Implement file positioning, buffering, temporary files, rename/remove,
  environment access, sorting/searching, random numbers, numeric conversion,
  time/calendar functions, nonlocal jumps, and signal behavior.
- Document any permitted implementation-defined library behavior and the
  supported locale/environment model.

Exit criteria:

- Every required hosted header compiles alone and in every pairwise
  combination.
- Every required public library facility has declaration and behavioral tests.
- The independent library-validation suite passes without exclusions other
  than documented C90 latitude.

## Phase 7: diagnostics and implementation documentation

- Create one stable diagnostic path carrying severity, file, line, column,
  clause/test identifier, and recovery action.
- Ensure every syntax error and constraint violation produces at least one
  diagnostic. Do not count crashes, linker failures, or unrelated follow-on
  errors as the required diagnostic.
- Document all implementation-defined behavior required by C90, including:
  character set and signedness, integer sizes/ranges and representations,
  floating-point model, right shift, conversions, structure layout and
  alignment, bit-fields, enum representation, identifiers and external-name
  significance, `NULL`, `size_t`, signals, files, locale, environment, and
  resource limits.
- Document unspecified and undefined behavior that UnderC deliberately detects
  as an extension, such as pointer/range checking, without promising a
  diagnostic that C90 does not require.
- Publish the conformance mode, extensions mode, effective translation limits,
  required invocation, and any environmental dependencies in the root README.

Exit criteria:

- The implementation-defined behavior document has no unresolved placeholders.
- The diagnostic suite verifies every `shall` constraint represented in the
  clause matrix.

## Phase 8: compatibility, fuzzing, and release qualification

- Run all existing C++ and migration regressions after every phase. Changes to
  C90 must not silently alter the historical `.cpp` dialect.
- Add lexer, preprocessor, declarator, initializer, and expression fuzzers.
  Seed them with minimized conformance cases and run host ASan/UBSan builds.
- Test interactive use, batch use, static/shared library builds, native ABI
  mode, and the experimental VM-width object model. Only matching-width builds
  may be used for runtime conformance claims.
- Run the full C90 matrix on each supported host/compiler combination. Record
  failures and implementation-defined differences as release artifacts.
- Have an independent reviewer audit the matrix against the normative C90
  text and inspect every waived or implementation-defined test.
- Update `README.md`, `HISTORY.md`, and `LANGUAGE_SUPPORT.md` only after the
  evidence supports a stronger claim.

Exit criteria:

- No sanitizer failure, crash, hang, or parser-state leak remains in the
  conformance corpus or fuzz regression set.
- Existing C++ tests pass, or every intentional compatibility change is
  versioned and documented.

## Final conformance gate

UnderC may advertise hosted C90 conformance and define `__STDC__` as `1` only
when all of the following are true:

1. Every applicable clause-matrix entry is passing; no entry is `untested`.
2. All required syntax, constraint, semantic, preprocessing, environment, and
   library tests pass in a clean build.
3. The independent validation suite has no unexplained failure.
4. Translation limits meet or exceed every C90 minimum and are documented.
5. Every implementation-defined choice required by C90 is documented and
   matches runtime behavior.
6. Strict mode rejects or diagnoses extensions where accepting them would
   change the meaning of a strictly conforming program.
7. The complete regression suite passes on every platform for which the
   conformance claim is made.

Until that gate is reached, documentation must continue to call the C
interpreter a C90-like subset and publish the current matrix rather than a
conformance claim.

## Recommended implementation order

Work in narrow vertical slices rather than completing an entire subsystem
without executable evidence:

1. Harness and clause matrix.
2. Strict dialect selection and C++ rejection.
3. Keywords, declaration specifiers, and qualifiers.
4. Recursive declarators and function-definition forms.
5. Type compatibility, conversions, and constant expressions.
6. Initializers, aggregates, bit-fields, and arrays.
7. Scope, linkage, storage duration, and multi-file programs.
8. Translation phases and preprocessor.
9. Hosted library, one header family at a time.
10. Diagnostics, implementation documentation, fuzzing, and final validation.

Each slice is complete only when its positive, runtime, diagnostic, and
extension-boundary tests are committed with the implementation.
