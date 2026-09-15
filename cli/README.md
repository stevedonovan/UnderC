# UnderC command-line interface (`ucc`)

`ucc` is the standalone command-line front end for the UnderC interpreter. It is
a thin consumer of the installed `libunderc`: `cli/main.cpp` only forwards
`argc`/`argv` to `uc_main()`. Everything below is specific to running the
interpreter from the command line; the library, embedding, and portability
documentation is in the [root README](../README.md).

## Building

The CLI is a separate CMake project that finds the installed interpreter through
`find_package(Underc REQUIRED MODULE)`. Build and install the library first,
then point the CLI at the same prefix:

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

The CLI locates `FindUnderc.cmake` through either `CMAKE_PREFIX_PATH` or
`CMAKE_INSTALL_PREFIX`, so pointing only the install prefix at the interpreter
installation is enough. To build against a shared-library interpreter, configure
the library with `-DUCL_SHARED=ON` and the CLI with `-DUCC_SHARED=ON`.

The CLI has no dependency discovery of its own: the installed
`UndercTargets.cmake` names the interpreter's libffi, readline, and curses by
file path, so no `pkg-config` is needed here. An interpreter installed by a
release before 1.5.4 recorded libffi on Unix as the imported target
`PkgConfig::LIBFFI`, which does not exist in this project and fails the link
with `cannot find -lPkgConfig::LIBFFI`; reinstalling the interpreter clears
that.

`UCC_` options and macros belong to the command-line program; `UCC_SHARED`
selects the shared-library link.

On Windows, `. .\build-cmake-install.ps1` in the repository root builds the
interpreter library, `ucc`, and the `venv` launcher in sequence and installs all
three under one prefix.

## Running

An installed `ucc` finds its own runtime tree. It resolves its executable path
(`$PREFIX/bin/ucc`), strips `bin/ucc`, and hands `$PREFIX` to the library
through `uc_set_home_dir()`. From an install where `ucc` sits in
`$PREFIX/bin`, no environment is needed:

```sh
$PREFIX/bin/ucc
$PREFIX/bin/ucc program.cpp argument1 argument2
```

Set `UC_HOME` (or pass `-H <path>`) to override that when running `ucc` from a
build tree, or to point it at a different prefix. `UC_HOME` is a single
`$PREFIX` with `bin/`, `include/`, and `lib/` subdirectories:

```sh
UC_HOME="/path/to/prefix" build-cli/ucc program.cpp
```

`ucc` needs `$PREFIX/include/underc/uclstl` (the interpreted include tree),
`$PREFIX/lib/uclr/self.imp` (the self-import manifest), and
`$PREFIX/lib/uclr/defs.h` (the default interactive prelude). The repository
root works directly as `$PREFIX` during development.

With no source-file argument, `ucc` starts interactively. It first checks the
working directory for an optional `defs.h`; otherwise it loads
`$PREFIX/lib/uclr/defs.h`, which imports `classlib.h` and the `std` namespace.
The `#help` and `--help` text is compiled into the interpreter and reads no
file at run time.

### Command-line options

`ucc <options> { <source file> }`. With no source file `ucc` is interactive.

- `-H path`: override the runtime prefix (`UC_HOME`).
- `-I path`: add an include directory.
- `-D name=value`: define a macro.
- `-r path`: change directory before running.
- `-i`: force interactive mode.
- `-P`: enable pointer checking.
- `-R`: enable array range checking.
- `-F`: attempt small-function inlining.
- `-T`: prefer typedef names in diagnostics.
- `-W`: suppress dynamic-link warnings.
- `-O0`..`-O3`: bytecode optimization level (see below).
- `-v`: print the version.
- `--help`: show command-line help.

The exact text `ucc --help` prints is compiled into the interpreter from the
block below. CMake extracts the lines between the `GENERATE_HELP_H_CONTENT_CLI`
markers into `help.h`, so editing this block changes the built-in help.

<!-- GENERATE_HELP_H_CONTENT_CLI_START -->
```text
UnderC Command-line Options (available with --help)
-H <path>   Override UC_HOME (the runtime prefix)
-I <path>   Add an include path
-D <M>=<V>  Add a preprocessor macro
-r <path>   Run in the specified directory
-T          Prefer a typedef name for a complex type in diagnostics
-i          Force interactive mode, even with a source file
-W          Suppress linker warnings
-R          Switch on array checking for builtin arrays and vector<>
-P          Switch on pointer checking
-F          Optimize by inlining one-instruction functions
-O <0-3>    Bytecode optimization level
-v          Print the version
--help      This text
```
<!-- GENERATE_HELP_H_CONTENT_CLI_END -->

### Interactive commands

At the interactive prompt, `#help` displays all commands. The principal ones
are `#l file` (load or reload), `#r args...` (run the loaded `main`), `#q`
(quit), `#ql` (quit and write a dated log), `#cd`/`#pwd`, `#x command`
(execute a shell command), and `#lib library [import-file]` (begin importing a
native library; use bare `#lib` to finish). `#pragma dlink` is the source-level
equivalent of `#lib`.

Inspection and debugging commands include `#v`/`#d`/`#lv` (symbols and
variables), `#types`, `#funs`, `#mod`, `#u` (disassemble), `#b`/`#bs`/`#gt`
(breakpoints), `#ff` (select a frame), `#s` (stop), and `#rm` (remove a symbol
or program). `#alias` defines command aliases and `#mc` clears macros and the
global namespace.

`#opt` accepts option letters followed by `+` or `-`: `o` automatic
disassembly, `t` function tracing, `v` verbose mode, `s` strict conversions,
`p` pointer checks, `a` access control, `C` C mode, `T` typedef names in
diagnostics, and `L` suppressed link errors.

### Bundled interpreted library

The default environment exposes common math, conversion, string, memory,
formatted-I/O, file-I/O, process-pipe, and allocation functions. Interpreted
programs call `popen` and `pclose` portably; the host bridge uses POSIX
`popen`/`pclose` on Linux and `_popen`/`_pclose` on Windows. The bundled
`stdio.h` defines `SEEK_SET`, `SEEK_CUR`, and `SEEK_END`; `stdlib.h` exposes
`getenv`, `system`, `_gcvt`, and callback-capable `atexit`; `io.h` exposes
`_access` through a portable host bridge; `string.h` defines `size_t` itself
so it can be included on its own; and `uc_except.h` exposes `RangeError`. The
bundled headers also add compact `string`, stream, `list`, `vector`, and `map`
implementations, regular expressions, directory traversal, timers, exception
helpers, persistence and reflection helpers. These are compact implementations
for UnderC programs, not a complete or conforming standard library. See
[LANGUAGE.md](../LANGUAGE.md) for the precise language boundary.

Native C functions can be imported after `#lib` by declaring `extern "C"`
prototypes; the examples in `examples/import/` show the declarations and
import files. The public `<underc/ucdl.h>` API provides interpreter lifecycle,
evaluation, imports, compilation, and live variable binding; `<underc/ucri.h>`
exposes lower-level symbols, types, calls, tracing, and persistence.

### Bytecode optimization

Use `-O0`, `-O1`, `-O2`, or `-O3` before the source-file argument to select
the bytecode optimization level. The default is `-O0`.

- `-O0` disables bytecode optimization.
- `-O1` applies local stack and redundant-operation peepholes.
- `-O2` adds integer constant folding and unary simplification.
- `-O3` adds algebraic strength reduction, jump threading, redundant-jump
  removal, and one-instruction function inlining.

The optimizer is built into UnderC and has no additional runtime dependency.
It follows the staged peephole, constant-folding, and control-flow reduction
approach used by V8's interpreter while adapting the passes to UnderC's
stack-based p-code and stable instruction-offset requirements.

## Examples

The `examples/` directory contains small applications that run directly with
the command-line interpreter. The calculator accepts one quoted mathematical
expression and prints its value:

```sh
UC_HOME="$PWD" build-cli/ucc examples/uccalc.cpp "2 * (3 + 4)"
```

`uccalc.cpp` supports floating-point `+`, `-`, `*`, `/`, right-associative
`^`, parentheses, and unary signs. `tkgui.c` demonstrates dynamic Tcl/Tk
imports by opening a window with a button that closes it:

```sh
UC_HOME="$PWD" build-cli/ucc examples/tkgui.c
```

The GUI example requires Tcl and Tk shared libraries discoverable as
`libtcl.so` and `libtk.so`, plus a graphical display.

Native-import sources live in `examples/import/`. Native imports have two
parts: a host compiler produces a `.so` or `.dll`, and UnderC parses the
matching declarations in a header bracketed by `#lib`. The native library must
export the exact symbols requested by those declarations. C++ imports are
ABI-specific, so build the library with a compiler compatible with the symbol
mangling expected by the UnderC build.

On Linux, the following commands build the two libraries used by `import1.h`,
show their exported symbols, and run the value-import smoke example. Run them
from the repository root:

```sh
g++ -std=gnu++98 -fPIC -fkeep-inline-functions -shared \
  examples/import/mstring.cpp -o examples/import/libmstring.so
g++ -std=gnu++98 -fPIC -fkeep-inline-functions -shared \
  examples/import/import1.cpp examples/import/mstring.cpp \
  -o examples/import/libimport1.so

nm -D --defined-only examples/import/libimport1.so | \
  grep -E '_Z3addii|_Z3sumdd|FatString'
nm -D --defined-only examples/import/libimport1.so | c++filt | \
  grep -E 'add\(|sum\(|FatString'

UC_HOME="$PWD" build-cli/ucc examples/import/import1-run.cpp
```

The first `nm` command displays the actual mangled ELF symbols, including
`_Z3addii` and `_Z3sumdd`. Piping through `c++filt` displays their readable
forms, `add(int, int)` and `sum(double, double)`. The program should print
`add=42 sum-ok=1`. If UnderC reports `cannot link to`, use `nm` to check that
the requested mangled symbol is present in the library.

Other Linux examples can be built in the same way:

```sh
g++ -std=gnu++98 -fPIC -fkeep-inline-functions -shared \
  examples/import/import2.cpp -o examples/import/libimport2.so
g++ -std=gnu++98 -fPIC -fkeep-inline-functions -shared \
  examples/import/import3.cpp -o examples/import/libimport3.so
g++ -std=gnu++98 -fPIC -fkeep-inline-functions -shared \
  examples/import/import4.cpp -o examples/import/libimport4.so
g++ -std=gnu++98 -fPIC -fkeep-inline-functions -shared \
  examples/import/import5.cpp -o examples/import/libimport5.so
nm -D --defined-only examples/import/libimport5.so | c++filt
```

With the Microsoft command-line compiler, open a Developer Command Prompt and
run these commands from the repository root. The DLLs are written to the root
because the Windows branches in `mstring.h` and `import1.h` load them by bare
filename:

```bat
cl /nologo /EHsc /LD examples\import\mstring.cpp /link /OUT:mstring.dll
cl /nologo /EHsc /LD examples\import\import1.cpp ^
  examples\import\mstring.cpp /link /OUT:import1.dll
dumpbin /exports import1.dll
set UC_HOME=%CD%
build-cli\ucc.exe examples\import\import1-run.cpp
```

MinGW uses the same source files and can create DLLs with `g++`:

```sh
g++ -std=gnu++98 -fkeep-inline-functions -shared \
  examples/import/mstring.cpp -o mstring.dll
g++ -std=gnu++98 -fkeep-inline-functions -shared \
  examples/import/import1.cpp examples/import/mstring.cpp -o import1.dll
nm -g --defined-only import1.dll | c++filt
```

The other `.cpp` files in that directory are native shared-library sources,
not standalone interpreted programs. `-fkeep-inline-functions` retains the
inline symbols described by their interpreter-side class declarations.
