# venv

A cross-platform utility that launches child processes inside a *virtual
environment* — a configured working root, a curated environment block, and a
sequence of commands, optionally driven through one persistent shell.

The launcher core is **portable C** with no third-party dependencies beyond the
C standard library and the platform's native process APIs. On top of it,
venv **embeds the [UnderC](http://underc.org) C++ interpreter**: a
configuration file is not a bespoke format any more, it is **C++ source** that
the interpreter runs. Its `main()` drives the whole run by calling a small
`venv*` API.

Configuration files use the suffix **`.cvc`** (*C venv configuration*).

| Feature | Linux | Windows |
|---|---|---|
| Filesystem root isolation | `chroot(2)` — child sees the root as `/` (only when `venvRootDir()` is called) | Working-directory pivot; the child's cwd is the root |
| Environment isolation | `environ` replaced wholesale in the child | Custom environment block via `CreateProcess` |
| Process containment | `fork` / `exec` | Windows **Job Object** with `KILL_ON_JOB_CLOSE` |
| Standalone commands | `fork` / `exec`; the child inherits venv's stdio, so its output lands in the same terminal | `CreateProcess` with venv's std handles handed to the child, so its output lands in the same terminal — no second console window |
| Persistent shell | any shell binary (`/bin/bash`, …) driven through its stdin; output goes straight to the terminal | any shell binary (`cmd.exe`, `powershell.exe`, …) driven through its stdin; output is piped through venv, which filters the status marker out |
| Capturing output | `/bin/sh -c`, stdout on a pipe | `%COMSPEC% /s /c`, stdout on a pipe |
| Environment diffing | `env` dumped, parsed and diffed inside the config | `SET` dumped, parsed and diffed inside the config |
| Scripting | the config file is C++ run by the embedded interpreter, with the STL available | same |

---

## What a configuration file looks like

```cpp
// examples/windows_test_env.cvc
int main(int argc, char* argv) {
    venvRootDir("L:\\bin");                       // optional working root

    venvPreEnv("PATH", "L:\\pkg\\bin\\cmake\\bin;");  // prepend, verbatim

    venvStartShell("cmd.exe");                    // one persistent shell
    venvExeCommand("call \"...\\vcvars64.bat\"", true);   // run in the shell
    venvExeCommand("cl /help", true);
    venvExeCommand("cmake --help", true);
    venvStopShell();
    return 0;
}
```

```cpp
// a shell-less config
int main(int argc, char* argv) {
    venvRootDir("/srv/sandbox");
    venvSetEnv("PATH", "/usr/local/bin:/usr/bin:/bin");
    venvSetEnv("MY_APP_ENV", "production");

    venvSnapShotEnv();
    venvExeCommand("/usr/bin/myapp --config /etc/myapp.toml");  // own child
    venvCompareSnapshotEnv();
    return 0;
}
```

The file is real C++: it may use `if`, loops, functions, and the STL
(`<string>`, `<vector>`, `<map>`, …). See [`examples/`](examples/).

---

## The `venv*` API

Every function below is a native function that venv imports into the
interpreter. A `.cvc` file calls them directly — nothing to `#include`, nothing
to declare.

| Function | Effect |
|---|---|
| `venvRootDir(const char* path)` | Set the virtual root. `path` must be an existing directory. On Linux this enables `chroot` (needs root); on Windows it sets the child's working directory. Optional — when never called, venv's own working directory is used and Linux does **not** `chroot`. |
| `venvSetEnv(const char* name, const char* value [, bool inShell])` | Set or replace an environment variable. |
| `venvPreEnv(const char* name, const char* fragment [, bool inShell])` | Prepend `fragment` to the current value of `name` (**verbatim** — no separator is inserted, so include the `;` / `:` yourself). Creates the variable when absent. |
| `venvAppEnv(const char* name, const char* fragment [, bool inShell])` | Append `fragment` to the current value of `name`, same rules. |
| `venvEnvGet(const char* name)` → `const char*` | Read a child-process variable, falling back to venv's own environment. |

The three env editors take an optional trailing `bool inShell` (default `false`):

* **`inShell == false`** (the default) — the edit is applied to the child-process
  environment table **and mirrored into venv's own process
  environment**. That second part matters: a shell-less `venvExeCommand()` child
  inherits venv's environment, and on **Windows** `CreateProcess()`
  resolves the executable image through the **calling process's** `PATH` — never
  the environment block handed to the child — so without the mirror a
  `venvPreEnv("PATH", "...\\cmake\\bin;")` would not let the next
  `venvExeCommand("cmake ...")` find `cmake.exe`.
* **`inShell == true`** — the edit is injected into the **running persistent
  shell** instead (so `venvStartShell()` must have been called first). It is
  translated to that shell's own syntax — `set "NAME=..."` for `cmd.exe`,
  `$env:NAME = '...'` for PowerShell, `export NAME="..."` for a POSIX shell —
  and every following `venvExeCommand(cmd, true)` sees it. The child-process
  table is left untouched.
| `venvExeCommand(const char* cmd)` | Run `cmd` as its **own child process** (tokenised into an argv). |
| `venvExeCommand(const char* cmd, bool inShell)` | With `inShell == true`, send `cmd` to the persistent shell opened by `venvStartShell()`; with `false` it behaves like the one-argument form. |
| `venvExeCommandString(const char* cmd)` → `const char*` | Run `cmd` through the **host command interpreter** in the environment built so far and **return what it wrote to stdout**. Use it to read a value back out of the environment rather than only act on it. |
| `venvStartShell(const char* shell)` | Start one persistent instance of `shell` (e.g. `cmd.exe`, `/bin/bash`) with the configured root and environment. Only one shell at a time. |
| `venvStopShell()` | Close stdin, wait for the shell to exit, release it. venv also closes a shell the config forgot. |
| `venvSnapShotEnv()` | Record the current environment under the id `default`. Inside a persistent-shell session this captures the **shell's live** environment. |
| `venvCompareSnapshotEnv()` | Capture again and print exactly which variables were added (`+`), removed (`-`) or changed (`~`) since `venvSnapShotEnv()`. |
| `venvExecAppCommands()` | Run every `-ac` command from the command line, in order — in the open shell when there is one, else as standalone children. |
| `venvAppCommandCount()` → `int` | Number of `-ac` commands. |
| `venvAppCommandAt(int i)` → `const char*` | The i-th `-ac` command (empty string when out of range). |
| `venvLastExitCode()` → `int` | Exit code of the last command run. Use it for flow control. |
| `venvPrint(const char* text)` | Print a line to venv's stdout. |

`venvExeCommand` prints a progress line before each command and its exit code
after. A standalone (shell-less) command runs on venv's **own stdin,
stdout and stderr**, so its output appears inline in the terminal that started
venv, between those two lines — on Windows too, where the child is
given the parent's std handles rather than a console window of its own:

```
venv: [1] running: cmake --help
Usage

  cmake [options] <path-to-source>
  …
venv: [1] child exited with code 0
```

### Reading a command's output back: `venvExeCommandString()`

`venvExeCommand()` lets a command's output go to the terminal;
`venvExeCommandString()` captures it and hands it to the config as a string:

```cpp
string vars    = venvExeCommandString("SET");          // Windows
string vars    = venvExeCommandString("env");          // Linux
string version = venvExeCommandString("cl 2>&1");
```

Unlike `venvExeCommand()`, this call **always goes through a shell** — `%COMSPEC%`
(usually `cmd.exe`) with `/s /c` on Windows, `/bin/sh -c` on Linux — because
what a config wants to read back is normally a shell built-in or the effect of a
script (`SET`, `env`, `call vcvars64.bat & SET`), none of which is an executable
image. Shell syntax (`&`, `|`, `>`, quoting) is therefore available inside `cmd`.

The child runs with the environment the config has built so far and in the
configured root directory. Only **stdout** is captured; the child's **stderr
still goes to the terminal**, so a failing command explains itself instead of
poisoning the returned string (redirect with `2>&1` when you want it included).
`venvLastExitCode()` reports the shell's exit status, and the progress lines name
how much was captured:

```
venv: [1] capturing: SET
venv: [1] command exited with code 0 (12226 bytes captured)
```

A command that fails does **not** automatically stop the ones that follow —
that is the config's decision now:

```cpp
venvExeCommand("make -j8");
if (venvLastExitCode() != 0) return venvLastExitCode();
venvExeCommand("make install");
```

The launcher's own exit code is the exit code of the last command the config
ran (0 when it ran none).

### Turning that output into an environment: the diff helpers

The dump is only text; three helpers in
[`examples/venv/main.cpp`](examples/venv/main.cpp) turn it into data. They are
ordinary interpreted C++ rather than natives, so they are available once that
file is auto-loaded from the venv directory, or named with `-ucll`.

| Helper | Effect |
|---|---|
| `parseEnvironment(const string& text)` → `map<string,vector<string> >` | Parse a `SET` (Windows) or `env` (Linux) dump into *name → value, split on the host's list separator*. |
| `findAddedEntriesEnvironment(map& before, map& after)` → `map<string,vector<string> >` | Diff two of those and return only what `after` gained: a variable `before` did not have at all, and for one both have, the fragments `before` lacked — in `after`'s order. Unchanged variables are left out. |
| `venvPreEnv(map<string,vector<string> >& entries)` | Prepend every entry to the variable it belongs to, joined with the host's list separator. |

Together they let a script that works by mutating its shell — `vcvars64.bat` is
the archetype — be run **once, in a throw-away shell**, with only its effect
carried into the environment every later command sees:

```cpp
string before = venvExeCommandString("SET");
string after  = venvExeCommandString("call vcvars64.bat & SET");

map<string,vector<string> > envBefore = parseEnvironment(before);
map<string,vector<string> > envAfter  = parseEnvironment(after);
map<string,vector<string> > added     = findAddedEntriesEnvironment(envBefore,
                                                                    envAfter);
venvPreEnv(added);
venvExeCommand("cl");            // no shell was kept open
```

Details worth knowing:

* The **list separator** is `;` or `:`, decided at run time from `COMSPEC` /
  `WINDIR` — the interpreter has no `_WIN32`. A value with no separator in it
  becomes a single-element vector, so scalars and lists are handled alike.
* Lines **without a `=`** are skipped, which is what keeps a banner printed
  ahead of the dump (vcvars64.bat prints one) out of the result. So are
  cmd.exe's `=C:=…` and `=ExitCode=…` pseudo variables, whose name is empty.
* `venvPreEnv(added)` **prepends** to a variable that already has a value,
  separator included, and **sets** one that does not exist yet — so a freshly
  introduced scalar such as `VSCMD_VER` does not end up with a stray separator
  glued to it.
* `findAddedEntriesEnvironment()` reports **additions only**. A variable the
  second dump dropped, or whose entries it only removed, is not in the result.

---

## Prerequisites

| Dependency | Version | Notes |
|---|---|---|
| CMake | ≥ 3.16 | |
| C compiler | C11 | GCC, Clang, MSVC 2015+ |
| C++ compiler | C++14 | one file — `underc_bridge.cpp` |
| UnderC | 1.5.0+ | 1.3.9 builds and runs, but the environment-diff helpers need the array-construction and `map` copy fixes that landed in 1.5.0 — see [What the embedded engine needs](#what-the-embedded-engine-needs). With the **STL headers installed** (`<prefix>/include/underc/uclstl`) and a CMake package under `<prefix>/lib/cmake/Underc` |

The embedded UnderC interpreter is **mandatory** — a `.cvc` file is C++ run by
it — so there is no build option to turn it off.

`venv/CMakeLists.txt` is a plain package consumer, the same shape as
`cli/CMakeLists.txt`: it locates the interpreter only through
`find_package(Underc REQUIRED MODULE)`, searching the `lib/cmake/Underc`
subdirectory of every entry on `CMAKE_PREFIX_PATH` and of `CMAKE_INSTALL_PREFIX`.
The interpreter is either on the prefix path or it is not. venv links
`Underc::underc` and forces the **dynamic CRT** (`/MD`, matching the shipped
`underc.lib`).

The installed `UndercTargets.cmake` names the interpreter's own dependencies —
libffi in particular — by file path, so venv needs no `pkg-config` of its own.
An interpreter installed by a release before 1.5.4 recorded libffi on Unix as
the imported target `PkgConfig::LIBFFI`, which does not exist in this project;
the link then fails with `cannot find -lPkgConfig::LIBFFI` and reinstalling the
interpreter clears it.

`ffi.dll` is not bundled — like `ucc`, `venv.exe` needs it on `PATH` at run
time on Windows.

UnderC is GPL software, so the `venv` binary links GPL code and is covered by
the GPL.

---

## Building

**Windows (MSVC)** — from a *Developer Command Prompt* (or after `call`ing
`vcvars64.bat`), with CMake on `PATH`, run from the UnderC repository root:

```bat
cmake -G "NMake Makefiles" -B out-venv-release -S venv ^
      -DCMAKE_BUILD_TYPE=Release ^
      -DCMAKE_PREFIX_PATH=%DEP_DIR%\underc-vc-x64r ^
      -DCMAKE_INSTALL_PREFIX=%DEP_DIR%\underc-vc-x64r
cmake --build out-venv-release
cmake --build out-venv-release --target install
```

The simplest path is the UnderC repository root's `build-cmake-install.ps1`,
run from an already-set-up developer PowerShell: it builds and installs the
interpreter library, `ucc`, and `venv` in sequence under one prefix.

**Linux** — from the repository root:

```bash
cmake -B build-venv -S venv -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_PREFIX_PATH=/usr/local
cmake --build build-venv
```

The resulting binary is `venv` / `venv.exe`. On Windows `ffi.dll` must be on
`PATH` at run time.

---

## Usage

```
venv <config.cvc> [-uclp <prefix>] [-ucll <file>]... [-ac <command>]...
venv --config <config.cvc> [options]...
```

| Option | Description |
|---|---|
| `-h`, `--help` | Show the help message and exit |
| `-c`, `--config <path>` | Path to the `.cvc` file (also `--config=<path>`; a bare positional path works too) |
| `-uclp <prefix>` | **UnderC library prefix** — the directory holding `include/underc/uclstl` (the interpreter's STL headers and engine resources). Optional: when omitted it is [auto-detected](#finding-the-underc-library-prefix). `-uclp=<prefix>` and `--underc-prefix` also accepted. |
| `-ucll <file>` | **Load an extra C / C++ source file** into the interpreter before the configuration is processed — after the auto-loaded venv directory, before the `.cvc`. Repeatable; the files are loaded in the order given. `-ucll=<file>` and `--underc-load` also accepted. |
| `-ac <command>` | Append one command to the list the config reads back through `venvExecAppCommands()` / `venvAppCommand*()`. Repeatable; order preserved. |

### Where configuration and `-ucll` files are looked up

A `<config.cvc>` argument, and every `-ucll <file>`, is resolved the same way:

* a path that **says where it lives** is used verbatim — an absolute path
  (`C:\tools\msvc.cvc`, `/etc/venv/msvc.cvc`) and one that is explicitly
  relative to the current directory (`.\msvc.cvc`, `./msvc.cvc`, `..\msvc.cvc`);
* anything else is a **bare name** and is looked up in the
  [per-user venv directory](#the-auto-loaded-venv-directory) — `%APPDATA%\venv`
  on Windows, `$XDG_CONFIG_HOME/venv` (else `$HOME/.config/venv`) on Linux — the
  same directory whose `.c` / `.cpp` files are auto-loaded.

So a configuration kept with the rest of your environment files runs from
anywhere, with no path:

```bat
cd L:\wrk\cpp_boost_asio\fsync
venv.exe msvc_env.cvc -ac ".\build-cmake-venv-ssl-release.bat"
```

and the banner shows what the name resolved to:

```
  config   : C:\Users\you\AppData\Roaming\venv\msvc_env.cvc
```

When the bare name is **not** in the venv directory it is kept as written, so a
file in the current directory still runs and an error message names what you
typed. Prefix with `.\` (or `./`) to skip the venv directory entirely.

### Loading extra sources with `-ucll`

`-ucll <file>` hands one more C / C++ source file to the interpreter **before
the configuration is processed**, so the `.cvc` can call what it defines:

```bat
venv.exe .\build.cvc -ucll .\msvc_helpers.cpp -ucll toolchains.cpp
```

The load order is: every `*.c` / `*.cpp` in the venv directory (sorted by name),
then the `-ucll` files in the order given, then the `.cvc` itself. The option is
repeatable, each file is resolved by the rule above (`toolchains.cpp` above comes
from the venv directory), and — like an auto-loaded file — a `-ucll` file is
parsed in its own module scope, so it needs its own `using namespace std;` and
must not define `main()`.

Use it for helpers that are specific to one project or one machine, where the
venv directory is too global and pasting them into the `.cvc` is too repetitive.

### Finding the UnderC library prefix

venv sets `UC_HOME` to the prefix before starting the interpreter, so
`uc_init()` can load the STL prelude from `<prefix>/include/underc/uclstl`.

A prefix counts as usable only when that `include/underc/uclstl` directory
actually exists. It is **resolved and validated before the interpreter is
started**, and the one in use is printed in the banner together with where it
came from:

```
  uclp     : L:/pkg/dep/underc (above venv)
```

Without `-uclp` the following are tried in order; the first usable one wins:

| # | Candidate | Label in the banner |
|---|---|---|
| 1 | `$UC_HOME` | `UC_HOME` |
| 2 | `$DEP_DIR/underc` | `$DEP_DIR/underc` |
| 3 | the directory holding `venv` | `next to venv` |
| 4 | its parent directory (an installed `<prefix>/bin/` layout) | `above venv` |
| 5 | `C:\pkg\dep\underc` (Windows) / `/usr/local` (Linux) | `built-in default` |

If none of them holds an UnderC install, venv stops with the full list
of what it tried instead of starting the interpreter.

An explicit `-uclp` is an instruction rather than a hint: when it does not point
at an UnderC install the run stops, naming the directory that is missing and —
if auto-detection would have found one — a prefix that does work:

```
venv: -uclp 'L:\pkg\dep\nope' is not an UnderC library prefix: no such
directory 'L:\pkg\dep\nope\include\underc\uclstl'; a usable prefix was found at
'L:/pkg/dep/underc' (above venv)
```

This check is not cosmetic: UnderC gives up when its include path is missing but
`uc_init()` carries on regardless and then crashes on the prelude's first
`#include`, which would kill venv silently right after the banner —
before the `.cvc` is loaded and before a single command runs.

**Linux note:** `chroot` is used **only when the config calls `venvRootDir()`**,
and it needs root:

```bash
sudo ./venv examples/linux_example.cvc     # config calls venvRootDir()
./venv       examples/linux_test_env.cvc   # no venvRootDir() → no sudo
```

---

## The configuration file in detail

### It is C++ run by UnderC

The interpreter is started **with** its standard-library prelude
(`uc_init(NULL, 1)` — `#include <classlib.h>` plus `using namespace std;`), so
a `.cvc` file gets `string`, `vector`, `list`, `map`, `algorithm` and
`iostream` for free. It does **not** get arbitrary system headers — it is an
interpreter, not a compiler — so keep to the core language, the STL, and the
`venv*` API.

The entry point is `int main(int argc, char* argv)` (the second parameter is
currently unused). venv runs it with `uc_run()`; on the console build
UnderC prints a cosmetic `Program returned N` line afterwards.


#### What the embedded engine needs

The interpreter is not a compiler, and its STL is its own implementation. Two
container defects used to rule the diff helpers above out entirely; both are
fixed in **UnderC 1.5.0 (2026-09-01)**, which venv now expects:

* `new T[n]` ran the constructor for element 0 only, so every element after the
  first was raw memory and a `vector<string>` corrupted the heap as soon as it
  held more than one string.
* `std::map` declared its copy constructor and `operator=` private and left
  both undefined (the C++98 noncopyable idiom), so a map could not be returned
  by value: `map<string,string> m = f();` failed with
  `map<…>::map(const map<…>&) is not defined yet`.

`underc_fix_vector.txt`, in the UnderC source tree, is the analysis that led
to that repair. Against an older UnderC the helpers in
[`examples/venv/main.cpp`](examples/venv/main.cpp) fail to load or crash the
process; nothing else in venv is affected.

One parser limit remains: nested template arguments need a space —
`map<string, vector<string> >`. The `>>` spelling is a syntax error.

### Environment

The environment table is **seeded with venv's own environment**, and the
config edits that snapshot:

```cpp
venvSetEnv("MY_APP_ENV", "production");        // add or replace
venvPreEnv("PATH", "/opt/mytool/bin:");        // extend the inherited PATH
venvSetEnv("SECRET", "");                      // keep it, but blank it out
```

On **Windows** names are matched case-insensitively, so writing `PATH` edits the
inherited `Path` rather than adding a second entry. On **Linux** names are
case-sensitive.

The resulting set is the environment handed to every child — on Linux it
replaces `environ` wholesale, on Windows it is the `CreateProcess` environment
block.

Each of these edits (when made with the default `inShell == false`) is also
mirrored into **venv's own process environment**. This is what makes a
`PATH` edit take effect for a shell-less command: on Windows `CreateProcess()`
locates the executable image through the calling process's `PATH`, not through
the environment block it passes to the child, so the mirror is required for
`venvExeCommand("cmake ...")` to find a `cmake` that a `venvPreEnv("PATH", …)`
just added. Pass `inShell == true` to instead push the edit into an already
open persistent shell (see [The `venv*` API](#the-venv-api)).

### The auto-loaded venv directory

Before your `.cvc` file, venv `uc_load()`s **every `*.c` / `*.cpp` file**
in the per-user venv directory, sorted by name:

| Platform | venv directory |
|---|---|
| Windows | `%APPDATA%\venv` |
| Linux | `$XDG_CONFIG_HOME/venv`, else `$HOME/.config/venv` |

Put shared helper functions there so your `.cvc` files stay short. An
auto-loaded file is parsed in its **own module scope**, so if it uses the STL it
must add its own `using namespace std;` at the top (a `.cvc` file loaded last
does not need to). Do **not** define `main()` in an auto-loaded file — that
belongs in the `.cvc`. See [`examples/venv/main.cpp`](examples/venv/main.cpp).

The same directory is where a **bare configuration name** is looked up
(`venv msvc_env.cvc`), and where a bare `-ucll` name comes from — see
[Where configuration and `-ucll` files are looked up](#where-configuration-and--ucll-files-are-looked-up).
Files loaded there on demand do not need a `.c` / `.cpp` suffix, only the
auto-loaded ones do.

---

## The persistent shell

Without a shell, every `venvExeCommand()` is its own child process, and a child
cannot change its parent's environment — so `vcvars64.bat`, `source activate`,
`nvm use`, `module load` and everything else that works by mutating the calling
shell has no effect on the next command.

`venvStartShell()` fixes that. venv:

1. **Starts one persistent shell** with the configured root and environment,
   stdin on a pipe.
2. **Sends every `venvExeCommand(cmd, true)` line to it through stdin**, in
   order, as shell input.
3. **Waits for each command's exit status before sending the next**, so the
   sequence stays strictly sequential.

Because all commands share one shell process, environment changes, the working
directory, shell functions and aliases persist from one to the next.

```cpp
int main(int argc, char* argv) {
    venvStartShell("/bin/bash");
    venvExeCommand("source ./examples/env_set_test.sh", true);  // exports VENV_TEST
    venvExeCommand("echo VENV_TEST=$VENV_TEST", true);          // prints somevar
    venvStopShell();
    return 0;
}
```

### How the status comes back

* **Linux:** the shell is started with an extra file descriptor 3, and each
  command is followed by `echo "$?" >&3`. stdout and stderr stay connected to
  the terminal, so command output is not intercepted.
* **Windows:** `cmd.exe` has no spare descriptor, so the status travels through
  stdout as a marker line (`@echo __VENV_SPAWNER_STATUS__%ERRORLEVEL%`) that
  venv filters out again. The shell is started as `cmd.exe /Q` and put
  into `echo off` so it does not echo its input (which would duplicate every
  command — and the probe — in the output). The `cmd.exe` greeting is drained
  while the shell opens, so it appears before the first command instead of in
  the middle of its output.

### Notes

* A command still has to change *this* shell to be felt by the next one —
  `source script.sh`, not `./script.sh`.
* Shell syntax (pipes, `&&`, redirection, `$VAR` expansion) is available and is
  evaluated by that shell. `$VAR` in a command is expanded by the shell at run
  time.
* Keep a compound command on one line (`if [ -f x ]; then y; fi`) — a line that
  leaves the shell waiting for more input swallows the status probe and hangs.
* On Windows `/Q` is only appended when the shell is `cmd.exe` / `cmd`.
* A command that terminates the shell (`exit`) ends the session; the shell's
  exit status becomes that command's status.

---

## Environment snapshots

`venvSnapShotEnv()` records the environment; `venvCompareSnapshotEnv()` captures
it again and prints the delta:

```cpp
int main(int argc, char* argv) {
    venvStartShell("cmd.exe");
    venvSnapShotEnv();
    venvExeCommand("call \"...\\vcvars64.bat\"", true);
    venvCompareSnapshotEnv();
    venvStopShell();
    return 0;
}
```

```
venv: snapshot 'default' captured (60 variables)
venv: [1] shell: call "...\vcvars64.bat"
[vcvarsall.bat] Environment initialized for: 'x64'
venv: [1] command exited with code 0
venv: snapshot 'default' vs current environment:
  + INCLUDE=C:\Program Files\...\include;...
  + LIB=C:\Program Files\...\lib\x64;...
  ~ Path
      old: ...
      new: ...;C:\Program Files\...\bin\HostX64\x64;...
venv: 44 environment change(s)
```

Inside a persistent-shell session the snapshot reads the **shell's live**
environment: venv sends the shell a `set` (`cmd.exe`) / `env` (POSIX)
command bracketed by markers — the same out-of-band trick used for the exit
status — and parses the `KEY=VALUE` lines back out. Outside a shell session the
snapshot reflects the environment table the config has built so far.

---

## Appending commands from the command line

`-ac` adds one command to a list the config decides what to do with:

```
venv examples\windows_test_env_arg.cvc ^
    -ac ".\build-cmake-venv-ssl-release.bat"
```

```cpp
int main(int argc, char* argv) {
    venvStartShell("cmd.exe");
    venvExeCommand("call \"...\\vcvars64.bat\"", true);
    venvExecAppCommands();      // runs every -ac command, here inside the shell
    venvStopShell();
    return 0;
}
```

`-ac` is repeatable; the commands run in the order given. A config can also
iterate them by hand:

```cpp
for (int i = 0; i < venvAppCommandCount(); ++i)
    venvExeCommand(venvAppCommandAt(i), true);
```

**The value is taken verbatim** — only your terminal's own quoting stands
between the text and venv. `venvExecAppCommands()` runs the commands in
the open persistent shell when there is one, otherwise as standalone children
(tokenised like any `venvExeCommand()`).

---

## Worked example: an MSVC build environment

`vcvars64.bat` works purely by mutating the shell that calls it, so it needs a
persistent shell. A reusable environment file is just the `PATH` edit and the
`call`:

```cpp
// %APPDATA%\venv\... or anywhere: msvc_env.cvc
int main(int argc, char* argv) {
    venvPreEnv("PATH", "L:\\pkg\\bin\\cmake-4.3.2-windows-x86_64\\bin;");
    venvStartShell("cmd.exe");
    venvExeCommand("call \"C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat\"", true);
    venvExecAppCommands();
    venvStopShell();
    return 0;
}
```

With no `venvRootDir()` the shell starts in venv's own working
directory, so the same file drives a build in whatever project you stand in —
the build command comes from `-ac`:

```bat
cd L:\wrk\cpp_boost_asio\fsync
venv.exe msvc_env.cvc -ac ".\build-cmake-venv-ssl-release.bat"
```

(`msvc_env.cvc` needs no path: a bare name is looked up in `%APPDATA%\venv`.)

### The shell-less variant

The shell above exists only because `vcvars64.bat` has to mutate *something*.
With `venvExeCommandString()` that state can be read back out instead: dump the
environment, run the batch file and dump it again, diff the two, and prepend
just what it added — after which the MSVC toolchain is in the child environment
and no shell is kept open.

[`examples/win_msvc2026_auto.cvc`](examples/win_msvc2026_auto.cvc) is that
configuration. It needs the helpers from
[`examples/venv/main.cpp`](examples/venv/main.cpp), so either copy that file
into `%APPDATA%\venv\` where it is auto-loaded, or name it explicitly:

```bat
venv.exe -ucll .\examples\venv\main.cpp .\examples\win_msvc2026_auto.cvc
```

From an environment with no MSVC variables in it and `PATH` cut down to
`C:\Windows\System32`, the diff picks up nine variables — `PATH`, `INCLUDE`,
`LIB`, `LIBPATH`, `Platform`, `VCToolsInstallDir`, `VSCMD_VER` and two
`__VSCMD_PREINIT_*` — and the `venvExeCommand("cl")` that follows finds the
compiler.

---

## Architecture

```
main.c            – argument parsing; resolve the UnderC prefix; prepare
                    config; start UnderC; auto-load helpers; load the -ucll
                    files; load the .cvc; run its main(); shut down
cmdline.c/.h      – argv tokenizer (venv_split_command_line / venv_free_argv)
config.c/.h       – mutable venv state: root_dir, environment table, venv_dir;
                    editors; venv source-file discovery (FindFirstFile/dirent);
                    bare-name lookup (venv_config_resolve_source_path)
util.c/.h         – allocation wrappers, growable buffer, error formatting
platform.c/.h     – thin dispatcher to process_spawner
process_spawner.c/.h
  ├── #if PLATFORM_LINUX    – fork/chdir/(chroot)/execvp; pipe-driven shell
  ├── #if PLATFORM_WINDOWS  – CreateProcess (inheriting our std handles)
  │                           + Job Object; pipe-driven shell
  ├── venv_process_spawner_capture
  │                         – run one command through the host command
  │                           interpreter and capture its stdout
  └── venv_shell_dump_env   – capture the shell's live environment out of band
underc_bridge.cpp/.h – the only C++ file: resolves and validates the UnderC
                       library prefix, starts UnderC with its STL prelude,
                       imports the venv* natives, and owns command execution,
                       the persistent shell and the snapshot store
examples/venv/main.cpp – sample auto-loaded helper source (no main()):
                       PATH helpers, plus parseEnvironment /
                       findAddedEntriesEnvironment / venvPreEnv(map)
```

The platform branch is selected at compile time (`PLATFORM_LINUX` /
`PLATFORM_WINDOWS`).

### Conventions

The launcher is C (the single `underc_bridge.cpp` aside):

* Functions that can fail return `0` / `-1` and write a message into a
  caller-supplied `char *err, size_t errlen`.
* Every `venv_config` is paired with `venv_config_free()`; every token array
  with `venv_free_argv()`.
* Allocation failure is fatal by design (`venv_xmalloc()` and friends print and
  exit).
* Strings are built with the growable `venv_buf`, so no fixed-size limits apply
  to paths, command lines or environment blocks.

---

## Migrating from the OCF configuration

Older versions used `*.ocf` files parsed by a bespoke parser, with an `->`
operator for interpreted actions. That is **gone** — there is no backward
compatibility. The mapping is mechanical:

| OCF (old) | `.cvc` (new) |
|---|---|
| `application.root_dir=/srv/sandbox` | `venvRootDir("/srv/sandbox");` |
| `environment.PATH=/usr/bin` | `venvSetEnv("PATH", "/usr/bin");` |
| `environment.PATH=$environment.PATH:/x` | `venvAppEnv("PATH", ":/x");` |
| `exec.<group>.run[]=<command>` | `venvExeCommand("<command>");` |
| `exec.<group>.shell=cmd.exe` | `venvStartShell("cmd.exe");` |
| `exec.<group>.run[]=<command>` (with a shell) | `venvExeCommand("<command>", true);` |
| `run[]->SnapShot()` | `venvSnapShotEnv();` |
| `run[]->CompareSnapshot()` | `venvCompareSnapshotEnv();` |
| `underc.parse[]=main.cpp` | drop a `*.cpp` file in `%APPDATA%\venv` — it is auto-loaded |
| `-ac <array> <command>` | `-ac <command>` + `venvExecAppCommands()` |
| `$` substitution, `#` comments, `[]` arrays, `\` escapes | plain C++: variables, `//` comments, real string handling |

The converted [`examples/`](examples/) are the best reference.

---

## Security considerations

* **Linux:** `chroot` alone is not a full sandbox (a process with
  `CAP_SYS_CHROOT` can escape). Combine with namespaces or a container runtime
  for production.
* **Without `venvRootDir()` there is no filesystem isolation on Linux** — the
  child reaches the whole host filesystem. That is the point of the mode (no
  `sudo`), but do not mistake it for containment.
* **The environment starts from the host environment**, so secrets in
  venv's own environment reach the child unless the config overwrites
  them.
* **A `.cvc` file is executed code.** It is C++ run by an interpreter with the
  `venv*` API and can spawn arbitrary processes and open a real shell. Treat
  config files — and the auto-loaded venv directory — as trusted input.
* **`-ac` extends that trust to the command line.** An appended value is run
  exactly like a `venvExeCommand()` line, so a script that forwards untrusted
  input into `-ac` hands that input to the shell.
* **Windows:** true filesystem isolation needs Windows Sandbox or Hyper-V
  containers. This implementation isolates the *working directory* and
  *environment* only.

---

## License

MIT — see [LICENSE](LICENSE).

The `venv` binary links the embedded UnderC interpreter, which is GPL software,
so the build as a whole is governed by the GPL. UnderC is mandatory, so this
always applies.
