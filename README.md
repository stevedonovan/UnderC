# UnderC 1.5.4

## Credits
Initial work by Steve Donovan (https://github.com/stevedonovan).
Previous modifications where done by https://github.com/antirez, https://github.com/brynne8
1.3.0-current modifications where done by Louis Höfler (https://github.com/mathematechde, www.mathematech.de)
I hereby want to thank the initial developers for their amazing work!

See LICENSE for license.

## Motivation
 - In the age of software that gets bloatet, working as a single developer got more harder. UnderC is a self contained library, able to be implemented by a single developer.
 - Big software companies have resouces for 100 developers, therefore software can only be maintained by a large ammount of developers. While complex software is the way to go for a use one for everything approach, it also has a big implementation complexity.
 - C++ is a hated and loved language but it shines in it's design philosophy for architecture compatibility compared to features.
 - Disabling features for a broader compatibility layer, making it able to be run on more SoC devices.

## Roadmap
- Further improvement of the api, seperating the library and consumers
- Further cleanup of the source repository.
- Further improvement of the build process. Using venv and a bootstrap underc removing cmake dependency alltogether.
- Further configuration and compilation options and better feature selection
- Implement more complete c/c++ standard
- arm/riscv/esp32 platform testing, embedded interop does only currently work on x86/x64. It would be a choice to only support libffi on those platforms. On esp32 you still need dram module.
- Migrate the interpreter to pure c, allthou there will be big hurdles to do so

## Alternatives
 - cling https://github.com/root-project/cling
 - cint https://github.com/kaisereagle/cint

## Overview
UnderC is an interactive C and C++ interpreter,
it parses source, compiles it to an internal p-code instruction stream, and executes that
stream immediately. Version 1.5.4 builds with current GCC/Clang and MSVC
toolchains, CMake, libffi, and 64-bit hosts.

## Language support

UnderC interprets its maintained C++98-era language dialect with extensions
and builds with GNU C++98. Files ending in `.c` activate C mode, which applies C
tag-name and enum behavior through the shared parser.

Supported C++98-era facilities include classes and structs, inheritance,
virtual functions, constructors and destructors, overloads, references,
namespaces, exceptions, RTTI-style casts, and templates.
UnderC also provides `typeof`, `__declare`, and `__lambda` extensions and
supports member templates. Standard scalar compatibility includes `true`,
`false`, `NULL`, `signed` integer spellings, a two-byte `wchar_t` alias, and
the alternative operator tokens (`and`, `or`, `not`, `bitand`, `bitor`,
`xor`, `compl`, and their assignment/equality forms). Other ISO C/C++98 words
remain reserved even when their semantics are outside this dialect.

## Features

- Interactive statement and expression evaluation with type-aware result
  display.
- Automatic interactive loading of the bundled class library from
  `$UC_HOME/lib/uclr/defs.h`, with a working-directory `defs.h` available
  as a local override.
- Compiled-in interactive (`#help`) and command-line (`--help`) help text, so
  no resource files are read at run time.
- A C embedding API, `uc_set_home_dir()`, that lets a host application point
  the interpreter at its runtime tree; the OS-specific logic that locates that
  tree lives in the host. `ucc` derives it from its own executable path.
- Source-file loading, unloading, cleaning, and reloading.
- Path-qualified source loads derive synthetic module-initializer names from
  the basename, without retaining the final directory separator.
- C and C++ declarations, functions, overloading, default arguments, classes,
  inheritance, access control, virtual methods, constructors, and destructors.
- ISO boolean/null constants, signed integer spellings, `wchar_t`
  compatibility, and alternative operator tokens.
- Namespaces, `using` declarations, typedefs, enums, references, pointers,
  arrays, operator overloading, templates, exceptions, and RTTI-style casts.
- An internal p-code compiler and virtual machine, with built-in staged
  bytecode optimization, optional one-instruction function inlining, and
  disassembly.
- A preprocessor supporting includes, macros, conditional compilation,
  `#warning`, `#error`, pragmas, and command aliases.
- Dynamic-library loading through `#lib` or `#pragma dlink`; the supported
  portable import surface is unmangled `extern "C"` functions.
- Built-in console, formatted and file I/O; string and memory operations;
  mathematics; allocation; environment and shell access; exit handlers;
  process pipes; file-access checks; and interpreter-control functions.
- A compact bundled library with strings, streams, containers, regular
  expressions, timers, exception helpers, and persistence helpers.
- A separated header layout: native consumer APIs live under
  `include/underc`, private native build headers remain under `include`, and
  the interpreted pocket STL/runtime library lives under
  `include/underc/uclstl` and is searched there by default.
- The native pocket-string API supports direct `const char *`
  comparison, equality, and inequality overloads and treats a null C-string
  constructor argument as an empty string.
- Interactive inspection of variables, functions, types, modules, and stack
  frames, plus disassembly, breakpoints, stepping, function tracing, pointer
  checking, and array-range checking.
- A C-compatible embedding API for live, two-way bindings between host scalar
  variables and interpreted names, plus reflection and native import APIs.
- Three installed consumers of the interpreter package: the `ucc` command-line
  front end, the `venv` virtual-environment launcher whose `.cvc` configuration
  files are C++ run by the embedded interpreter, and the `embed` binding
  example.
- Checked scalar native-call argument-slot marshalling for fixed and variadic
  libffi calls, including bool and enum constants in multi-argument calls.
- Aggregate return values from imported natives, resolved through the import
  scheme rather than through uninitialized function metadata.
- Whole-object value semantics: assignment between plain structs and return of
  a plain struct by value copy in the correct direction.
- Word-accurate local frame allocation: every local occupies its own slot,
  including locals narrower than a VM word and a scalar declared after an
  array.
- `new T[n]` constructs and `delete[]` destroys every element, so dynamic
  arrays of class type hold fully initialized objects, and the hidden
  method-table slot reserved by `new` matches the width the engine reads.
- Pocket-STL containers of strings, including `vector<string>` at any size,
  `std::map` copy construction, assignment, and return by value, and nested
  instantiations such as `map<string, vector<string> >`.
- Interpreted exception handling with pointer-width handler and thrown-object
  storage, innermost-first catch matching, catch-by-base, and `catch(...)`.
- A generated, address-free UCRI self-import manifest that resolves symbols in
  the running process and remains valid with PIE, ASLR, and 64-bit pointers.
- A libffi that can be named directly with `-DLIBFFI_INCLUDE_DIR` and
  `-DLIBFFI_LIBRARY` on every platform, ahead of the automatic search, and an
  installed CMake package that records the interpreter's dependencies by file
  path, so consumers need no pkg-config of their own.

## Requirements and build

The source tree builds the interpreter engine as an installable library, and
the `ucc` command-line interface, the `venv` launcher, and the `embed` example
as separate consumers of the installed package. It requires CMake 3.16 or
newer, a compiler with GNU C++98 support, and libffi on every host whose
native-call path needs it. The `venv` consumer additionally needs a C11 and a
C++14 compiler (its launcher core is plain C; one bridge file is C++). Readline
and curses
development packages are used by default on Unix; on Windows `UCL_USE_READLINE`
defaults to `OFF` and neither package is needed. GNU Bison (with its `yacc`
mode) is required only when the pre-generated parser under `src/gen` is absent;
a source tree that ships those files builds without bison or yacc installed.

Optional Libffi can be downloaded from github.com/libffi/libffi or https://github.com/mathematechde/libffi for cmake support.

Build, install, and consume the default static library with:

```sh
cmake -S src -B build-lib -DCMAKE_INSTALL_PREFIX=/tmp/underc
cmake --build build-lib
cmake --build build-lib --target selfimp
cmake --build build-lib --target install
cmake -S cli -B build-cli -DCMAKE_PREFIX_PATH=/tmp/underc \
  -DCMAKE_INSTALL_PREFIX=/tmp/underc
cmake --build build-cli
cmake --build build-cli --target install
```

This installs `libunderc`, its CMake package support, the consumer API in
`include/underc`, and the interpreted library in `include/underc/uclstl`, then
installs `ucc`. Compiler-private headers from the source tree are not
installed. The CLI locates the installed `FindUnderc.cmake` through either
`CMAKE_PREFIX_PATH` or `CMAKE_INSTALL_PREFIX`, so pointing only the install
prefix at the interpreter installation is enough. To build and consume the
shared library instead:

```sh
cmake -S src -B build-lib-shared -DUCL_SHARED=ON \
  -DCMAKE_INSTALL_PREFIX=/tmp/undercshared
cmake --build build-lib-shared
cmake --build build-lib-shared --target selfimp
cmake --build build-lib-shared --target install
cmake -S cli -B build-cli-shared -DUCC_SHARED=ON \
  -DCMAKE_PREFIX_PATH=/tmp/undercshared \
  -DCMAKE_INSTALL_PREFIX=/tmp/undercshared
cmake --build build-cli-shared
cmake --build build-cli-shared --target install
```

The explicit `selfimp` target uses `nm` and `awk` to generate the UCRI symbol
manifest at `lib/uclr/self.imp`. Set the `UNDERC_SELFIMP_OUTPUT` CMake cache
variable to choose another output path. The manifest contains symbol names,
not link-time addresses; UnderC resolves them in the current process at
runtime. Including `ucri.h` always autoloads the manifest from
`$UC_HOME/lib/uclr/self.imp`. The install step copies a generated manifest to
`lib/uclr` when it exists.

`UCL_` options and macros belong to the library; `UCC_` options and macros
belong to the command-line program. `UCL_SHARED` builds the shared-library
variant. To build the library without readline:

```sh
cmake -S src -B build-lib -DUCL_USE_READLINE=OFF
cmake --build build-lib
```

Native calls use libffi by default, providing ABI-correct scalar, pointer,
reference, floating-point, variadic, and dynamically sized fixed argument
lists. Native function pointers exported from interpreted functions are also
libffi closures and support free functions, methods, floating-point values,
argument lists beyond the register limit, and recursive host/interpreter
calls. Plain non-union aggregates use generated libffi structure descriptions
for arguments and returns. Non-trivial C++ objects and aggregates containing
bit-fields remain pointer/reference-only.

#### Finding libffi

Every platform accepts a libffi named by hand, and an explicitly named libffi
is used verbatim and never replaced by an automatically discovered copy:

```sh
cmake -S src -B build-lib \
  -DLIBFFI_INCLUDE_DIR=/opt/libffi/include \
  -DLIBFFI_LIBRARY=/opt/libffi/lib/libffi.a
cmake --build build-lib
```

Both variables must be given together; giving only one is a configuration
error. On Unix the automatic search runs when they are not set, in this order:
a libffi CMake package first (`find_package(libffi CONFIG)`, then
`find_package(ffi CONFIG)`, since ports differ in both package and target
name), then `pkg-config`, then a plain `find_path`/`find_library` sweep. All
three honour `CMAKE_PREFIX_PATH`. A libffi built into its own prefix often installs neither
a CMake package nor a `.pc` file, and the two variables above are then the way
to build against it. When nothing is found, the configuration error names all
three mechanisms and the variables to set. Windows has no `pkg-config`: there
the same two variables are used, normally filled in by
`find_path`/`find_library` from `CMAKE_PREFIX_PATH`.

Whichever mechanism finds it, libffi is recorded in the installed
`UndercTargets.cmake` as the library file itself, so a consumer of the
installed package links the same libffi without needing that mechanism —
`pkg-config`, in particular — available in its own project.

A prebuilt libffi carries no architecture marker that `find_library`
inspects, so CMake link-tests the candidate before accepting it. A libffi that
cannot be linked by the active toolchain — an x64 package offered to a 32-bit
build, say — is reported during configuration instead of surfacing as
unresolved `ffi_*` externals in the first executable that links. On a 64-bit
host this is a configuration error, because there is no built-in dispatcher to
fall back on; on a 32-bit host the build warns and uses the built-in 32-bit
native dispatcher, which handles scalar, pointer, and floating-point calls and
interpreted callbacks but not variadic natives or by-value aggregates.
`-DUCL_LIBFFI=OFF` selects the built-in dispatcher outright, and is supported
on a 64-bit host only for Linux System V x86-64.

`UCL_STRICT_CONVERSIONS` enables migration-oriented conversion warnings, and
`UCL_SANITIZERS` enables AddressSanitizer and UndefinedBehaviorSanitizer on
GCC/Clang builds.

### Windows (MSVC / nmake)

`build-cmake-vs2026-nmake-release.bat` in the repository root configures and
builds the interpreter library with a Visual Studio toolchain and the
`NMake Makefiles` generator:

```bat
cmake -G "NMake Makefiles" -B out-cmake-vs2026-nmake-x64r -S ./src ^
  -DCMAKE_PREFIX_PATH="<libffi-prefix>" ^
  -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="%APPDATA%"
cmake --build out-cmake-vs2026-nmake-x64r
cmake --build out-cmake-vs2026-nmake-x64r --target install
```

`. .\build-cmake-install.ps1` runs the full sequence from an already-set-up
developer PowerShell: it configures and builds `src/`, then the `cli/` and
`venv/` consumers, and installs `underc.lib`, `ucc.exe`, and `venv.exe` under
one prefix (`$env:DEP_DIR\underc-vc-x64r`), with libffi taken from
`$env:DEP_DIR\libffi-380-vc-x64r`.

The Windows build does not use `pkg-config`. libffi is located with
`find_path`/`find_library` from `CMAKE_PREFIX_PATH`, which must point at a
prebuilt libffi that provides `ffi.h` and an `ffi` or `libffi` import library;
`-DLIBFFI_INCLUDE_DIR` and `-DLIBFFI_LIBRARY` name it directly instead.
`UCL_USE_READLINE` defaults to `OFF` here because GNU readline and curses are
not part of a stock MSVC toolchain; the interpreter uses its plain console
line editor instead. The `selfimp` target requires `nm` and `awk` and is not
available in this configuration, so the generated `lib/uclr/self.imp` manifest
must be produced on a POSIX host if it is needed.

The `NMake Makefiles` generator takes its compiler from the environment, so
the developer prompt that runs the build chooses the target: an x64 prompt
produces a 64-bit interpreter and an x86 prompt a 32-bit one. Both are
supported, and `CMAKE_PREFIX_PATH` must point at a libffi of the same
architecture.

Sources that previously assumed 32-bit x86 MSVC have been made portable: the
fake-iostream library now streams
64-bit `VMWord`/frame-slot values, `Type::alignment()` uses standard `alignof`,
the 32-bit inline-assembler native-call thunk and x87 FP-exception fiddle are
restricted to `_M_IX86` (x64 uses the libffi path and the portable fallback),
and the exported embedding API in `ucembed.h` carries consistent DLL linkage.
Local UnderC script headers (`src/eh.h`, `src/winuser.h`) that shadowed the
real Windows SDK headers were removed from the compiler include path; the
canonical interpreted copies are under `include/underc/uclstl`. At runtime the
prebuilt `ffi.dll` must be on `PATH`.

The 32-bit path is maintained rather than merely retained. Its generated
callback stubs are placed in executable pages instead of on the no-execute C++
heap, their argument block is initialized before the interpreter reads an
argument count from it, and aggregate layout follows the host's own alignment
of a `double` inside a struct.

### VM word size

A 32-bit host runs a 32-bit ABI and a 64-bit host a 64-bit one. CMake detects
the host pointer size with `CMAKE_SIZEOF_VOID_P` and uses that as the VM word
size; `underc/vm_types.h` derives the same answer from the host when no build
system supplies `UNDERC_VM_BITS`, so a consumer that only has the installed
headers never has to restate the ABI. The selected value is reported during
configuration. It may be set explicitly to 16, 32, or 64 bits:

```sh
cmake -S src -B build-lib -DUNDERC_VM_BITS=32
cmake --build build-lib
```

`UNDERC_VM_BITS` controls the signed and unsigned VM word types, execution
stack slots, instruction operands, pointer transport, constants, symbol
payloads, switch tables, function-frame offsets, argument blocks, and the
native-call bridge. Floating-point values consume as many VM slots as their
representation requires.

Runnable builds require a VM word at least as wide as a host pointer. CMake
rejects narrower selections before compilation. A narrower configuration can
be retained solely as a non-runnable compile check with
`-DUCL_COMPILE_ONLY_NARROW_VM=ON`; `uc_init` refuses to start such a build.

By default, interpreted object layout follows the compiler host ABI: `int` and
ordinary enums use the host `int` width, `long` uses the host `long` width, and
pointers use the host pointer width. VM evaluation slots remain
`UNDERC_VM_BITS` wide. Class fields use their natural type alignment capped by
the active packing value; aggregate sizes are rounded to their effective
alignment. That packing value is the widest fundamental alignment of the host
ABI, not the pointer width: on 32-bit MSVC a `double` is 8-aligned inside an
aggregate although a pointer is only 4-aligned, and the alignment is measured
from the host rather than assumed, because the i386 System V ABI aligns the
same `double` to 4. Host-comparison regressions verify mixed `char`, `int`,
`double`, and pointer layouts and pass interpreted aggregate pointers to
native code.

The VM-width object model can be selected with:

```sh
cmake -S src -B build-lib -DUCL_DISABLE_NATIVE_ABI=ON
```

In that mode, `int`, ordinary enums, and `long` objects use the configured VM
word width.

The parser sources `tparser.cpp` and `tparser.h` are generated with bison/yacc
from `src/build/parser.y` and cached in `src/gen`. When those cached files are
present CMake uses them verbatim and does not search for or require bison; when
they are absent CMake runs bison/yacc to regenerate them into `src/gen`, so a
later checkout can reuse them. This allows compiling on systems that have no
bison or yacc installed. Delete `src/gen` to force regeneration. The original
code requires GNU extensions and is therefore compiled as GNU C++98. Non-debug
builds use the project’s `-O1` optimization level.

### Tests

The permanent runtime regression sources live under `regressiontests/`. A
test runner is built with the library when `BUILD_TESTING` is enabled (the
CMake default), so the migration suite can be run without first installing
the separate CLI:

```sh
cmake -S src -B build-test -DUCL_USE_READLINE=OFF -DBUILD_TESTING=ON
cmake --build build-test
ctest --test-dir build-test --output-on-failure
```

Use `-DUCL_DISABLE_NATIVE_ABI=ON` in a second build directory to exercise the
VM-width object model. The sources can also be passed directly to an installed
`ucc` executable. The `host-abi-width` test compiles against the installed
public headers alone, without the library's own compile definitions, and
checks that the VM word and the aggregate alignment rule match the host.

The interpreter has a built-in, staged bytecode optimizer selected with the
`-O0`..`-O3` command-line levels; see [`cli/README.md`](cli/README.md#bytecode-optimization).

### Embedding

Include `underc/ucdl.h`, initialize the interpreter with `uc_init`, and call
`uc_bind_variable` to expose host storage as an interpreted global variable.
Bindings are live and two-way: interpreted assignments immediately update the
host object. The host object must remain alive until the interpreter no longer
uses the binding.

`uc_bind_variable` accepts a name, a `uc_variable_type`, and the host address,
and returns a `uc_status`. Supported types are `bool`, signed and unsigned
`char`, `short`, `int`, and `long`, plus `float` and `double`. Names must be
valid C identifiers and must not already exist in the global context.

The standalone consumer in `embed/` demonstrates both execution paths. First,
`main.cpp` binds host `count` and `multiplier` variables and changes them by
calling `uc_exec` directly. It then initializes an interpreted string, loads
`embed/ucload.cpp` with `uc_load`, and prints the value after the loaded
function changes it. `uc_load` accepts a `const char *` path and returns
nonzero when the source loaded successfully. Build the example against an
installed library:

```sh
cmake -S src -B build-lib -DCMAKE_INSTALL_PREFIX=/tmp/underc
cmake --build build-lib --target install
cmake -S embed -B build-embed -DCMAKE_PREFIX_PATH=/tmp/underc
cmake --build build-embed
UC_HOME="$PWD" build-embed/underc-embed
```

The example prints the initial and changed numeric values, followed by
`Hello from underc`.

## Runtime layout and path discovery

At run time UnderC reads its interpreted include tree from
`$UC_HOME/include/underc/uclstl`, the self-import manifest from
`$UC_HOME/lib/uclr/self.imp`, and the default interactive prelude from
`$UC_HOME/lib/uclr/defs.h`. The help text shown by `#help` and `--help` is
compiled into the library and needs no file.

`UC_HOME` is a single `$PREFIX` that contains `bin/`, `include/`, and `lib/`.
A host application supplies it by calling `uc_set_home_dir("<prefix>")` before
`uc_init()` or `uc_main()`. The `UC_HOME` environment variable and the `-H`
option still override that value. The library contains no code that inspects
the running executable's location; the host decides where runtime files come
from. `ucc` implements the common case: it resolves its own path
(`$PREFIX/bin/ucc`), strips `bin/ucc`, and passes `$PREFIX` to
`uc_set_home_dir()`.

## Consumers

Running `ucc`, its command-line options, the interactive `#` command set, the
`-O0`..`-O3` bytecode optimization levels, and the runnable programs under
`examples/` are documented in [`cli/README.md`](cli/README.md). The `venv`
launcher is documented in [`venv/README.md`](venv/README.md).

The public consumer API is split across `<underc/ucdl.h>` (interpreter
lifecycle, evaluation, imports, compilation, and live variable binding) and
`<underc/ucri.h>` (lower-level symbols, types, calls, tracing, and
persistence). The UCRI instruction record uses a pointer-width operand and
matches runtime instructions in runnable builds; it no longer exposes a packed
22-bit operand. New clients should use `XFunction::instruction_count()` and
`XFunction::instruction_at()` to obtain versioned `XInstructionInfo` snapshots
instead of casting runtime instruction storage. UCRI self-import uses the
generated `UC3 AUTO` manifest, with runtime ABI selection and symbol
resolution instead of fixed executable addresses.

## Project layout

- `src/`: installable interpreter library, VM, debugger, and library
  CMake/package files.
- `src/build/`: parser grammar, self-import generator, and build support.
- `src/gen/`: cached bison/yacc parser output (`tparser.cpp`, `tparser.h`) used
  when present so builds need no bison or yacc.
- `cli/`: standalone `ucc` command-line front end and consumer CMake project;
  see [`cli/README.md`](cli/README.md).
- `venv/`: cross-platform virtual-environment process launcher that embeds the
  interpreter and runs `.cvc` C++ configuration files; consumer CMake project,
  see [`venv/README.md`](venv/README.md).
- `embed/`: standalone host-variable binding example and consumer CMake project.
- `regressiontests/`: permanent language, VM, ABI, and migration regression
  sources.
- `examples/`: runnable applications and native import examples.
- `include/`: private headers used to compile the native UnderC library.
- `include/underc/`: public headers needed by native library consumers.
- `include/underc/uclstl/`: pocket STL, C library declarations, and support
  headers made available to interpreted programs through the default include
  search path.
- `lib/`: bundled implementation support, the generated `uclr/self.imp`
  manifest, and `uclr/defs.h`, the default interactive prelude loaded from
  `$UC_HOME/lib/uclr/defs.h` at run time (installed to `<prefix>/lib/uclr`).
- `src/uclr/`: source of `defs.h`; CMake keeps `lib/uclr/defs.h` in sync and
  installs it.
- `verify/`: language verification programs.
- `VERSIONS.md`: release history and feature deltas.
- `LANGUAGE.md`: audited interpreted-language scope.
- `MISSMATCH.md`: claims from the old documentation that do not match the
  maintained implementation.
- `LICENSE`: GNU Library General Public License version 2.

## Interactive command reference

This is the text shown by `#help` at the interactive prompt. It is compiled
into the library from the block below (CMake extracts the lines between the
`GENERATE_HELP_H_CONTENT_CLI` markers into `help.h`), so editing it here changes
the built-in help. `#help <name>` prints the entry for one command.

<!-- GENERATE_HELP_H_CONTENT_CLI_START -->
```text
UnderC Command Summary (available with #help)
#q     Quit session
#ql    Quit session, writing log file
  The temp file is of the form <month><day>-<hour><min>
#log   Write to <log file>
  Currently only available in the Win32 GUI version (WCON)
#cd    Change current directory <dir>
#pwd   Show current directory
#l     Load <file>
#r     Run current program
  This must have previously been loaded with #l
#lib   Load <library> <import-file>
  Any class declarations and function prototypes are then imported from the
  specified shared library or DLL. An optional import file can be used when
  linking DLLs without symbolic information. To end importing, say #lib with
  no parameter. This is the same as #pragma dlink <file>
#alias Create an alias for a command
  Aliases are defined like #define macros, but only substitute the first token
  on the line and pick up space-separated arguments. For example,
    #alias cd(x) @cd x @pwd
    #alias D(obj,y,z) obj->set(y,z);
    #alias L(f) @include #f
#opt   Set options, e.g. #opt t+ v+
  o- auto disassemble        t- function trace
  v- verbose mode            s- strict mode (no implicit bool conversions)
  p- pointer check           a- access control
  c- strip prompt when copying (WCON only)
  C- C mode                  T- use typedef names if possible
  L- suppress link errors
#lv    Display all local variables
#d     Display variable
#v     Information on variable or function
#u     Disassemble function
#rm    Remove symbol or program (use 'main' to remove the program)
#s     Stop program
#mod   List modules, or position of a function
#types List types <pat>, wildcards pat* or *pat
#funs  List functions <pat>, wildcards pat* or *pat
#gt    Set temporary breakpoint at <file> <lineno>
#b     Set breakpoint at <file> <lineno>
#bs    List breakpoints in <file>
#ff    Set frame <n>
#mc    Clear all macros (also cleans out the global namespace)
```
<!-- GENERATE_HELP_H_CONTENT_CLI_END -->

## Portability notes

The maintained native-call path uses libffi on Linux x86-64 with GCC/Clang and
on Windows with MSVC. The MSVC/nmake build configures, compiles, and links
the interpreter library and regression executables against a prebuilt libffi.
As of this build the Windows x64 suite passes 44 of 45 tests, both in a
release build and in an AddressSanitizer build. A 32-bit MSVC build with no
matching libffi uses the built-in dispatcher and passes 38 of 39 tests; the
six tests it does not register are the libffi-gated native-call cases. In both
configurations the one remaining failure is
`ucri-self-import`: `#lib $self` resolves symbols with `GetProcAddress` in the
running image and reads the generated `lib/uclr/self.imp` manifest, and neither
the manifest generator (which needs `nm` and an `awk`) nor exported symbols
from a statically linked host executable are available under MSVC. Self-import
is therefore a GCC/Clang facility for now. Portable native integrations should
use unmangled `extern "C"` symbols.

Pointer-width correctness on LLP64 hosts, where `long` is 32 bits, is carried
by the VM word type rather than by `int` or `long`. The hidden virtual-method
table pointer, the try-block marker's handler field, the thrown-object slot,
generated native callback stubs, and the `argv` passed to an interpreted
`main` all use pointer-width storage. Instructions that carry a type operand
store a parser type handle and are decoded through `Parser::AsType()`.

On Windows the bundled C library is imported from `msvcrt.dll`. The stdio
entry points that take a `FILE *` are interpreter built-ins bound to the host
C runtime, so handles from `_get_std_stream()` and `fopen()` are never passed
to a separately loaded runtime.

The bundled `vector` now has regression coverage for construction, growth,
reserve/resize, copy and self-assignment, range assignment, clear, and
destruction. The generic `map` now owns and destroys its nodes, supports empty
insertion, prevents unsafe shallow copying, and has insertion/destruction
coverage.

On non-Windows hosts, native C++ allocations use the host allocator directly;
UnderC's `_new_ex` VMT prefix is reserved for interpreted allocations. Native
calls only receive a hidden object pointer when their registered function is
actually a non-cdecl method.

UnderC is distributed under the terms in [LICENSE](LICENSE).
