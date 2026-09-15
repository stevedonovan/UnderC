# History

Changes are listed newest first. **Prepend** new entries to the top of this
file, under a `## <date> — <summary>` heading.

---

## 2026-09-07 — UnderC is mandatory; CMake reduced to a plain package consumer

venv (renamed from `venv_spawner`) is now built and installed by the UnderC
repository's `build-cmake-install.ps1` alongside the interpreter library and
`ucc`.

### Changed

- **`USE_UNDERC` is gone.** A `.cvc` file is C++ run by the embedded
  interpreter, so a build without it could only print an error. Removed the
  CMake option, the `VENV_USE_UNDERC` compile definition, the
  `#ifdef VENV_USE_UNDERC` pure-C `main()` in `src/main.c` and its "rebuild
  with `-DUSE_UNDERC=ON`" message.
- **`CMakeLists.txt` reduced to the shape of `cli/CMakeLists.txt`.** UnderC is
  found only through `find_package(Underc REQUIRED MODULE)` against
  `CMAKE_PREFIX_PATH` / `CMAKE_INSTALL_PREFIX`. Removed the `Underc_ROOT` /
  `$DEP_DIR` / `C:/pkg/dep` hint search, the manual `UndercTargets.cmake`
  include, the imported-target prefix recovery, the baked-in
  `VENV_UNDERC_PREFIX` (build-time default `UC_HOME`), and the `ffi.dll`
  copy/install step. The interpreter is either on the prefix path or it is not.
- `src/underc_bridge.cpp` includes `<underc/ucdl.h>` (the installed public
  path) instead of `<ucdl.h>`.
- `UC_HOME` auto-detection no longer has a `build-time prefix` candidate;
  `$UC_HOME`, `$DEP_DIR/underc`, next-to-`venv`, above-`venv`, and the built-in
  default remain, and `-uclp` still overrides.

### Build

```
. .\build-cmake-install.ps1     # from the UnderC repo root
```

builds `underc.lib`, `ucc.exe` and `venv.exe` into one prefix. A direct
configure is unchanged except that `-DUSE_UNDERC=...` is no longer accepted:

```bat
cmake -G "NMake Makefiles" -B build -S venv ^
      -DCMAKE_PREFIX_PATH=%DEP_DIR%\underc-vc-x64r ^
      -DCMAKE_INSTALL_PREFIX=%DEP_DIR%\underc-vc-x64r
```

## 2026-09-01 — the environment-diff API, unblocked

The two engine defects that stopped this work yesterday were fixed in UnderC
1.5.0 and the new interpreter installed to the prefix, so the API described in
the previous entry as *Blocked* is now implemented and the shell-less MSVC
example runs.

### New

- **`parseEnvironment(const string& text)` → `map<string,vector<string> >`**
  (`examples/venv/main.cpp`). Parses a `SET` (Windows) or `env` (Linux) dump
  into *variable name → its value split on the host's list separator*, one
  `NAME=VALUE` per line, `\r\n` and `\n` both accepted. A line without a `=`
  is skipped, which is what keeps the banner `vcvars64.bat` prints ahead of its
  `SET` output out of the result; so are cmd.exe's `=C:=…` and `=ExitCode=…`
  pseudo variables, whose name is empty. A value holding no separator becomes
  a single-element vector, so scalars and lists are handled uniformly.

- **`findAddedEntriesEnvironment(map& before, map& after)` →
  `map<string,vector<string> >`**. Returns only what `after` gained: a
  variable `before` did not have at all, with its whole value, and for a
  variable both have, the fragments `before` lacked, in the order `after`
  lists them. Variables that did not change are left out entirely, and so are
  ones that only lost fragments — it is an *additions* diff, which is what
  adopting a toolchain script's effect calls for.

- **`venvPreEnv(map<string,vector<string> >& entries)`**, an interpreted
  overload of the native two-argument `venvPreEnv()`. Prepends every entry to
  the variable it belongs to, joined with the host's list separator. A
  variable that already has a value is prepended to, separator included, so
  the existing entries stay reachable behind the new ones; one that does not
  exist yet is set outright, so a freshly introduced scalar such as
  `VSCMD_VER` does not end up with a stray separator glued to it.

- Supporting helpers in the same file: `venvPathSep()`, which picks `;` or `:`
  at run time from `COMSPEC` / `WINDIR` because the interpreter defines no
  `_WIN32`; `venvSplitEnvValue()`, which drops empty fragments (a trailing
  separator is normal in `PATH`); and `venvIsEnvName()`.

### Changed

- **`examples/win_msvc2026_auto.cvc` runs.** It captures `SET`, captures
  `call vcvars64.bat & SET` in the same throw-away `cmd.exe`, diffs the two,
  prepends the difference and then runs `cl` — with no persistent shell open.
  Its header now says where the helpers come from instead of carrying a
  *NOT RUNNABLE YET* warning.

- `README.md`: new section *Turning that output into an environment: the diff
  helpers*; *Known limits of the embedded engine* replaced by *What the
  embedded engine needs*, which records the two defects as fixed and the
  version they were fixed in; *The shell-less variant, and why it is not
  ready* is now *The shell-less variant* and describes a working example; new
  feature-matrix row for environment diffing.

### Fixed upstream — UnderC 1.5.0, 2026-09-01

venv now expects that version. Both defects were reported from here in
`underc_fix_vector.txt`, which now lives in the UnderC source tree:

- **`new T[n]` constructed element 0 only**, so every element after the first
  was raw memory and `std::string::operator=` on one ran `resize()` over a
  garbage `m_str` / `m_len`. Two independent faults: `_new_vect()` recorded
  the element count only when the pointer checker was on, which it is not in a
  release build, and `CCALLV` looked that count up under a key that agreed
  with the one `_new_vect_ex()` wrote only while a VM word and an `int` were
  the same width. The count is now recorded unconditionally and keyed on the
  object pointer the VM holds. That is what made `vector<string>` corrupt the
  heap in a way that depended on the allocation size.
- **`std::map` was noncopyable** — copy constructor and `operator=` declared
  private and left undefined — so it could not be returned by value. Both are
  now public and deep-copy the node tree; `clear()`, `empty()` and `count()`
  were added alongside.

The `> >` spacing in `map<string, vector<string> >` is still required; `>>`
remains a syntax error to that parser.

### Verified

Rebuilt with `. .\build-cmake-simple.ps1` against the new interpreter, then run
from an environment with the MSVC variables removed and `PATH` cut down to
`C:\Windows\System32`:

```
venv.exe -ucll .\examples\venv\main.cpp .\examples\win_msvc2026_auto.cvc
  venv: [1] capturing: SET
  venv: [1] command exited with code 0 (6812 bytes captured)
  venv: [2] capturing: call "...\vcvars64.bat" & SET
  venv: [2] command exited with code 0 (11185 bytes captured)
  added 9 variables: PATH +19, INCLUDE +9, LIBPATH +6, LIB +5, Platform,
                     VCToolsInstallDir, VSCMD_VER, __VSCMD_PREINIT_*
  venv: [3] running: cl
  Microsoft (R) C/C++ Optimizing Compiler Version 19.51.36256 for x64
```

`cl` is not on the stripped `PATH` before the diff is applied. A separate unit
check parsed a synthetic dump with CRLF endings, a `=C:=` pseudo variable and a
banner line, and confirmed the diff reports only the added entries.

---

## 2026-08-31 — `-ucll`, bare configuration names, and `venvExeCommandString()`

### New

- **`-ucll <file>` loads an extra C / C++ source into the interpreter before
  the configuration is processed.** Repeatable; the files are loaded in the
  order given, after the auto-loaded venv-directory sources and before the
  `.cvc` itself, so a configuration can call what they define. `-ucll=<file>`
  and `--underc-load` are accepted too, and each file is listed in the banner:

  ```
  venv.exe .\build.cvc -ucll .\msvc_helpers.cpp -ucll toolchains.cpp
  ```

  Like an auto-loaded file, a `-ucll` file is parsed in its own module scope —
  it needs its own `using namespace std;` and must not define `main()`.

- **A configuration (or `-ucll`) argument that does not say where it lives is
  looked up in the per-user venv directory** — `%APPDATA%\venv` on Windows,
  `$XDG_CONFIG_HOME/venv` (else `$HOME/.config/venv`) on Linux: the same
  directory whose `.c` / `.cpp` files are auto-loaded. Absolute paths and
  paths that start with `.\`, `./`, `..\` or `../` are used verbatim, so
  `.\examples\foo.cvc` still means the one in the current directory. A bare
  name that is not in the venv directory is kept as written, which leaves the
  current directory working as a fallback and keeps error messages pointed at
  what the user typed. The banner prints the resolved path:

  ```
  venv.exe msvc_env.cvc
    config   : C:\Users\you\AppData\Roaming\venv\msvc_env.cvc
  ```

  New `venv_config_resolve_source_path()` in `config.c` implements the rule;
  `main.c` applies it to the config argument and to every `-ucll` value.

- **`venvExeCommandString(const char* cmd)` runs a command and returns its
  output as a string.**

  ```cpp
  string vars = venvExeCommandString("SET");                    // Windows
  string vars = venvExeCommandString("env");                    // Linux
  ```

  Unlike `venvExeCommand()` it always goes through the host command interpreter
  (`%COMSPEC% /s /c` on Windows, `/bin/sh -c` on Linux), because what a config
  wants to read back is normally a shell built-in or the effect of a script
  (`SET`, `env`, `call vcvars64.bat & SET`) rather than an executable image —
  shell syntax is therefore available inside `cmd`. The child runs with the
  environment the config has built so far and in the configured root directory.
  Only stdout is captured; stderr still reaches the terminal, so a failing
  command explains itself instead of poisoning the returned string.
  `venvLastExitCode()` reports its status, and the progress line names the
  captured size:

  ```
  venv: [1] capturing: SET
  venv: [1] command exited with code 0 (12226 bytes captured)
  ```

  New `venv_process_spawner_capture()` in `process_spawner.c` (both platforms:
  `CreatePipe` + `CreateProcess` inside the usual Job Object on Windows,
  `pipe`/`fork`/`execl` after the usual root pivot on Linux), plus
  `exec_command_capture()` and the `venvExeCommandString` import in
  `underc_bridge.cpp`.

### Blocked: the environment-diff API

`parseEnvironment()`, `findAddedEntriesEnvironment()` and the `venvPreEnv()`
overload taking a parsed environment were **not implemented**. Both halves of
the intended design run into defects in the embedded UnderC engine, and per the
project rule the work stops at the interpreter rather than routing around it.
Two minimal reproductions, run against the current build:

**1. `vector<string>` crashes as soon as it holds more than one element.**

```cpp
int main(int argc, char* argv) {
    vector<string> v;
    v.push_back("a");
    v.push_back("b");     // <-- growth reallocation
    venvPrint("reached");
    return 0;
}
```

`reached` is never printed; the process dies with a segmentation fault (exit
139) inside the second `push_back`. Giving the vector a `reserve(16)` first
moves the crash to the end of the run — the elements are then filled in and
printed correctly, and the fault happens when the vector is destroyed. A
`vector<int>` grows to 20 elements without trouble and a `list<string>` is
fine in both places, so the defect is in `vector`'s handling of a non-POD
element type, not in `string` and not in the container generally. A vector
holding exactly one string survives; a local one holding two does not.

**2. `map` has no copy constructor, so it cannot be returned by value.**

```cpp
map<string,string> build() { map<string,string> m; m["A"] = "x"; return m; }
int main(int argc, char* argv) {
    map<string,string> m = build();   // <-- needs map's copy ctor
    venvPrint(m["A"].c_str());
    return 0;
}
```

```
map<std::string,std::string>::map<std::string,std::string>(
    const std::map<std::string,std::string>& ) is not defined yet
```

That is exactly the shape `map<...> env1p = parseEnvironment(env1);` needs.

What does work, should the design move that way: a `map<...>&` **out-parameter**
(`void parseEnvironment(const string& in, map<string,list<string> >& out)`)
drives fine end to end, including iterating a `map<string, list<string> >` and
its nested lists. Note also that the parser needs `map<string, list<string> > `
with a space — the `>>` spelling is a syntax error.

`examples/win_msvc2026_auto.cvc` therefore keeps the intended shape but is
marked not runnable at the top, and `examples/venv/main.cpp` documents why the
two functions are absent.

### Changed

- `examples/win_msvc2026_auto.cvc`: uses `venvExeCommandString()` (the name the
  engine now imports; the file previously called `venvExeCommandStr`), spells
  the nested template `map<string,vector<string> >`, and carries a header
  explaining what blocks it.
- `examples/venv/main.cpp`: lists `venvExeCommandString` in the venv* API
  reference at the top and documents what it captures.
- `README.md`: new *Reading a command's output back*, *Where configuration and
  `-ucll` files are looked up*, *Loading extra sources with `-ucll`* and *Known
  limits of the embedded engine* sections; `venvExeCommandString` in the API
  table; `-ucll` in the option table and synopsis; a capture row in the feature
  matrix; the shell-less MSVC variant and its status; updated architecture map.
- The usage text now lists `-ucll`, `venvExeCommandString` and the bare-name
  lookup rule.

---

## 2026-08-31 — Fix: a wrong UnderC prefix crashed the launcher silently; standalone commands print to the terminal

### Fixed

- **venv died silently after its banner and never ran the config's
  commands.** Running

  ```
  venv.exe .\examples\win_msvc2026_direct.cvc
  ```

  printed the `starting` banner and then stopped — no `loading …` line, no
  `cmake --help`, no error (exit status 139 / segmentation fault).

  Cause: the `-uclp` default was the hardcoded `C:\pkg\dep\underc`, which does
  not exist on a machine whose UnderC lives elsewhere (here `L:\pkg\dep\underc`).
  venv put that path into `UC_HOME` and called `uc_init()` regardless.
  UnderC appends `include/underc/uclstl` to `UC_HOME` and
  `Main::process_command_line()` returns `false` when that directory is missing —
  but `uc_init()` ignores the failure and goes on to evaluate its prelude with
  **no include path set at all**, which segfaults inside `#include <classlib.h>`.
  Every path — a stale default, a mistyped `-uclp`, a moved install — failed the
  same silent way. As a bonus, the hardcoded default also overrode a correctly
  set `UC_HOME` in the environment.

  The prefix is now resolved and validated *before* the interpreter is started
  (`venv_underc_resolve_prefix()`), so a bad prefix is a clear error message
  instead of a crash.

- **On Windows, a standalone `venvExeCommand()` produced no visible output.**
  The child was created with `CREATE_NEW_CONSOLE` and `bInheritHandles = FALSE`,
  so it ran in a separate console window that closed with it: `cmake --help`
  really did run, but nothing reached the terminal that started venv,
  which read exactly like the command had been skipped. The child now inherits
  venv's `stdin` / `stdout` / `stderr` (`STARTF_USESTDHANDLES` with the
  parent's std handles, `bInheritHandles = TRUE`, no `CREATE_NEW_CONSOLE`), so
  its output appears inline between the progress and exit-code lines — matching
  the persistent-shell path, which already relayed output. `stdout` / `stderr`
  are flushed before the spawn so the interleaving is in the right order. When a
  std handle is not available (a GUI parent) the explicit handles are skipped and
  plain handle inheritance is used.

### New / changed

- **The UnderC library prefix is auto-detected.** `-uclp` is now optional; when
  omitted, the first candidate whose `include/underc/uclstl` exists wins:
  `$UC_HOME`, the prefix the binary was built against, `$DEP_DIR/underc`, the
  directory holding `venv`, its parent (an installed `bin/` layout),
  then the built-in default (`C:\pkg\dep\underc` / `/usr/local`).
- **The banner names the prefix and its source**, e.g.
  `uclp     : L:/pkg/dep/underc (build-time prefix)`.
- **An explicit `-uclp` that is not an UnderC install is a hard error**, naming
  the missing `include/underc/uclstl` directory and, when auto-detection finds
  one, a prefix that would work. When nothing at all is found, the error lists
  every candidate that was tried.
- **CMake bakes the prefix it linked against into the binary** as
  `VENV_UNDERC_PREFIX`, which becomes the run-time default `UC_HOME`, so a build
  looks for the STL headers where it was actually built against. The configure
  step prints `-- venv: UnderC prefix <path>`. The prefix is recovered
  from the imported `Underc::underc` target when the package came from
  `find_package()` rather than from the hint list.
- **CMake hint order changed:** an explicit `-DCMAKE_PREFIX_PATH` now outranks
  `$DEP_DIR/underc` and the hardcoded `C:/pkg/dep/underc` instead of coming last.
- `venv_underc_init()` now validates the prefix itself and reports a proper
  error, and checks `uc_init()`'s return value instead of discarding it; both
  fill the caller's `err` buffer, which the function previously ignored.
- `src/underc_bridge.cpp`: new prefix-resolution section — `is_directory()`,
  `path_join()`, `uclstl_dir()`, `prefix_is_valid()`, `parent_dir()`,
  `executable_dir()`, `collect_candidates()` and the exported
  `venv_underc_resolve_prefix()`.
- `src/underc_bridge.h`: declares `venv_underc_resolve_prefix()` and now owns
  `VENV_DEFAULT_UCLP`, which moved out of `main.c` so the usage text and the
  resolver share one definition. `main.c` includes the header unconditionally
  (declarations only, so a build without UnderC is unaffected).
- Docs: `README.md` gains a *Finding the UnderC library prefix* section, notes
  that standalone command output is inline, documents the baked-in prefix and
  the CMake search order, and lists the `build-cmake-simple.ps1` /
  `build-cmake-install.ps1` wrappers.

---

## 2026-08-31 — `venvSetEnv` / `venvPreEnv` / `venvAppEnv` take an optional `inShell` flag

### Fixed

- **A shell-less `venvExeCommand()` could not find an executable that a
  `venvPreEnv("PATH", …)` had just added** (Windows: `CreateProcess('cmake …')
  failed: The system cannot find the file specified. (code=2)`). The cause:
  Windows `CreateProcess()` resolves the executable image through the **calling
  process's** `PATH`, never through the environment block handed to the child,
  so the new `PATH` only ever reached the spawned process — too late to locate
  it. The env editors now also mirror their result into venv's own
  process environment (`_putenv_s` / `setenv`), which the image search and every
  inheriting child then see.

### New / changed

- **`venvSetEnv`, `venvPreEnv`, `venvAppEnv` gained an optional trailing
  `bool inShell` argument (default `false`).**
  - `inShell == false` (default, and the behaviour that fixes the bug above):
    edit the child-process environment table **and** mirror the result into
    venv's own process environment.
  - `inShell == true`: inject the change into the **running persistent shell**
    instead (`venvStartShell()` must have been called first), translated to that
    shell's syntax — `set "NAME=…"` (`cmd.exe`), `$env:NAME = '…'` (PowerShell),
    `export NAME="…"` (POSIX). The child-process table is left untouched.
  - Each name is imported into the interpreter twice, as a 2-arg and a 3-arg
    overload (`src/underc_bridge.cpp`), mirroring the existing `venvExeCommand`
    pattern.
- `src/underc_bridge.cpp`: new shared back end `env_edit()` /
  `env_edit_in_shell()` / `proc_env_set()` / `current_shell_kind()`; the old
  `venv_uc_set_env` / `_pre_env` / `_app_env` natives now delegate to it, and
  `venv_uc_set_env_s` / `_pre_env_s` / `_app_env_s` add the `inShell` parameter.
- Docs: `README.md` and `examples/venv/main.cpp` describe the new overloads and
  the Windows `CreateProcess` / `PATH` rationale.

---

## 2026-08-31 — Configuration files are now UnderC C++ source (`.cvc`)

Breaking change. The bespoke OCF parser and the `->` operator are gone. A
configuration file is now ordinary C++ source run by the embedded UnderC
interpreter, with the suffix `.cvc` (*C venv configuration*). Its `main()`
drives the run imperatively through a new `venv*` API. There is **no backward
compatibility** with `*.ocf` / `*.ini`.

### New

- **`.cvc` configuration files.** A `.cvc` file looks like:

  ```cpp
  int main(int argc, char* argv) {
      venvRootDir("path/to/root");            // optional working root
      venvSetEnv("NAME", "value");            // set / replace a variable
      venvPreEnv("PATH", "C:\\new\\bin;");    // prepend verbatim
      venvAppEnv("PATH", ";C:\\extra\\bin");  // append verbatim

      venvSnapShotEnv();                      // was SnapShot()
      venvExeCommand("some command");         // spawn as its own child
      venvCompareSnapshotEnv();               // was CompareSnapshot()

      venvStartShell("cmd.exe");              // open one persistent shell
      venvExeCommand("cl /Bv", true);         // 2nd arg true => run in it
      venvStopShell();

      venvExecAppCommands();                  // run the -ac commands
      return 0;
  }
  ```

  The full native API: `venvRootDir`, `venvSetEnv`, `venvPreEnv`, `venvAppEnv`,
  `venvEnvGet`, `venvSnapShotEnv`, `venvCompareSnapshotEnv`, `venvExeCommand`
  (1- and 2-arg overloads), `venvStartShell`, `venvStopShell`,
  `venvExecAppCommands`, `venvAppCommandCount`, `venvAppCommandAt`,
  `venvLastExitCode`, `venvPrint`. Imported into the interpreter by name in
  `src/underc_bridge.cpp` — no wrapper prelude, no config-file parser.

- **STL enabled.** The interpreter is now started with its standard-library
  prelude (`uc_init(NULL, 1)` => `#include <classlib.h>` + `using namespace
  std;`), so a `.cvc` file may use `<string>`, `<vector>`, `<map>`,
  `<iostream>` … venv points UnderC at its STL headers by setting
  `UC_HOME` to the library prefix before `uc_init()`. An **auto-loaded** helper
  file is parsed in its own module scope and must add its own
  `using namespace std;` if it uses the STL.

- **`-uclp <prefix>` command-line flag** (*underc library prefix*). Sets where
  the UnderC engine finds its STL headers and resources. Default
  `C:\pkg\dep\underc` (Windows) / `/usr/local` (Linux). `-uclp=<prefix>` and
  `--underc-prefix` are accepted too.

- **Auto-load of the per-user venv directory.** Every `*.c` / `*.cpp` file in
  `%APPDATA%\venv` (Windows) or `$XDG_CONFIG_HOME/venv` — else
  `$HOME/.config/venv` (Linux) is `uc_load()`ed, sorted by name, before the
  `.cvc` file. Put shared helper functions there. `src/config.c` grows
  `venv_config_collect_sources()` (Win32 `FindFirstFile` / POSIX `dirent`).

- **`-ac <command>`** changed shape: it now takes **one** value (a command),
  is repeatable, and the collected list is exposed to the config through
  `venvExecAppCommands()` / `venvAppCommandCount()` / `venvAppCommandAt()`
  rather than being spliced into a config array. `venvExecAppCommands()` runs
  the list in order — in the open persistent shell when there is one, else as
  standalone children.

### Changed / removed

- **Deleted** `src/ocf_parser.{c,h}` and the whole OCF format
  (`application.*` / `environment.*` / `exec.*` / `underc.*`, `=` / `->` / `$`
  / `#` / `[]`). The argv tokenizer that lived there moved to
  `src/cmdline.{c,h}` as `venv_split_command_line()` / `venv_free_argv()`.
- **`src/config.{c,h}`** slimmed to mutable state (`root_dir`, env table,
  `venv_dir`) plus editors (`venv_config_set_env`, `venv_config_prepend_env`,
  `venv_config_append_env`, `venv_config_set_root_dir`, `venv_config_prepare`).
  No groups, no load-actions, no document.
- **`src/main.c`** reduced to: parse args, prepare the config, start UnderC,
  auto-load helpers, load the `.cvc`, run its `main()` via `uc_run()`,
  shut down. All command execution now happens inside `underc_bridge.cpp`,
  which owns the persistent shell and the snapshot store and calls straight
  into `process_spawner`.
- **`src/underc_bridge.{cpp,h}`** rewritten around the new API and lifecycle
  (`venv_underc_init` / `venv_underc_load_source` / `venv_underc_run_main` /
  `venv_underc_shutdown`).
- `src/process_spawner.h` gained `extern "C"` guards (the C++ bridge now calls
  it directly).
- Examples: every `examples/*.ocf` became `examples/*.cvc`;
  `examples/venv/main.cpp` is now an optional helper-functions sample (no
  `main()`), not a required interop shim.
- The launcher's exit code is the exit code of the last command the config
  ran (0 when it ran none). Flow control — stopping after a failure — is the
  config's job now: check `venvLastExitCode()`.

### Build

- `CMakeLists.txt`: `src/ocf_parser.c` → `src/cmdline.c`; project version
  2.0.0. `build-cmake-release.sh` now defaults `USE_UNDERC=ON` (a `.cvc` file
  is useless without the interpreter) and honours `UNDERC_PREFIX`.
- `uc_run()`'s console build prints a trailing `Program returned N` line after
  `main()` — cosmetic.

---

## 2026-08-30 — Embedded UnderC interpreter and the `->` operator

Added optional scripting through the embedded [UnderC](http://underc.org) C++
interpreter (installed at `C:\pkg\dep\underc`).

### New

- **`->` operator in OCF.** `path -> Expr()` runs an UnderC function instead of
  assigning a value (`=`). Accepted anywhere `=` is. Inside a `run[]` array the
  action runs interleaved with the commands, in file order; elsewhere it runs
  once after the configuration has been loaded.
  - `src/ocf_parser.{c,h}`: new `OCF_ACTION` node kind, `find_assignment_op()`,
    `ocf_node_is_action()` / `ocf_node_action_text()`. The right-hand side of a
    `->` is stored verbatim (no `$` / `\` / quote processing).
- **`underc` config object.** `underc.parse[]=main.cpp` names UnderC sources to
  interpret. They are loaded from a per-user *venv directory*:
  `%APPDATA%\venv` on Windows, `$XDG_CONFIG_HOME/venv` or `$HOME/.config/venv`
  on Linux. Absolute paths are used as-is.
- **`ConfigObject` exposed to UnderC.** `src/underc_bridge.{cpp,h}` starts the
  interpreter (`uc_init(NULL, 0)` — no prelude) and imports native interop
  functions: `venv_print`, `venv_env_set`, `venv_env_get`, `venv_cfg_get`,
  `venv_cfg_set`, `venv_snapshot`, `venv_snapshot_compare`. Interpreted code
  wraps these into `Config` / `Environment` classes so a script can do
  `cfg.environment->SetSomeVar()` to edit the child environment.
- **`SnapShot()` / `CompareSnapshot()`.** Capture the environment and later
  print exactly which variables were added, removed or changed. Inside a
  persistent-shell group they see the shell's **live** environment (so
  `vcvars64.bat`'s edits show up): venv sends the shell a `set` / `env`
  command bracketed by markers and parses `KEY=VALUE` out of its stream —
  `venv_shell_dump_env()` in `src/process_spawner.c`, one implementation per
  platform. Outside a shell group they read `getenv` / `environ`.
- `examples/venv/main.cpp` — reference interop source (copy it to your venv
  directory). `examples/msvc_2026_direct.ocf` and `examples/msvc_2026_cmd.ocf`
  rewritten to use `->` with `SnapShot()` / `CompareSnapshot()` around
  `vcvars64.bat`.

### Build

- `CMakeLists.txt`: project now enables `C` **and** `CXX`. New option
  `USE_UNDERC` (**ON by default**). When ON it finds the UnderC package
  (`UndercTargets.cmake` under `CMAKE_PREFIX_PATH` / `Underc_ROOT` /
  `C:/pkg/dep/underc`), links `Underc::underc`, compiles `src/underc_bridge.cpp`,
  forces the dynamic CRT (`/MD`, matching the shipped `underc.lib`), and bundles
  `ffi.dll` next to the executable. When OFF the build is pure C with no
  dependencies and a config that uses `->` / `underc.parse[]` fails with a
  "rebuild with -DUSE_UNDERC=ON" message (`VENV_USE_UNDERC` guards `main.c`).
- `build-cmake-vs2026-nmake-x64r.bat`: fixed the `%DEP_DIR%` expansion and keeps
  `-DUSE_UNDERC=On`.
- Project headers `config.h` / `util.h` gained `extern "C"` guards so the C++
  bridge can include them.

### Notes

- UnderC is GPL; a build with `USE_UNDERC=ON` links it and is therefore covered
  by the GPL. `USE_UNDERC=OFF` keeps venv MIT-only.
- `uc_load()` / `uc_eval()` report success as return value `1` (not `0`); the
  bridge treats anything else as failure and surfaces UnderC's own stderr
  diagnostic.
