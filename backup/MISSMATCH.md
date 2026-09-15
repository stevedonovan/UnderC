# Documentation mismatches

This file records statements in the former `doc/` material that do not
describe UnderC 1.3.1. It is not a list of current features or release notes.

## Language and library claims

- The 1.2.0 notes call UnderC an “ISO C++” interpreter and the 1.2.4 readme
  says it implements a generous ISO subset. UnderC implements a non-conforming
  C++98-era dialect and a shared-parser, C90-like mode; the exact boundary is
  documented in `LANGUAGE_SUPPORT.md`.
- The old documents imply broad bit-field support. The grammar accepts only a
  restricted member form, so complete C or C++ bit-field behavior should not
  be assumed.
- `mutable`, `inline`, `typename`, `register`, and `volatile` are accepted or
  discarded in places without their standard semantics. Modern C and C++
  language editions are not implemented.
- The 1.2.9 notes say `vector::assign` “should also be a ctor version”; no
  iterator-range vector constructor was added. Out-of-class member-template
  definitions remain unsupported.
- The 1.2.9 map example prints `mi->end`; this is a typographical error for
  `mi->second`. The bundled map has no const `operator[]`, `find`, or const
  iterator API, and intentionally prevents copying instead of providing
  standard map copy semantics.
- The old library manual describes the bundled headers as pocket substitutes
  and contains provisional APIs and examples. They remain compatibility
  headers, not a complete standard library, and their behavior is only covered
  where current regression tests exist.

## Runtime and architecture claims

- `DISCUSSION` describes fixed 32-bit packed instructions, four-byte VM words,
  a fixed data segment, and four-byte object/VMT offsets. The current VM word
  is configurable as 16, 32, or 64 bits, defaults to host pointer width, and
  uses a native-sized instruction representation. Narrower-than-host builds
  are compile checks, not runnable configurations.
- Historical portability notes require x86 inline assembly and name GCC 2.95,
  GCC 2.96, MinGW, Visual C++ 6, and BeOS. The maintained console build uses a
  portable native-call dispatcher on current GNU/Clang hosts. Version 1.3.1
  uses libffi by default for ABI-aware calls without a fixed argument limit;
  the previous dispatcher remains available through `UCL_LIBFFI=OFF`.
- The old help says `#r` runs in its own thread and console window. That is a
  historical Windows GUI behavior; the maintained CLI runs through the console
  program path.
- Claims about catching hardware faults, graphical WCON behavior, GTK+, VTK,
  YAWL, Windows DLL import ordinals, compiler-specific class import, and native
  callbacks have not been revalidated for the current supported build.

## Build and packaging claims

- The former build notes describe monolithic executables, old makefiles,
  Bison 1.24 skeleton overrides, Visual Studio workspaces, and retired macros
  such as `_USERDLL` and `UCL_EXPORTS`. Version 1.3.1 builds and installs the
  `underc` library first and builds `ucc` as a separate CMake consumer.
- `compile_information_linux32-64.txt` was empty and the Windows counterpart
  contained only “64bit”. Neither documented a working build.
- The old package readme identifies itself as 1.2.4w and expects packaged
  binaries and headers under an executable directory. The current source tree
  is version 1.3.1 and uses `UC_HOME` only to locate the repository's
  interpreted `include/` and `lib/` support at runtime.
