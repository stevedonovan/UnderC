# Language support

## Summary

UnderC is not a conforming implementation of any complete ISO C or C++
standard. It recognizes a useful C++98-era dialect with extensions and offers a
`.c` mode for a C-like subset. “Built as GNU C++98” refers to UnderC's own
host-language build and must not be confused with interpreted-language
conformance.

This assessment describes UnderC 1.5.0 and is based on `src/build/parser.y`,
the keyword table in `src/keywords.cpp`, the built-in constants installed in
`src/common.cpp`, preprocessing behavior in `src/uc_tokens.cpp`, the bundled
headers under `include/underc/uclstl`, and the registered regression suite in
`src/CMakeLists.txt`.

## C++ dialect

The broad baseline is a subset of ISO C++98. Implemented areas include basic
types and expressions, declarations, functions, overloads and default
arguments, classes, access control, single inheritance, virtual methods,
construction and destruction, operator overloading, namespaces and `using`
declarations, references, exceptions, casts, and limited class, function, and
member templates.

Scalar and lexical compatibility with ISO C++98 covers:

- `true` and `false` as directly stored `bool` constants.
- A built-in `NULL` compatibility macro.
- The `signed` integer spellings (`signed`, `signed int`, `signed char`,
  `signed short`, `signed long`).
- `wchar_t`, as a typedef for the Windows-width unsigned short rather than a
  distinct native type.
- The alternative operator spellings `and`, `and_eq`, `bitand`, `bitor`,
  `compl`, `not`, `not_eq`, `or`, `or_eq`, `xor`, and `xor_eq`, supplied as
  token substitutions that reuse the symbolic-operator grammar.

Templates are supported in class, function, and member form; member templates
are usable when defined in-class. Exception handling covers `throw`, `try`,
innermost-first `catch` matching, catch-by-base, and `catch(...)`.

It is not full C++98. The template implementation is source-substitution based
and instantiates more eagerly than ISO C++; out-of-class member-template
definitions are unsupported, and `>>` closing two template argument lists is a
syntax error — the space in `map<string, vector<string> >` is required. Only a
single base class is accepted, so there is no multiple or virtual inheritance.
Of the RTTI-oriented operations, the four named casts including `dynamic_cast`
are available, but `typeid` is not. The bundled library is deliberately small
and not a conforming C++ standard library.

`mutable`, `inline`, `typename`, `register`, and `volatile` are discarded by
the preprocessor for parsing compatibility rather than implemented, so
`volatile` in particular does not retain its required semantics. The remaining
ISO C++98 words outside the dialect — `asm`, `auto`, `export`, and `typeid` —
are reserved and rejected rather than silently accepted as ordinary
identifiers. Modern C++ features — such as `nullptr`, standard `auto`
deduction, `decltype`, `constexpr`, lambdas with standard syntax, rvalue
references, variadic templates, concepts, modules, and coroutines — are not
supported. The similarly named `__lambda` facility is an UnderC extension, not
a standard C++ lambda, as are `typeof` and `__declare`.

## C dialect

Loading a `.c` file enables C mode, which can also be toggled with the `C`
interpreter option. It gives structure/union/enum tags their C namespace
behavior and permits C enum/int matching, but does not select an independent
ISO C grammar. Consequently, the safe description is “C-like, C90-based subset
with selected extensions,” not “C90 support.” No later ISO C edition is fully
supported either.

Useful supported areas include arithmetic and pointer expressions, arrays,
structures, unions, enums, typedefs, functions and prototypes, variadic
function declarations with `...`, control flow, aggregate brace
initialization, `NULL`, the `signed` integer spellings, and a traditional
macro/include/conditional preprocessor.

Known missing or incomplete areas include:

- Fundamental C90 coverage: `auto` is not a declaration keyword; `register` and
  `volatile` are stripped; old-style function definitions and the full
  declarator grammar are absent. Bit-fields and unusual nested declarators
  should not be assumed to be complete.
- C99: no `long long`, `long double`, `_Bool`, `_Complex`, `_Imaginary`,
  `restrict`, designated initializers, compound literals, variable-length or
  flexible arrays, variadic macros, or standard `inline` semantics. Some C99
  conveniences, such as `//` comments and declarations in loop/block scope,
  are accepted independently.
- C11/C17: no `_Atomic`, `_Generic`, `_Static_assert`, `_Alignas`, `_Alignof`,
  standard thread-local storage, or complete anonymous member semantics.
- C23: no C23 keyword, type, attribute, preprocessing, or declaration model as
  a supported standard level.

## Bundled library

The interpreted pocket library lives under `include/underc/uclstl` and is the
interpreter's default include search root. It provides a compact `string`,
streams, `vector`, `list`, `map`, regular expressions, timers, exception
helpers, and persistence helpers, together with compatibility headers that
bind to the host C runtime.

Containers hold class types, including `vector<string>` at any size and nested
instantiations such as `map<string, vector<string> >`. `std::map` supports deep
copy construction, assignment, and return by value, along with `clear()`,
`empty()`, and `count()`.

The preprocessor and bundled headers are compatibility implementations, not
complete ISO library environments. Passing an UnderC program therefore proves
only compatibility with this interpreter, not conformance or portability to a
particular ISO language edition.
