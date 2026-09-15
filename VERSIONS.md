# UnderC release history

Each entry summarizes the maintained feature delta. Historical version entries
from the complete earlier history are retained below.

## 1.5.4 — 2026-09-09

- Made libffi discovery on Unix match Windows: `-DLIBFFI_INCLUDE_DIR=<dir>`
  and `-DLIBFFI_LIBRARY=<file>` now name libffi directly on every platform.
  The pair is honoured ahead of any automatic search, so a hand-built libffi
  (`-DLIBFFI_INCLUDE_DIR=/opt/libffi/include
  -DLIBFFI_LIBRARY=/opt/libffi/lib/libffi.a`) builds on a host where libffi has
  neither a CMake package nor a pkg-config file. Giving only one of the two is
  a configuration error.
- Replaced the unconditional `find_package(PkgConfig REQUIRED)` on Unix with an
  ordered search: the explicit pair, a libffi CMake package
  (`find_package(libffi CONFIG)` or `find_package(ffi CONFIG)`), pkg-config,
  then plain `find_path`/`find_library`. pkg-config is no longer required to configure the
  library, and a build with none of the mechanisms available reports what to
  set instead of failing inside PkgConfig.
- Link-probed the chosen libffi on Unix as well as Windows, so an unusable
  candidate is reported during configuration; the probe is re-run whenever the
  candidate changes.
- Fixed the installed CMake export on Unix. `underc` linked the imported target
  `PkgConfig::LIBFFI` publicly, which was written verbatim into
  `UndercTargets.cmake`, and every consumer of an installed interpreter —
  `ucc`, `venv`, `embed` — failed with `cannot find -lPkgConfig::LIBFFI`.
  libffi is now recorded as its library file, and imported targets from a
  libffi CMake package are reduced to the same.
- Added the `libffi-manual-paths` regression: it configures a throwaway build
  tree with `find_package(PkgConfig)` disabled and libffi named by hand, and
  requires the configuration to succeed and to use exactly the given library.
- Added the missing `<stdlib.h>` to `venv/src/cmdline.c`, whose `free()` calls
  were an implicit declaration that current GCC rejects as an error.
- Bumped the library, CLI, embed, and venv projects to 1.5.4 and updated the
  `public-header-layout` regression and the current-feature documentation.

## 1.5.3 — 2026-09-07

- Compiled the `#help` and `--help` text into the library. CMake generates
  `help.h` from the `GENERATE_HELP_H_CONTENT_CLI_START` /
  `GENERATE_HELP_H_CONTENT_CLI_END` marked blocks in `README.md` and
  `cli/README.md`; `show_help()` scans that string and no longer opens a file.
- Merged `uclresource/help.txt` and `uclresource/cmd-help.txt` into those
  README blocks and deleted both files and the loader code.
- Removed `uclresource/`. `defs.h` now lives at `src/uclr/defs.h`, is installed
  to `<prefix>/lib/uclr/defs.h`, kept in sync at `lib/uclr/defs.h` for the
  in-tree `UC_HOME`, and loaded from `<UC_HOME>/lib/uclr/defs.h` at run time.
- Added `uc_set_home_dir()` to `<underc/ucdl.h>`: a host application sets the
  runtime `$PREFIX` (`bin/`, `include/`, `lib/`) before `uc_init()` /
  `uc_main()`. `UC_HOME` and `-H` still override it. The OS-specific logic that
  locates the prefix stays in the host.
- `ucc` now finds its own runtime tree: it resolves its executable path,
  strips `bin/ucc`, and calls `uc_set_home_dir()`. An installed `ucc` needs no
  environment. The library keeps no `argv[0]`-inspection code.
- Bumped the library, CLI, embed, and venv projects to 1.5.3 and updated the
  `public-header-layout` regression and the current-feature documentation. The
  Windows x64 suite passes 50 of 51 tests; `ucri-self-import` remains a
  GCC/Clang-only facility.

## 1.5.1 — 2026-09-07

- Fixed the CMake CLI build (`build-cmake-install.ps1`) failing with
  `No "FindUnderc.cmake" found in CMAKE_MODULE_PATH`. `cli/CMakeLists.txt`
  only extended `CMAKE_MODULE_PATH` with prefixes on `CMAKE_PREFIX_PATH`, but
  the install script configures the CLI with just `CMAKE_INSTALL_PREFIX`
  pointing at the interpreter installation. The install prefix is now searched
  as well, so the installed `FindUnderc.cmake` and `UndercTargets.cmake` are
  found. `embed/CMakeLists.txt` got the same fix.
- Incremented the library, CLI, and embed project versions to 1.5.1 and updated
  the current-feature documentation.

## 1.5.0 — 2026-08-31

- Fixed local variable allocation on 64-bit hosts: the frame is addressed in
  VM words but the cursor advanced by each variable's raw byte size, so any
  local narrower than a word shared storage with the one declared after it.
  `int p; int q;` was a single variable, and a scalar declared after an array
  overwrote that array's first element.
- Fixed `new T[n]`: the element count never reached the constructor and
  destructor loops, so only element zero was ever constructed and elements
  1..n-1 were raw memory. This is what made `vector<string>` corrupt the heap
  once it held more than one element.
- Fixed the width of the hidden method-table slot reserved by `new` and
  `new[]`, which was `sizeof(int)` while the engine reads it one VM word below
  the object, and released `new char[]` blocks with `delete[]` rather than
  scalar `delete`.
- Gave `std::map` a working copy constructor and assignment operator, so a map
  can be returned by value; added `clear()`, `empty()`, and `count()`.
  `map<string, vector<string> >` now works end to end.
- Fixed the bundled `string`: a `new char[]` buffer released with scalar
  `delete`, two constructors that called `resize()` on uninitialised members,
  and a freshly allocated buffer left unterminated.
- Added `local-slot-allocation`, `new-array-construction`,
  `container-vector-of-string`, `container-map-copy-semantics`,
  `container-map-of-vector-string`, and `array-allocation-churn` regressions.
  The Windows x64 release suite passes 50 of 51 tests; `ucri-self-import`
  remains a GCC/Clang-only facility.
- Fixed virtual method dispatch on 64-bit hosts: the hidden method-table
  pointer was read four bytes below the object instead of one VM word, so
  every virtual call, including the bundled `ostream::flush()` reached by
  `cout << ... << endl`, faulted.
- Fixed interpreted exception handling: the try-block marker field and the
  thrown-object slot are pointer-wide, `THROW_EX`/`DCAST`/`SHOWI` decode their
  parser type handle instead of reading the operand as a `Type` object, and an
  exception is offered to the innermost enclosing try block first.
- Fixed whole-object copies: `COPY` takes its destination from the top of the
  stack, so plain-struct assignment and plain-struct return by value no longer
  copy backwards.
- Initialized `Function`'s return-object, cdecl, function-kind, and
  default-argument members, which decided the aggregate-return calling
  convention from uninitialized memory.
- Fixed pointer truncation through 32-bit `long` when passing an interpreted
  function to a native as a callback and when passing `argv` to an interpreted
  `main`.
- Fixed out-of-bounds accesses in `Utils::strip_last`, `ifs::fetch_line`, and
  `string::resize`, gave `LineNumbersB` a virtual destructor, and corrected
  `VStack::empty`.
- Replaced the obsolete `msvcrt40.dll` with `msvcrt.dll` as the Windows C
  library, made `fputs`, `putc`, `putchar`, `popen`, and `pclose` built-ins
  bound to the host C runtime, and made `string.h` define `size_t` itself.
- Added `runtime-exception-handling`, `object-value-semantics`,
  `bundled-c-library-imports`, and `native-shell-env` regressions. The Windows
  x64 suite passes 43 of 44 tests in release and AddressSanitizer builds;
  `ucri-self-import` remains a GCC/Clang-only facility.
- Removed the obsolete `ENUM_INIT` compatibility path; bool literals and named
  enumerators now have direct, independently owned, correctly typed constant
  storage.
- Strengthened native-call regression coverage to use the standard prelude,
  exact bool/enum value checks, native heap churn, interpreter cleanup, and
  post-cleanup allocation.
- Verified the `venv_spawner` shell-environment reproducer repeatedly with
  literal `true`: it prints `VENV_ONE=pre-alpha-post` and exits without heap
  corruption.
- Incremented the library, CLI, and embed project versions to 1.5.0 and updated
  the current-feature documentation.
- Selected the ABI from the host: a 32-bit host builds and runs a 32-bit
  interpreter and a 64-bit host a 64-bit one. `underc/vm_types.h` derives
  `UNDERC_VM_BITS` from the host when the build system does not supply it, so
  consumers of the installed headers no longer have to restate it.
- Fixed aggregate alignment on 32-bit hosts. The default object alignment was
  the pointer width, which sized and laid out every `double`-bearing struct
  differently from the host compiler on MSVC x86; it is now the larger of the
  pointer alignment and the host's measured aggregate `double` alignment.
- Fixed 32-bit interpreted callbacks: generated stubs are placed in executable
  pages rather than on the no-execute C++ heap, and their argument block is
  initialized, so a zero-argument callback no longer pushes a garbage number
  of arguments.
- Added a link test for the libffi found on Windows, so an architecture
  mismatch is reported during configuration instead of as unresolved `ffi_*`
  externals at link time; a 32-bit build with no matching libffi falls back to
  the built-in native dispatcher.
- Made `FindUnderc.cmake` prefer the installed `UndercTargets.cmake`, so `cli/`
  and `embed/` inherit the interpreter's exact dependencies and ABI instead of
  re-deriving them.
- Added the `host-abi-width` regression, compiled against the public headers
  alone, which pins the VM word and the aggregate alignment rule to the host.
  Windows x64 passes 44 of 45 tests; a 32-bit MSVC build without libffi passes
  38 of 39. `ucri-self-import` remains a GCC/Clang-only facility.

## 1.4.0 — 2026-08-31

- Added correctly stored `true` and `false` literals, a built-in `NULL`
  compatibility macro, `signed` integer spellings, a `wchar_t` compatibility
  typedef, and the ISO C++ alternative operator spellings.
- Reserved otherwise unsupported ISO C/C++98 keywords instead of accepting
  them as identifiers, and restored bytecode emission for `~`/`compl`.
- Added scalar native-call VM-slot validation before libffi dispatch and
  prevented fixed-arity calls from fabricating variadic tail arguments.
- Added ISO keyword/literal and repeated bool/enum native-argument regressions,
  including Windows full-page-heap validation.
- Split the source headers into private native build headers under `include/`,
  native consumer API headers under `include/underc/`, and the interpreted
  pocket STL/runtime library under `include/underc/uclstl/`.
- Changed the default interpreter include search root to
  `$UC_HOME/include/underc/uclstl`, retaining ordinary `-I` paths after the
  default library path.
- Restricted installation to the public native header dependency closure plus
  generated `version.h`, while installing the interpreted library only in its
  `uclstl` subtree.
- Made the CLI and embed CMake consumers handle every entry in a multi-value
  `CMAKE_PREFIX_PATH`, allowing UnderC and libffi to use separate prefixes.
- Added public-header layout and default pocket-STL search regressions, and
  incremented the library, CLI, and embed project versions to 1.4.0.

## 1.3.9 — 2026-08-20

- Added the maintained Linux System V x86-64 non-libffi bridge with unbounded
  scalar argument dispatch and generated AMD64 callback trampolines.
- Added libffi descriptions for plain aggregate arguments and returns, plus
  explicit rejection of unsupported non-trivial, union, and bit-field values.
- Added natural class-field alignment and host-comparison layout coverage.
- Widened core size/frame/type metadata and added checked Type pointer-depth
  bounds.
- Added versioned UCRI bytecode snapshot accessors.
- Added method and recursive callback, aggregate ABI, layout, and UCRI
  regressions, plus GCC/Clang, sanitizer, legacy-mode, and narrow-VM CI jobs.
- Fixed long macro-name handling and macro-token terminator bounds exposed by
  the Clang test build.
- Fixed narrow host-object constant stores and the native pocket-string array
  deallocation pairing.
- Added build switches for sanitizers, conversion diagnostics, and
  experimental C++ imports.

## 1.3.8 — 2026-08-20

- Restored basename extraction for path-qualified source files so synthetic
  module-initializer names no longer retain a leading directory separator,
  with dedicated regression coverage.
- Restored the 1.2.9 native pocket-string overloads for direct C-string
  comparison, equality, and inequality, along with safe construction from a
  null `const char *` and dedicated regression coverage.
- Restored the 1.2.9 interpreted C-library surface for `SEEK_SET`, `SEEK_CUR`,
  `SEEK_END`, `getenv`, `system`, `_gcvt`, `atexit`, and `_access`, using
  portable built-in bridges for platform-specific spellings and safe
  interpreted exit callbacks.
- Restored the public interpreted `RangeError` declaration and added bundled
  C-library exposure regression coverage.
- Added the explicit CMake `selfimp` target and the portable `UC3 AUTO`
  symbol-only UCRI manifest at `lib/uclr/self.imp`; runtime self-imports now
  resolve current-process symbols without fixed addresses, propagate the
  required export flags to static consumers, and load the manifest from
  `$UC_HOME/lib/uclr/self.imp`.
- Made legacy import values pointer-width, repaired custom-stream manifest
  parsing, added safe current-ABI symbol matching, and covered UCRI
  self-import with a regression.
- Moved the maintained parser grammar to `src/build/parser.y` and the
  self-import symbol filter to `src/build/xnames.awk`, updating current and
  legacy build references.
- Moved default interactive definitions and help lookup into
  `$UC_HOME/uclresource`, while retaining a working-directory `defs.h` as a
  local override without recording an error when that override is absent.
- Removed the duplicate `src/defs.h` and added regression coverage proving
  that repository-root interactive startup loads the bundled `string` type.

## 1.3.7 — 2026-08-20

- Enforced pointer-width VM runtime checks while preserving narrower VM words
  as explicitly non-runnable compile checks.
- Added libffi closures for every maintained interpreted callback consumer,
  with owned lifetime and scalar, pointer/reference, floating-point, method,
  zero-argument, and long argument-list support; retained the legacy emitter
  for `UCL_LIBFFI=OFF` builds.
- Removed all libffi-mode fallback calls to the legacy dispatcher and added
  deterministic diagnostics for unsupported C++ objects passed by value.
- Replaced packed 32-bit type metadata with semantic fields and interned parser
  handles, widened pointer depth and type indices, and removed aliasing-based
  equality.
- Updated UCRI instructions to carry pointer-width operands and corrected
  declared-base-type bit-field allocation boundaries.
- Added native callback regression coverage and documented the maintained ABI,
  legacy platform boundary, and current interop behavior.

## 1.3.6 — 2026-08-20

- Changed the public `uc_load` declaration from `void uc_load(char *)` to
  `int uc_load(const char *)`, matching the implementation's success status
  and allowing const paths.
- Consolidated the native embedding example in `embed/main.cpp`, retained the
  direct `uc_exec` example that changes bound `count` and `multiplier` values,
  and added an interpreted `embed/ucload.cpp` source that changes its string
  from `Started up` to `Hello from underc` before the program prints it.
- Added regression coverage for the public `uc_load` signature, return value,
  source execution, and changed output.

## 1.3.5 — 2026-08-20

- Replaced the pointer-string-based `uc_init_ref` interface with the typed,
  status-returning `uc_bind_variable` API for live host scalar bindings.
- Added direct global reference registration with identifier, address,
  initialization, duplicate-name, and supported-type validation.
- Added an installed-library embedding example and native regression coverage
  for two-way `int` and `double` binding, invalid names, and duplicate names.

## 1.3.4 — 2026-08-20

- Added `-O0` through `-O3` command-line optimization levels and a staged
  bytecode optimizer while preserving instruction offsets.
- Added regressions that execute optimized programs at every supported level.

## 1.3.3 — 2026-08-20

- Added portable interpreted `popen` and `pclose` functions and preserved
  `fgets` end-of-file results through console-aware host bridges.
- Added platform-selected process-output regressions.

## 1.3.2 — 2026-08-20

- Moved native import examples to `examples/import`, fixed current Linux builds
  and symbol matching, and added a runnable value-import smoke example.
- Fixed integer `case` labels when interpreted `int` and native `long` widths
  differ, with dedicated regression coverage.

## 1.3.1 — 2026-08-20

- Added default-on libffi native dispatch with dynamically sized argument
  lists while retaining `UCL_LIBFFI=OFF` compatibility mode.
- Fixed pointer indexing, scalar/floating/reference return transport, double
  slot accounting, and pointer-to-const increments.
- Added expression-parser and Tcl/Tk examples plus relevant regressions.

## 1.3.0 — 2026-08-20

- Introduced the installable library/separate CLI build, current CMake/Bison
  support, configurable VM words, native object layout, and the regression
  runner.
- Fixed parser, enum, allocation, reference, vector, and map migration defects.

## 1.2.9

- Added member templates, container improvements, deferred static
  initialization, native return fixes, and BeOS patches.

## 1.2.1 — 2002-11-07

- Added interactive help and fixed enum, integer, pointer, overload, macro, and
  preprocessing behavior.

## 1.2.0

- Added C mode, packing controls, include paths, imported-object support, and a
  Windows graphical DLL build, with numerous conversion and aggregate fixes.

## Earlier development releases

The source history records the 0.9.x through 1.1.4 development line covering
the p-code runtime, preprocessing, classes, templates, exceptions, namespaces,
dynamic imports, callbacks, debugging, reflection, C compatibility, and the
bundled library. Complete per-release deltas do not survive for every build.
