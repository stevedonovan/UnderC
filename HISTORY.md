# UnderC change history

This file records modernization work performed on this source tree. Consolidated
release information is in `VERSIONS.md`.

## UnderC 1.5.4 libffi discovery and a self-contained CMake export (2026-09-09)

libffi no longer has to be described by pkg-config on Unix, and the installed
CMake package no longer hands consumers a dependency they cannot resolve.

Naming libffi by hand:

- `-DLIBFFI_INCLUDE_DIR=<dir>` and `-DLIBFFI_LIBRARY=<file>`, previously
  meaningful only on Windows, are honoured on every platform. The pair is
  checked before any automatic discovery runs and is never replaced by a system
  copy, so

  ```sh
  cmake -S src -B build -DLIBFFI_INCLUDE_DIR=/opt/libffi/include \
                        -DLIBFFI_LIBRARY=/opt/libffi/lib/libffi.a
  ```

  configures on a host whose libffi ships neither a CMake package nor a `.pc`
  file. Passing only one of the two is a configuration error naming both.

Unix discovery order:

- `src/CMakeLists.txt` no longer runs `find_package(PkgConfig REQUIRED)` plus
  `pkg_check_modules(LIBFFI REQUIRED IMPORTED_TARGET libffi)` unconditionally.
  The order is now: the explicit variables, a libffi CMake package
  (`find_package(libffi CONFIG)`, then `find_package(ffi CONFIG)`, and the
  target spellings `libffi::libffi`, `libffi::ffi`, `ffi::ffi`, `ffi::libffi`,
  `libffi`, `ffi`), pkg-config, and a plain `find_path`/`find_library` sweep
  that also honours `CMAKE_PREFIX_PATH`.
- When every mechanism comes up empty the build stops with a message that
  lists them and the variables to set, instead of the previous failure inside
  `find_package(PkgConfig REQUIRED)`.
- The Windows branch is unchanged in behaviour. Its link probe was factored
  into the `underc_probe_libffi` macro, which both platforms now use, and which
  re-runs the cached probe whenever the candidate include directory or library
  changes.

Export correctness:

- `underc` linked `PkgConfig::LIBFFI` as a `PUBLIC` dependency. `install(EXPORT)`
  wrote that imported target name straight into `UndercTargets.cmake`, where it
  means nothing to a consumer's project, so `ucc`, `venv`, and `embed` all
  failed against an installed interpreter on Unix with
  `/usr/bin/ld: cannot find -lPkgConfig::LIBFFI`.
- libffi is now always reduced to a plain library file before it is linked:
  pkg-config results are taken from `<prefix>_LINK_LIBRARIES`, and an imported
  target from a libffi CMake package is reduced by
  `underc_imported_library_location()` to its `IMPORTED_LOCATION` and
  `INTERFACE_INCLUDE_DIRECTORIES`. The installed export now records
  `/usr/lib/libffi.so` (or whichever file was used), and consumers link without
  needing pkg-config themselves.

Tests and documentation:

- Added `regressiontests/libffi-manual-paths.cmake`, registered as the
  `libffi-manual-paths` test on Unix. It configures a throwaway build tree of
  `src/` with `-DCMAKE_DISABLE_FIND_PACKAGE_PkgConfig=ON` and libffi named by
  hand, and requires the configure step to succeed and to report exactly the
  library it was given.
- `README.md` gained a "Finding libffi" section covering the search order, the
  explicit variables, and the file-path export; `cli/README.md` and
  `venv/README.md` note that a consumer needs no pkg-config and what an
  interpreter installed before 1.5.4 fails with.
- Bumped the library, CLI, embed, and venv CMake projects to 1.5.4 and the
  `public-header-layout` regression's expected version string. On this Linux
  host 52 of 53 tests pass; `ucri-self-import` fails here both before and after
  this change.

Unrelated build fix found while verifying the consumers:

- `venv/src/cmdline.c` called `free()` with no `<stdlib.h>` in scope, which
  current GCC rejects outright (`implicit declaration of function 'free'`)
  rather than warning about. The include was added; `venv` builds against an
  installed 1.5.4 interpreter on Linux again.

## UnderC 1.5.3 compiled-in help, resource relocation, runtime path API (2026-09-07)

The interpreter no longer reads any text resource file at run time, the
remaining resource directory moved out of the repository root, and a host
application now tells the library where its runtime tree lives instead of the
library guessing from `argv[0]`.

Help text:

- `#help` and `--help` text is compiled into the library. CMake generates
  `help.h` (`src/build/generate-help-h.cmake`, wired into `src/CMakeLists.txt`
  as a custom command) from the blocks between the
  `GENERATE_HELP_H_CONTENT_CLI_START` / `GENERATE_HELP_H_CONTENT_CLI_END`
  markers in `README.md` (interactive command summary) and `cli/README.md`
  (command-line option summary). The Markdown code fence inside each block is
  stripped; only the marked region is used.
- `show_help()` in `src/main.cpp` now scans a compiled-in string rather than
  opening a file; the file-reading path and the `ifstream` it used are gone.
- The content of `uclresource/help.txt` and `uclresource/cmd-help.txt` was
  merged into the two README marker blocks, and both `.txt` files were deleted.

Resource relocation:

- `uclresource/` was removed. `defs.h` now lives at `src/uclr/defs.h`; CMake
  copies it to `lib/uclr/defs.h` for the in-tree `UC_HOME` and installs it to
  `<prefix>/lib/uclr/defs.h`.
- The default interactive prelude is loaded from `<UC_HOME>/lib/uclr/defs.h`
  (`uc_resource_file()` in `src/main.cpp` retargeted from `uclresource/` to
  `lib/uclr/`).

Runtime path discovery:

- Added `uc_set_home_dir(const char *)` to `<underc/ucdl.h>` (implemented in
  `src/dll_entry.cpp`, backed by `Main::set_home_dir` /
  `Main::configured_home_dir` in `src/main.cpp` and `include/main.h`). A host
  calls it before `uc_init()` / `uc_main()` to set the runtime `$PREFIX`
  (`bin/`, `include/`, `lib/`). `UC_HOME` and `-H` still override it.
- The library contains no OS-specific "where am I" logic. `cli/main.cpp` now
  resolves the `ucc` executable path (`GetModuleFileNameA` on Windows,
  `/proc/self/exe` on Linux, `_NSGetExecutablePath` on macOS), strips
  `bin/ucc`, and passes the prefix to `uc_set_home_dir()`. An installed `ucc`
  in `<prefix>/bin` now needs no environment.

Version and documentation:

- Bumped the library, CLI, embed, and venv CMake projects to 1.5.3 and the
  `public-header-layout` regression's expected version string.
- Rewrote the `README.md` runtime/consumer sections (library and embedding
  only; `ucc` and `venv` usage now only linked, not repeated), added the
  interactive command reference block, and updated `cli/README.md` running,
  options, and `--help` sections.
- `regressiontests/interactive-bootstrap.cmake` messages updated for the
  compiled-in help; it still asserts `#help` shows `Quit session` and `--help`
  shows `Override UC_HOME`, now proving the text is compiled in.

Verified: the MSVC/NMake Windows x64 release build passes 50 of 51 tests
(`ucri-self-import` remains a GCC/Clang-only facility). An installed `ucc` run
with no `UC_HOME` finds `include/underc/uclstl` and `lib/uclr/defs.h` from its
own location, `--help` and `#help` print the compiled-in text, and a source
file runs and prints its output.

## UnderC 1.5.1 venv launcher build integration and CLI doc split (2026-09-07)

The `venv` virtual-environment launcher (renamed from `venv_spawner`) is now a
first-class consumer of the interpreter package, built and installed by the same
Windows script as the library and `ucc`.

Build:

- `build-cmake-install.ps1` already invoked `cmake -S venv` as a third stage
  after `src/` and `cli/`; that stage now succeeds. `venv.exe` installs next to
  `ucc.exe` under the shared prefix.
- Removed the `USE_UNDERC` CMake option from `venv/CMakeLists.txt`. The embedded
  UnderC interpreter is mandatory — a `.cvc` configuration file is C++ run by
  that interpreter — so the option, the `VENV_USE_UNDERC` compile definition,
  the `#ifdef VENV_USE_UNDERC` pure-C fallback `main()` in `venv/src/main.c`,
  and its "rebuild with -DUSE_UNDERC=ON" stub are gone.
- Reduced `venv/CMakeLists.txt` to the shape of `cli/CMakeLists.txt`: it locates
  the interpreter only through `find_package(Underc REQUIRED MODULE)` against
  `CMAKE_PREFIX_PATH` / `CMAKE_INSTALL_PREFIX`. Removed the bespoke
  `Underc_ROOT` / `$DEP_DIR` / `C:/pkg/dep` hint search, the direct
  `UndercTargets.cmake` include, the recovery of the prefix from the imported
  target, the baked-in `VENV_UNDERC_PREFIX` default `UC_HOME`, and the
  `ffi.dll` copy/install step. UnderC is either on the prefix path or it is
  not, exactly as for `ucc`.
- `venv/src/underc_bridge.cpp` now includes `<underc/ucdl.h>` — the installed
  public header path, reachable through the `Underc::underc` interface include
  directory — instead of `<ucdl.h>`, which only resolved because the removed
  CMake code added `<prefix>/include/underc` to the search path.
- Dropped the `build-time prefix` candidate from `venv`'s `UC_HOME`
  auto-detection (it was fed by `VENV_UNDERC_PREFIX`); `$UC_HOME`,
  `$DEP_DIR/underc`, the directory holding `venv`, its parent, and the built-in
  default remain.

Documentation:

- Added `cli/README.md` and moved the CLI-specific material into it: building
  `ucc`, running it interactively or on a source file, the command-line
  options, the interactive `#` command set and `#opt` letters, the
  `-O0`..`-O3` bytecode-optimization levels, the interpreted environment
  exposed at the prompt, and the runnable `examples/` (`uccalc.cpp`,
  `tkgui.c`, and the `examples/import/` native-import walk-throughs).
- Trimmed `README.md` to the library, embedding, build, and portability
  material, refreshed the feature list and project layout for the three
  installed consumers (`ucc`, `venv`, `embed`), and documented that
  `build-cmake-install.ps1` builds and installs all three under one prefix.

Verified: `. .\build-cmake-install.ps1` configures, builds, and installs
`underc.lib`, `ucc.exe`, and `venv.exe` on the MSVC/NMake Windows x64
toolchain, and the installed `venv.exe` runs a `.cvc` configuration through a
persistent `cmd.exe` shell.

## UnderC 1.5.1 CMake CLI package discovery repair (2026-09-07)

`. .\build-cmake-install.ps1` stopped during the CLI configure step with:

```
No "FindUnderc.cmake" found in CMAKE_MODULE_PATH
```

`cli/CMakeLists.txt` locates the interpreter with `find_package(Underc REQUIRED
MODULE)`. The interpreter's install step writes `FindUnderc.cmake` and
`UndercTargets.cmake` to `<prefix>/lib/cmake/Underc`, and the CLI adds that
directory to `CMAKE_MODULE_PATH` by iterating the prefixes on
`CMAKE_PREFIX_PATH`. `build-cmake-install.ps1` configures the CLI with only
`-DCMAKE_INSTALL_PREFIX="$env:DEP_DIR\underc-vc-x64r"` and no
`CMAKE_PREFIX_PATH`, so the loop had nothing to iterate and the module was
never on the path.

Fix:

- `cli/CMakeLists.txt` now builds its search list from `CMAKE_PREFIX_PATH`
  *and* `CMAKE_INSTALL_PREFIX`, then appends the `lib/cmake/Underc`,
  `lib64/cmake/Underc`, and `${CMAKE_INSTALL_LIBDIR}/cmake/Underc`
  subdirectories of each to `CMAKE_MODULE_PATH`.
- `embed/CMakeLists.txt` carried the identical latent bug and received the same
  fix.
- Bumped the library, CLI, and embed CMake project versions to 1.5.1, and
  updated the `public-header-layout` regression's expected version string.

The full `build-cmake-install.ps1` run now configures, builds, and installs
both the static `underc.lib` and `ucc.exe` on the MSVC/NMake Windows x64
toolchain.

## UnderC 1.5.0 frame and array allocation repair (2026-09-01)

Investigation of the `vector<string>` crash described in
`underc_fix_vector.txt`, found while writing `parseEnvironment()` for
`venv_spawner`. The reported defect is real and is fixed here. Tracing it
also turned up a second, wider allocation bug in the same family: local
variables narrower than a VM word shared storage with the variable declared
after them.

Local frame slots:

- `LocalContext::alloc()` advanced the frame cursor by the raw byte size of
  each variable, but the frame is addressed in VM words -- the context sets
  `set_mem_unit(sizeof(VMWord))`, and `Table::alloc_aligned()` returns the byte
  offset divided by that unit. Anything that was not a whole number of words
  left the cursor mid-word, and the next declaration's offset truncated back
  on top of it. On a 64-bit host, where an int is half a word, `int p; int q;`
  produced one variable rather than two, and the scalar declared after an
  array landed on that array's first element, so a loop counter overwrote
  `a[0]`. While `VMWord` was four bytes the division was always exact, so this
  is a 64-bit port defect. Locals are now rounded up to whole words, which is
  what `add_variable()` was already assuming when it reserved
  `vm_word_count(size)` words for the offset it handed out.

Dynamic array construction:

- The element count of a `new T[n]` never reached the `CCALLV` opcode, so the
  constructor and destructor loops ran exactly one iteration whatever `n` was
  and elements 1..n-1 were raw memory. Two independent faults caused this.
  `_new_vect()` recorded the count only when the pointer checker was on, and
  it is off in every non-debug build; and `CCALLV` looked the count up under
  `mOP - sizeof(void *)` while `_new_vect_ex()` had recorded it under the
  block base, one `int` below the object pointer. The two agreed only while a
  VM word and an int were the same width. The count is now recorded
  unconditionally and keyed on the object pointer the VM actually holds.
- This is why `vector<string>` corrupted the heap. Every element from index
  one up was memory `std::string` had never initialised, so the first
  assignment to it ran `string::resize()` on a garbage `m_len` and `m_str`.
  Whether it survived depended on whether the block happened to be zero
  filled, which is the size-dependent behaviour that was reported.
- Map entries are now retired in `_delete()` and `_delete_ex()`. Without that
  the map grows for the life of the session, and a recycled address is found
  again with a stale count, which would construct or destroy past the end of
  the new block.

Hidden VMT slot width:

- `_new_ex()` and `_new_vect_ex()` reserved `sizeof(int)` for the hidden
  method-table word while `VMT()` in `engine.h` reads it at
  `(char *)obj - sizeof(VMWord)`. On a 64-bit host the slot was four bytes
  short, so `*VMT(mOP) = vtable` wrote across the front of the heap block for
  any class with a true VMT. Both now use `sizeof(VMWord)`. `Class::size()`
  already counts that word for a class that has one, so element `i` of an
  array finds its VMT slot in its own leading word and the per-element layout
  needed no change.
- `_delete()` released a `new char[]` block with scalar `delete`; it is now
  `delete[]`.

Copying a map:

- `std::map` declared a private copy constructor and assignment operator and
  defined neither, the C++98 noncopyable idiom, so a map could not be returned
  by value: the engine correctly reported `is not defined yet`. The tree owns
  its nodes, so a member-wise copy would double free. Both are now public and
  perform a deep copy, walking the source in pre-order so `insert()` receives
  the keys in an order that reproduces the original shape. `clear()`,
  `empty()`, and `count()` are added alongside them.
- `map<string, vector<string> >` -- the `venv_spawner` case -- needed the
  array constructor fix and the map copy constructor together. The space in
  `> >` is still required; `>>` remains a syntax error to this parser.

Bundled string:

- `~string()` released its `new char[]` buffer with scalar `delete`.
- `string(const char *, int)` and `string(size_type, char)` called `resize()`
  without first initialising `m_str` and `m_len`, so `resize()` read both
  uninitialised.
- `resize()` left a freshly allocated buffer unterminated when there was no
  previous one, so `append()` concatenated onto uninitialised bytes.

An asymmetric header for scalar and array allocations -- the array cookie
suggested as a follow-up in `underc_fix_vector.txt` -- was deliberately not
taken. Scalar and array allocations currently share one header layout, and the
bundled headers rely on that: `~string()` freed `new char[]` storage through
scalar `delete`, and any user code doing the same would have started corrupting
the heap. Recording the count in a side map keyed on the object pointer keeps
the two layouts identical and leaves such mismatches as benign as they were.

Regression coverage added under `regressiontests/`:

- `local-slot-allocation.cpp`: adjacent sub-word locals of int, char, and
  short, and a scalar declared after an array.
- `new-array-construction.cpp`: constructor and destructor counts and element
  contents for `new T[n]` at eight sizes, with a static array as a guard that
  the always-correct `pcb->num()` branch has not regressed.
- `vector-of-string.cpp`: `vector<string>` growth at seven sizes, and that the
  elements of a `new string[n]` are real empty strings before assignment.
- `map-copy-semantics.cpp`: return by value, deep-copy assignment, self
  assignment, `count()`, `clear()`, and `empty()`.
- `map-of-vector-string.cpp`: the `venv_spawner` `parseEnvironment()` shape,
  built in a function, returned by value, and iterated.
- `array-allocation-churn.cpp`: 20000 allocate-and-free cycles of seventeen
  different sizes, checking that every one still constructs and destroys
  exactly `n` elements, which is what a stale map entry on a recycled address
  would break.

Verification: the release build passes 50 of 51 tests. All six new tests fail
on the unfixed sources -- `map-of-vector-string` segfaults there -- and pass
after the change. `ucri-self-import` still fails on MSVC for the reason
recorded above, and fails identically before and after this work.

## UnderC 1.5.0 host-width ABI selection (2026-08-31)

UnderC now builds and runs with a 32-bit ABI on a 32-bit host and a 64-bit ABI
on a 64-bit host, with no configuration difference between the two beyond the
toolchain that runs the build.

The starting symptom was `build-cmake-simple.ps1` failing to link
`underc-regression-runner.exe` with sixteen unresolved `__imp__ffi_*`
externals. The cause was an x86 MSVC environment paired with the x64
`libffi-380-vc-x64r` package named on `CMAKE_PREFIX_PATH`: `find_library`
accepts any `ffi.lib` it finds, and the architecture conflict is not fatal
until the first executable links. That environment has since been corrected to
x64, but the mismatch it exposed is now diagnosed rather than deferred.

Build configuration:

- `src/CMakeLists.txt` link-tests the libffi it finds on Windows with a real
  `ffi_prep_cif` call before committing to it. On a 64-bit host a candidate
  that cannot be linked is a configuration error naming the library, the
  toolchain width, and the fix; on a 32-bit host it is a warning and the build
  uses the built-in 32-bit native dispatcher instead.
- `src/cmake/FindUnderc.cmake` now includes the installed `UndercTargets.cmake`
  when it is present, so a consumer inherits the exact library, include
  directory, VM word width, and libffi the interpreter was built against
  instead of re-deriving them. `cli/` and `embed/` needed no change: they
  configure and link against an install without naming libffi at all.

ABI derivation:

- `underc/vm_types.h` derives `UNDERC_VM_BITS` from the host when the build
  system does not supply it, rather than refusing to compile. The installed
  headers are consumed by projects that never see the interpreter's own
  compile definitions, and the answer they need is the one the interpreter
  already reached for that host.
- `vm_default_object_alignment()` was `sizeof(void *)`, which understates
  aggregate alignment on a 32-bit host: MSVC x86 aligns a `double` in a struct
  to 8 while a pointer is 4-aligned, so every double-bearing aggregate was laid
  out and sized differently from the host compiler. The alignment is now the
  larger of the pointer alignment and the host's real aggregate `double`
  alignment, measured with an `offsetof` probe because the i386 System V ABI
  aligns the same `double` to 4 even though the compiler reports 8 as its
  preferred alignment. `abi-layout-host-comparison` failed on x86 before this
  and passes after it.

32-bit native calls:

- The legacy code generator copied its generated stub into a `new char[]`
  buffer and jumped to it. Heap pages are no-execute on every current desktop
  OS, so the first native call into an interpreted callback faulted. Stubs are
  now placed in executable pages through a new `alloc_executable()` in the OS
  layer, backed by `VirtualAlloc`/`VirtualProtect` on Windows and
  `mmap`/`mprotect` elsewhere.
- The same generator left its `ArgBlock` uninitialized. `copy_array` fills in
  the object pointer and argument count, but it is only called when the
  callback takes arguments, so a zero-argument callback reached
  `Engine::execute` with a garbage count and pushed that many words off the
  end of `values[]`. Reproduced as an access violation in `atexit` handling,
  which only appeared outside a debugger because the debug heap happened to
  leave a survivable value there. The block is now zeroed at generation.

Coverage:

- Added `regressiontests/host-abi-width.cpp` and the `host-abi-width` test. It
  is compiled against the public headers alone, deliberately without linking
  the library, so it fails if the headers ever stop deriving the host ABI on
  their own. It checks the VM word against the host pointer width and the
  interpreter's aggregate alignment rule against the host's own `offsetof`.

Windows results after this work: x64 passes 44 of 45 tests, and a 32-bit MSVC
build with no matching libffi passes 38 of 39. The remaining failure in both is
`ucri-self-import`, which is a GCC/Clang facility.

## UnderC 1.5.0 64-bit memory-safety repair (2026-08-31)

Investigation of the heap corruption described in `underc_fix.txt`. The
reported trigger — a bool literal as the trailing argument of a three-argument
imported native — did not reproduce in a faithful standalone repro, under
Windows full page heap or under AddressSanitizer. What the investigation did
find is a group of genuine memory-safety and 64-bit defects, several of which
produce exactly this class of delayed, allocation-sensitive corruption. The
Windows x64 regression suite went from 30 failures out of 40 to 1 out of 44.

Pointer width on LLP64 hosts, where `long` is 32 bits:

- `VMT()` located the hidden method-table pointer four bytes below the object
  rather than one VM word below it, so every virtual method call read a
  truncated table pointer and faulted. This broke `cout << ... << endl` in the
  interactive session, because the bundled `base_stream::flush()` is virtual.
- The try-block marker class stored its `CatchHandler` address in an int-wide
  field, and `throw_exception()` read it back as a whole VM word.
- The global thrown-object slot `_xo_` was declared `int`, so storing the
  thrown object's address both truncated it and wrote past the slot. It is now
  pointer-typed, and scalar catch parameters cast back from it.
- `convert_function_ptr()` cast a generated native callback stub address
  through `long`, so an interpreted function passed to a native — for example
  to `atexit` — arrived sign-extended and faulted at shutdown.
- `Program::call_main()` cast `argv` through `long` the same way.

Instruction operands:

- `emit_type_instr()` stores a `Parser::TType` handle, but `THROW_EX`, `DCAST`,
  and `SHOWI` reinterpreted the operand word as a `Type` object. Every throw
  therefore carried a garbage type and matched no catch block; the same applies
  to `dynamic_cast` and to interactive result display.

Value semantics and calling convention:

- The `COPY` opcode takes its destination from the top of the stack, but
  `COPY_BLOCK` emitted the destination first and the source last, so
  plain-struct assignment and plain-struct return by value copied backwards
  and left the destination unchanged.
- `Function`'s constructor left `m_ret_obj`, `m_cdecl`, `m_ftype`, and
  `m_default_index` uninitialized. A garbage `m_ret_obj` made `callfn()` treat
  the first real argument of an aggregate-returning native as a hidden result
  destination, which is the `libffi-aggregate-by-value` fault.
- `throw_exception()` walked the object-destruction stack from the oldest
  entry, so a nested `try` was matched by the outer handler first.

Memory safety:

- `Utils::strip_last()` scanned backwards without a lower bound and then wrote
  a terminator wherever it stopped. A program name with no directory separator
  — how CTest invokes the runner — walked off the front of `argv[0]`. This
  alone accounted for 27 of the suite's failures.
- `ifs::fetch_line()` indexed `buff[-1]` when `fgets` returned an empty line or
  reported end of file without touching the buffer.
- `string::resize()` released a `new[]` buffer with scalar `delete`, leaked the
  old buffer whenever the recorded length was zero, and could leave a truncated
  copy unterminated.
- `LineNumbersB` had virtual methods but no virtual destructor, and derived
  line-number tables own containers.
- `VStack::empty()` was written as an assignment rather than a comparison.

Bundled C library:

- The Windows C library was named `msvcrt40.dll`, which has not existed for
  many Windows releases, so every declaration under it failed to link and the
  interpreter faulted on the unresolved entry points. It is now `msvcrt.dll`.
- `fputs`, `putc`, `putchar`, `popen`, and `pclose` are interpreter built-ins
  bound to the host C runtime, so the `FILE` handles produced by
  `_get_std_stream()` and `fopen()` are never handed to a separately loaded
  runtime.
- `string.h` defines `size_t` itself instead of depending on `stdlib.h` having
  been included first, and a stray trailing NUL byte was removed from
  `direct.h`.

Regression coverage added under `regressiontests/`:

- `exception-handling.cpp`: throw and catch of scalars and class objects,
  catch by base class, `catch(...)`, nested try blocks that rethrow, and a
  non-matching inner handler falling through to an outer one.
- `object-value-semantics.cpp`: plain-struct assignment, that the assignment
  leaves its right-hand side intact, return by value into locals and globals,
  the same for a struct with a constructor, and an assignment used as a value.
- `bundled-c-library-imports.cpp`: the allocation, conversion, string, and
  memory functions imported from the platform C runtime.
- `native-shell-env.cpp` with `native-shell-env.cvc`: the `venv_spawner`
  scenario from `underc_fix.txt` — overloaded two- and three-argument natives
  imported by name, a loaded script calling them with the literal `true`,
  native heap churn between calls, interpreter shutdown, and further host
  allocation afterwards.

Verification: release and AddressSanitizer builds both pass 43 of 44 tests.
`native-shell-env`, `native-constant-arguments`, and `libffi-aggregate-by-value`
also pass under Windows full page heap. `ucri-self-import` still fails on
MSVC: `#lib $self` needs exported symbols in the running image and a manifest
generated with `nm` and `awk`, neither of which this toolchain provides.

## UnderC 1.5.0 direct language constants and native-call regression (2026-08-31)

- Removed the obsolete `ENUM_INIT` variable-initialization mode. Boolean
  literals and named enumerators are now installed directly as independently
  owned, correctly typed constants, without compatibility initializer entries
  or aliasing behavior from the historical object model.
- Kept enum storage at the interpreter's integer width and bool storage at its
  declared bool width, so loading either constant always contributes exactly
  one clean VM argument word before libffi marshalling.
- Strengthened `native-constant-arguments` to initialize UnderC with the
  standard prelude, validate the exact bool/enum value sequence across two-,
  three-, and four-argument native calls, interleave native heap allocation,
  and exercise cleanup followed by additional heap traffic.
- Rebuilt and relinked the `venv_spawner` integration against the installed
  library. Its exact three environment-edit calls with literal `true` produced
  `VENV_ONE=pre-alpha-post` and exited cleanly in repeated runs and under CDB
  with access-violation breaks enabled.
- Incremented the library, CLI, and embed projects to 1.5.0 and refreshed the
  current-feature README and release notes.

## UnderC 1.4.0 ISO literals, keywords, and native-call safety (2026-08-31)

- Gave `true` and `false` correctly sized, independently owned `bool` storage
  instead of aliasing their temporary integer initializers, and corrected bool
  constant evaluation and display to read one-byte bool objects.
- Added the standard `NULL` compatibility macro, `signed` integer spellings,
  the `wchar_t` compatibility typedef, and all eleven ISO C++ alternative
  operator spellings. Added the missing bitwise-complement bytecode mapping
  used by both `~` and `compl`.
- Reserved the remaining ISO C/C++98 keyword spellings so unsupported words
  cannot silently become user identifiers, while retaining the interpreter's
  established compatibility handling for declaration specifiers.
- Hardened scalar libffi native calls by calculating the declared VM-slot count
  before reading arguments, rejecting fixed-arity and variadic underflow
  mismatches, and restricting undeclared tail marshalling to variadic
  signatures.
- Added C, C++, and host-side native-call regressions under `regressiontests/`.
  The native test exercises repeated two-, three-, and four-argument calls with
  `true`, `false`, and named enum constants in first, middle, and trailing
  positions, and passed with Windows full page heap enabled.

## UnderC 1.4.0 header and pocket-STL layout (2026-08-31)

- Moved native compiler-private headers out of `src/` and into `include/`,
  keeping them available to the library build without exporting them to
  consumers.
- Moved the native public API and its required dependency closure into
  `include/underc/`. The public set now consists of `ucdl.h`, `ucembed.h`,
  `ucri.h`, `export.h`, `fblock.h`, `listx.h`, `mstring.h`, `vm_types.h`, and
  `xtrace.h`; CMake also generates and installs `version.h` there.
- Moved the interpreted pocket STL, C-library declarations, compatibility
  headers, and their subdirectories into `include/underc/uclstl/`. Updated the
  interpreted UCRI forwarding header for the new relative public-header path.
- Changed UnderC's default include directory from `$UC_HOME/include` to
  `$UC_HOME/include/underc/uclstl`, while preserving additional `-I` search
  paths.
- Reworked `src/CMakeLists.txt` include interfaces and install rules so native
  consumers receive only `include/underc`, the interpreted library installs as
  the `uclstl` subtree, and compiler-private headers remain source-only.
- Updated native regression consumers to include installed-style
  `<underc/...>` paths and removed the `XAPI` redefinition warning when the
  lifecycle and reflection APIs are included together.
- Corrected `cli/CMakeLists.txt` and `embed/CMakeLists.txt` to iterate all
  `CMAKE_PREFIX_PATH` entries, so an UnderC installation and a separate libffi
  prefix can be consumed in the same configuration.
- Added `public-header-layout` and `uclstl-default-search` regressions under
  `regressiontests/`, covering the public dependency closure, generated 1.4.0
  version header, and interpreted `<algorithm>`, `<map>`, `<string>`, and
  `<vector>` lookup through the new default path.
- Incremented the library, CLI, and embed CMake projects to version 1.4.0 and
  refreshed the current-feature and release documentation.

## Windows MSVC x64 build repair (2026-08-30)

The `build-cmake-vs2026-nmake-release.bat` build no longer compiled with the
Visual Studio 2026 / MSVC 19.51 x64 toolchain. Fixed the following, in build
order:

- Removed `src/eh.h` and `src/winuser.h`. These were UnderC interpreter script
  stubs, not compiler headers, and because `src/` is on the compiler include
  path they shadowed the real `<eh.h>` and `<winuser.h>` from the toolchain.
  Newer MSVC pulls `<eh.h>` into `<exception>`, so the stub broke every
  translation unit that included `<exception>`; the SDK `<winuser.h>` was
  likewise unreachable from `<windows.h>`. The canonical script copies remain
  under `include/`.
- Added 64-bit integer insertion operators (`long long`, `unsigned long long`)
  to the fake iostream (`iostrm.h` / `iostrm.cpp`). The 64-bit ABI work made
  `VMWord` / `VMFrameSlots` reach `operator<<`, which was ambiguous between
  `long`, `unsigned long`, and `int` on LLP64.
- Restricted the 32-bit MSVC inline-assembler native-call path in
  `directcall.cpp` (`legacy_callfn`, the naked `copy_array`) and the x87
  FP-exception fiddle in `hard_except.cpp` (`UnmaskFPExceptionBits`) to
  `_M_IX86`. On x64 MSVC these used unsupported `__asm`; x64 now takes the
  libffi path plus the portable `legacy_callfn` / `copy_array` fallback, and
  leaves the FP environment untouched like the non-Win32 build.
- Made `vm_word_count` / `vm_slot_count` in `vm_types.h` `constexpr` so they
  can size the fixed `VMWord slots[...]` arrays in `directcall.cpp`; MSVC has
  no variable-length-array extension.
- Replaced the GCC-only `__alignof__` with standard `alignof` in
  `Type::alignment()` (`types.cpp`).
- Compiled `dll_entry.cpp` with `WITHIN_UC` defined before `common.h` (so
  `EXPORT` resolves consistently), and gave the exported `uc_bind_variable`
  declaration in `ucembed.h` a `UC_EMBED_API` DLL-linkage macro that matches
  the `CEXPORT` definition, resolving MSVC C2375 "different linkage".
- Pointed the parser prologue at `#include "common.h"` unconditionally in
  `src/build/parser.y` and the committed `src/gen/tparser.cpp`, dropping the
  stale `_MSC_VER` path `../../../../src/common.h` that only matched the old
  `src/build/vs2010` tree layout.

The library, install step, and regression executables now build and link.
Runtime is partial: with `ffi.dll` on `PATH`, 28 of 35 regression tests pass;
`interactive-default-bootstrap`, `process-directory-listing-windows`,
`ucri-self-import`, and four native-call tests still fail or crash on Windows
x64 and remain open.

## Windows MSVC/nmake CMake build (2026-08-30)

- Added `build-cmake-vs2026-nmake-release.bat` in the repository root. It
  configures `src/` with the `NMake Makefiles` generator and a Visual Studio
  toolchain, points `CMAKE_PREFIX_PATH` at a prebuilt VC libffi, builds the
  `underc` library, and installs it under `%APPDATA%`.
- Made libffi discovery in `src/CMakeLists.txt` platform-specific. Unix keeps
  `find_package(PkgConfig REQUIRED)` and `pkg_check_modules(libffi)`; Windows
  never loads PkgConfig and instead locates libffi with `find_path(ffi.h)` and
  `find_library(ffi libffi)` resolved from `CMAKE_PREFIX_PATH`.
- Defaulted `UCL_USE_READLINE` to `OFF` on Windows, so the readline and curses
  `find_*` calls are skipped and the interpreter uses its plain console line
  editor, matching the historical `src/build/nmake` build. Other hosts still
  default the option `ON`.
- Updated `README.md` with a "Windows (MSVC / nmake)" build section covering
  the batch script, the required libffi prefix layout, and the readline and
  `selfimp` differences, and noted the MSVC build in the requirements and
  portability sections.

## Optional bison/yacc via cached parser output (2026-08-30)

- Added `src/gen` as the cache location for the bison/yacc-generated parser
  sources `tparser.cpp` and `tparser.h`, and committed a freshly generated
  copy produced from `src/build/parser.y` with GNU Bison 3.8.2.
- Reworked `src/CMakeLists.txt` parser handling: when `src/gen/tparser.cpp`
  and `src/gen/tparser.h` both exist, CMake uses them verbatim and no longer
  calls `find_package(BISON)` or checks for a bison/yacc installation. When
  either file is missing, CMake requires bison and runs `BISON_TARGET` to
  regenerate both files into `src/gen` for reuse by later builds.
- Pointed the library include path, source list, and header install rules at
  the `src/gen` copy of `tparser.h` instead of the per-build-tree copy.
- Updated `README.md` requirements, build notes, and project layout to
  describe the cached parser output and that bison/yacc is needed only when
  `src/gen` is absent.

## UnderC 1.3.9 64-bit ABI completion

- Added a System V AMD64 assembly bridge for `UCL_LIBFFI=OFF`. Native scalar
  calls now classify integer and SSE arguments, spill an unbounded number of
  stack arguments, and return integer or floating-point values without the
  former six-argument ceiling.
- Replaced the legacy-mode 32-bit callback code on maintained Linux x86-64
  builds with owned executable trampolines and a shared AMD64 callback entry.
  Both libffi and legacy callbacks now cover methods, register overflow,
  floating-point values, and recursive host/interpreter calls.
- Added cached libffi aggregate descriptions for plain structs, including
  aggregate argument and return ABI classification. Non-trivial classes,
  unions, and bit-field aggregates receive explicit diagnostics.
- Added natural per-type class-field alignment, effective aggregate alignment,
  packing caps, declared-base-type bit-field allocation, and a host comparison
  regression for mixed scalar and pointer fields.
- Widened entry element counts, function-frame slot counts, signature byte
  sizes, and Type table indices; added named byte/offset/slot metadata types,
  checked size arithmetic, and an explicit pointer-depth overflow bound.
- Added versioned `XInstructionInfo` bytecode snapshots through
  `XFunction::instruction_count()` and `instruction_at()`, while retaining the
  old pointer view as a compatibility API.
- Added CMake controls for strict conversion diagnostics, sanitizers, and
  experimental compiler-specific C++ imports. Unsupported 64-bit
  `UCL_LIBFFI=OFF` targets now fail during configuration.
- Added Linux GCC/Clang CI jobs for libffi and legacy modes, a sanitizer job,
  and a non-runnable narrow-VM compile check.
- Removed an identifier-buffer overflow in `defined(...)` processing that was
  exposed by the new Clang test matrix, and reserved space for the terminator
  in macro-substitution token buffers.
- Stopped VM-width constant stores from overwriting narrower host-ABI objects,
  and matched the native pocket-string array allocation with `delete[]`.
- Added regression sources under `regressiontests/` for aggregate calls,
  host-matched layout, UCRI snapshots, method callbacks, and recursive
  callbacks.
- Incremented the project and documented release version to 1.3.9.

## UnderC 1.3.8 runtime and build

- Restored the 1.2.9 basename behavior in `Utils::get_filepart()`, excluding
  the final directory separator so path-loaded sources receive clean synthetic
  module-initializer names.
- Added and registered `regressiontests/basename-handling.cpp`, covering
  relative and absolute native paths with and without extension stripping.
- Restored the 1.2.9 native pocket-string `compare(const char *)`, member
  `operator==(const char *)`, and non-member
  `operator!=(const string &, const char *)` overloads in `lib/string_imp.*`,
  and mirrored the public overload declarations in `include/string`.
- Restored safe native pocket-string construction from a null `const char *`,
  producing a valid empty string instead of passing null to `strlen`.
- Added and registered `regressiontests/native-pocket-string.cpp`, which pins
  the exact overload signatures and exercises null construction.
- Restored the bundled `stdio.h` seek-origin macros and the interpreted
  `stdlib.h` declarations for `getenv`, `system`, `_gcvt`, and `atexit`.
- Added portable built-in bridges for `_gcvt` and `_access`, avoiding reliance
  on Microsoft-only exported symbol names, and made interpreted `atexit`
  callbacks run in reverse registration order before callback closures are
  released.
- Restored the public interpreted `RangeError` class in `uc_except.h`.
- Added and registered `regressiontests/bundled-c-library.cpp`, covering every
  restored macro, declaration, callback, and exception type.
- Moved the maintained grammar from `src/parser.y` to `src/build/parser.y` and
  updated current and legacy build references.
- Moved the Linux self-import filter from
  `src/build/linux-x86/XNAMES.AWK` to `src/build/xnames.awk`.
- Added the explicit CMake `selfimp` target, generating
  `lib/uclr/self.imp` by default and installing it under `lib/uclr` when it
  exists.
- Replaced fixed 32-bit `nm` addresses with the address-free `UC3 AUTO`
  manifest format. Self-imports now resolve exported process symbols at
  runtime, propagate executable symbol export flags to installed static
  consumers, support PIE/ASLR, retain pointer-width legacy address parsing,
  and match current Itanium ABI symbols when the historical mangler omits
  template-pointer or variadic details.
- Routed `ucri.h` autoloading through `$UC_HOME/lib/uclr/self.imp`, repaired
  manifest parsing through the custom input stream, and added a UCRI
  self-import regression.
- Changed the interactive `defs.h` fallback from `$UC_HOME/defs.h` to
  `$UC_HOME/uclresource/defs.h`, so starting `ucc` from the repository root
  loads `classlib.h` and makes bundled types such as `string` available.
- Preserved a working-directory `defs.h` as an explicit local override.
- Checked for that optional override before asking the parser to open it,
  preventing a stale `Cannot open defs.h` error when the fallback is used.
- Routed `#help` and `--help` resource lookup through `$UC_HOME/uclresource`
  and updated the command-line help text to describe the new location.
- Removed the obsolete duplicate `src/defs.h` and added an interactive
  bootstrap regression that starts in the repository root and uses `string`.
- Retained the project version at 1.3.8.

## UnderC 1.3.7 architecture and interop completion

- Enforced the runnable invariant that `VMWord` can carry a host pointer.
  Narrow VM configurations now require the explicitly non-runnable
  `UCL_COMPILE_ONLY_NARROW_VM` option and are refused by `uc_init`.
- Replaced the active 32-bit x86 callback generator with owned libffi closures
  for free functions and methods, including integer, pointer/reference, float,
  double, zero-argument, and long argument-list signatures. The legacy emitter
  remains compiled when `UCL_LIBFFI=OFF`.
- Removed the libffi-mode fallback to `legacy_callfn`; unsupported native C++
  objects by value now receive a deterministic pointer/reference diagnostic.
- Replaced packed 32-bit `Type` metadata and its two-bit pointer depth with
  semantic fields and interned parser handles, eliminating aliasing and table
  index limits in the maintained representation.
- Made the public UCRI instruction operand pointer-width and removed its stale
  22-bit/32-bit layout promise.
- Corrected bit-field allocation to use the declared integer base type,
  allocation-unit boundaries, zero-width separators, and width validation.
- Added libffi callback and deep-pointer regression coverage and verified the
  complete default and legacy-mode suites.

## 2026-08-20

### UnderC 1.3.6 embedded source loading

- Corrected the public `uc_load` declaration to match its status-returning
  implementation and made its path parameter `const char *` throughout.
- Consolidated the native embedding example into `embed/main.cpp`; it directly
  executes code that changes bound `count` and `multiplier` host variables,
  then initializes a string, loads `embed/ucload.cpp`, and executes its
  function to print the changed `Hello from underc` value.
- Added `regressiontests/uc-load.cpp` and registered it with CTest to cover the
  const path, load status, loaded assignment, and resulting output.
- Updated current feature documentation and incremented the project version to
  1.3.6.

### UnderC 1.3.5 host variable embedding

- Removed `uc_init_ref`, which rendered host pointers into interpreted source
  with a 32-bit format and could truncate addresses on 64-bit hosts.
- Added the C-compatible `uc_bind_variable` API with explicit scalar type and
  status enums, identifier validation, duplicate detection, initialization
  checks, and direct reference registration in the global symbol table.
- Added `regressiontests/embed-binding.cpp` to verify live two-way `int` and
  `double` updates and error statuses.
- Added the standalone `embed/` CMake consumer, where host variables defined
  and printed in `main.cpp` are changed by interpreted code evaluated from
  `ucinteractive.cpp`.
- Updated current feature and embedding documentation and incremented the
  project version to 1.3.5.

### UnderC 1.3.4 bytecode optimization

- Added command-line parsing and validation for `-O0`, `-O1`, `-O2`, and
  `-O3`; bytecode optimization defaults to disabled.
- Implemented an internal V8-inspired optimization pipeline with level-one
  local stack peepholes, level-two constant folding and unary reduction, and
  level-three algebraic simplification and jump threading.
- Enabled the existing safe one-instruction function inliner as part of
  `-O3` and retained `-F` as its explicit compatibility switch.
- Kept optimized bytecode instruction indices stable by replacing eliminated
  instructions with `NOP`, preserving branches, switch tables, breakpoints,
  line mappings, and disassembly offsets.
- Added and registered `regressiontests/bytecode-optimization.cpp` at all four
  optimization levels, updated current feature documentation, and incremented
  the project version to 1.3.4.

### UnderC 1.3.3 portable process pipes

- Exposed `popen` and `pclose` to interpreted programs through host wrappers
  that select POSIX `popen`/`pclose` on Linux and Microsoft CRT
  `_popen`/`_pclose` on Windows.
- Declared the portable process-pipe API in the bundled `stdio.h`.
- Corrected the console-aware `fgets` bridges to preserve the host C
  function's null return at end-of-file for ordinary files and process pipes.
- Added platform-selected Linux `ls` and Windows `dir` regression programs;
  each captures and prints the listing of the repository root and checks for
  `README.md`.
- Updated current-feature documentation and incremented the project version
  to 1.3.3.

### UnderC 1.3.2 import examples and switch labels

- Moved `examples-import/` to `examples/import/` and updated maintained paths.
- Ported the native example export macros and includes to current Linux
  compilers, supplied explicit default constructors where imported symbol
  signatures require them, and added a runnable scalar import smoke program.
- Built every native import implementation as a shared library and parsed the
  interpreter-facing declarations with the current interpreter.
- Replaced size-based `case` constant decoding with the interpreter's constant
  integer evaluator, fixing valid integer labels on 64-bit native-ABI builds.
- Added and registered `regressiontests/switch-in-function.cpp`.
- Updated current-feature and release-delta documentation and incremented the
  project version to 1.3.2.

### UnderC 1.3.1 interpreter and native-call fixes

- Added default-on `UCL_LIBFFI` native dispatch with dynamically allocated
  argument metadata and no fixed argument-count ceiling; preserved the prior
  dispatcher behind `-DUCL_LIBFFI=OFF`.
- Corrected 64-bit pointer-to-pointer indexing, arbitrary-size address scaling,
  pointee-width dereferences, void-pointer native returns, double argument slot
  accounting, and pointer-to-const increment expressions.
- Added a fixed-signature floating-point output bridge used by the bundled
  streams, plus regressions for `argv` indexing and eight-argument native calls.
- Moved the remaining C and C++ diagnostic and regression sources from `/tmp`
  into `regressiontests/` so they are retained with the source tree.
- Incremented the library and documented release version to 1.3.1.

### Runnable example applications

- Added `examples/uccalc.cpp`, a command-line mathematical expression parser
  supporting precedence, parentheses, unary signs, exponentiation,
  floating-point values, input errors, and division-by-zero diagnostics.
- Added `examples/tkgui.c`, which dynamically imports Tcl/Tk and displays a
  window with a button that closes it.
- Documented how to run both examples with `ucc` and listed their runtime
  requirements in the root README.

### Documentation and language-support audit

- Refocused the root README on current capabilities and operation, moved
  missing-feature and known-error notes into `PLAN.md`, and removed planning
  references from the README.
- Added a root `PLAN.md` defining the staged parser, type-system,
  preprocessor, execution, hosted-library, diagnostics, and validation work
  required before UnderC can claim ISO C90 conformance.
- Clarified that GNU C++98 is the host build mode, while the interpreted
  language is a non-conforming C++98-era subset rather than a complete ISO
  C++ implementation.
- Documented `.c` mode as a shared-parser, C90-like subset and listed missing
  C90, C99, C11/C17, and C23 language facilities, including ignored declaration
  qualifiers and absent modern type, initializer, array, macro, and generic
  features.
- Added a documentation index that separates maintained guidance from archival
  1.2.4/1.2.9 manuals and calls out obsolete build, x86, fixed-width VM, and
  container claims, including the empty Linux and placeholder Windows notes.
- Corrected the root README's native-import example directory name from
  `import-examples/` to `examples-import/`.

### Runtime, parser, enum, and container follow-up

- Fixed host heap corruption caused by applying UnderC's four-byte interpreted
  VMT prefix to global C++ `new`/`new[]` allocations on 64-bit systems.
- Added an explicit native-call method flag so ordinary built-ins invoked from
  an interpreted method no longer receive the current object as a spurious
  first argument. This repairs `new[]` inside constructors and member methods.
- Replaced parser `Type`/semantic-word aliasing with `memcpy` encode/decode
  helpers and a compile-time representation-size check.
- Made repeated named enums compare membership and values, reject changed or
  incomplete repeats and unrelated enumerator collisions, and retain the
  original enum and entries as authoritative.
- Added zero-argument scalar value initialization (`T()`) to the supported
  functional-cast path.
- Reworked the bundled vector's allocation, capacity, copy, self-assignment,
  clear, resize, reserve, push/pop, and range-assignment behavior. Hardened the
  generic map's empty insertion, iterator conventions/decrement, destruction,
  and copy policy; native map specialization remains opt-in.
- Added a CTest-owned interpreter runner and reusable regression programs for
  allocation in methods, reference returns, bitwise precedence, precise enum
  rejection, vector operations, and generic-map insertion/destruction behavior.
- Documented the remaining interpreted const-overload and map value-access
  limitations in the README.

### Library and CLI source-layout separation

- Replaced the monolithic console build with an installable `underc` static or
  shared library and a separate `cli/` consumer project that builds `ucc`
  through `find_package(Underc)` and `CMAKE_PREFIX_PATH`.
- Added `UCL_SHARED` (default `OFF`) and the corresponding shared-library
  compile definition, replacing the historical shared-library switch.
- Renamed the old library switch namespace to `UCL_`; CLI-specific
  switches use the `UCC_` prefix, including `UCC_SHARED`.
- Added `src/cmake/FindUnderc.cmake`, an imported `Underc::underc` target, and
  install rules for the library, public headers, generated parser header,
  exported targets, find module, and CLI executable.
- Preserved the historical GNU C++98, Bison, non-debug `-O1`, readline/curses,
  and dynamic-loader build settings found in `src/build`.
- Verified static and shared library builds, installation to separate prefixes,
  and compilation, linking, installation, and startup of both CLI consumers.

## 2026-08-18

### Native ABI compatibility and 1.2.9 parity follow-up

- Restored native object-layout semantics by default: interpreted `int` and
  ordinary enum objects use host `int`, `long` uses host `long`, and pointers
  use the host pointer width, while VM evaluation and transport slots retain
  the independently configurable `UNDERC_VM_BITS` width.
- Added the `UCL_DISABLE_NATIVE_ABI` CMake option. It defaults to `OFF`; setting
  it to `ON` selects the experimental legacy VM-width object model for `int`,
  enum, and `long`, at the cost of native structure ABI compatibility.
- Added width-aware integer aliases and a default object-alignment helper, and
  corrected primitive, enum, pointer, array, class-member, table, stack, and
  frame sizing/alignment to use the selected object model.
- Added dedicated pointer load/store VM instructions so pointer objects retain
  pointer width without changing the width of interpreted integer objects.
- Corrected pointer-sized storage and conversions in exception handlers,
  function offsets, virtual-method tables, OS ordinals, pointer arithmetic,
  array strides, and the execution engine.
- Restored the parser's bitwise-OR expression path, made parser semantic type
  payloads explicitly 32-bit, and accepted compatible repeated enum
  declarations while keeping the first declaration authoritative.
- Applied const-correctness fixes throughout the migrated compiler and removed
  the resulting warnings from the supported native and VM-width builds.
- Added runtime regression programs for native/VM-width ABI layout, member
  templates, and repeated enum declarations, and registered them with CTest.
  Both default and `UCL_DISABLE_NATIVE_ABI=ON` configurations pass all six
  registered tests.
- Verified 16- and 32-bit VM configurations as compile-only portability checks
  on the 64-bit host. They still report expected pointer-narrowing diagnostics
  and are not runnable when a VM word cannot hold a host pointer.
- Audited the bundled `vector` and `map` implementations. Some migration
  defects were corrected, but their runtime examples still fail; these
  historical container implementations remain an explicitly unresolved gap.
- Renamed `examples/` to `regressiontests/` and preserved the exploratory
  UnderC sources previously held only in `/tmp` so future migration work does
  not depend on ephemeral files.

### Configurable VM architecture

- Added `UNDERC_VM_BITS`, accepting 16, 32, or 64 and defaulting to the host
  pointer width detected through `CMAKE_SIZEOF_VOID_P`.
- Added `VMWord`/`VMUWord` target-width types and centralized conversions
  between VM values and host pointers.
- Converted instruction operands, execution-stack slots, stack/base pointers,
  argument blocks, symbol-entry payloads, constants, switch tables, frame
  sizing, and the native-call bridge to the configured VM word.
- Made VM slots, local-variable transport units, stack allocation, and
  floating-point slot counts derive from the VM representation. Native object
  widths are now separated from those slots as described above.
- Removed packed 32-bit instruction fields and fixed instruction copying,
  offsets, and the end-of-code sentinel for the native instruction size.
- Removed the remaining `-fpermissive` dependency after correcting pointer and
  integer conversions and replacement delete exception specifications.
- Fixed an empty-input-line underflow found during runtime validation.
- Built the complete console target with 16-, 32-, and 64-bit VM settings and
  ran a 64-bit pointer/native-call smoke program that produced `vm-value=42`
  and exited successfully.

- Added `src/CMakeLists.txt` for the console interpreter, using GNU C++98,
  Bison-generated parser sources, optional readline/curses support, dynamic
  loader linkage, and the historical non-debug `-O1` setting.
- Updated obsolete comma-separated Bison symbol declarations and removed
  duplicate token declarations so Bison 3.8 can generate the parser.
- Replaced GCC's i386 stack-manipulating inline assembly with a portable native
  call dispatcher for current compiler architectures. Unsupported calls with
  more than six native arguments now fail explicitly.
- Replaced removed `_itoa`, `_ltoa`, `_ultoa`, and `_gcvt` uses with available
  formatting functions and corrected pointer formatting to `%p`.
- Corrected `Type` initialization to clear its actual 32-bit representation
  instead of overwriting adjacent memory through a host-width `long`.
- Selected this version's bundled string and stream implementations in the
  console build, adapted readline prompt construction to those streams, and
  excluded Windows-only or placeholder translation units.
- Added this README with build, usage, feature, layout, and portability
  documentation.
- Verified configuration, Bison generation, compilation, and linking with
  CMake 4.4.2, Bison 3.8.2, and GCC 16.1.1 on a 64-bit Linux host.
