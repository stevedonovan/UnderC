#ifndef VENV_UNDERC_BRIDGE_H
#define VENV_UNDERC_BRIDGE_H

/* Bridge between venv (C) and the embedded UnderC C++ interpreter.
 *
 * A .cvc configuration file is C++ source: the interpreter loads it and runs
 * its main(), and every venv* call main() makes is a native function imported
 * here that drives the real work — editing the child environment, spawning
 * commands, driving a persistent shell, diffing environment snapshots.
 *
 * Lifecycle:
 *     venv_underc_resolve_prefix(requested, &uclp, &src, ...); // find UC_HOME
 *     venv_underc_init(&cfg, uclp, appc, appv, ...);   // start the interpreter
 *     venv_underc_load_source(path, ...);              // auto-load + the .cvc
 *     venv_underc_run_main(&exit_code, ...);           // run the config's main()
 *     venv_underc_shutdown();                          // once, before exit
 */

#include "config.h"

#include <stddef.h>

/* Last-resort UnderC library prefix, used when nothing else is found. */
#if defined(PLATFORM_WINDOWS)
#  define VENV_DEFAULT_UCLP "C:\\pkg\\dep\\underc"
#else
#  define VENV_DEFAULT_UCLP "/usr/local"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Work out which UnderC library prefix to run with, i.e. what to put in
 * UC_HOME. A prefix is usable only when <prefix>/include/underc/uclstl exists;
 * UnderC refuses to start without it and then crashes inside uc_init() on the
 * prelude's first #include, so this has to be settled before the interpreter
 * is started.
 *
 * `requested` is the -uclp value, or NULL/"" to auto-detect. Auto-detection
 * tries, in order: $UC_HOME, $DEP_DIR/underc, the directory holding venv and
 * its parent (an installed bin/ layout), and finally VENV_DEFAULT_UCLP.
 *
 * On success 0 is returned, `*out_prefix` receives a freshly allocated path
 * (free it) and `*out_source` a static label naming where it came from. On
 * failure -1 is returned and `err` explains which candidates were tried.
 * `out_source` may be NULL. */
int venv_underc_resolve_prefix(const char *requested, char **out_prefix,
                               const char **out_source, char *err,
                               size_t errlen);

/* Start the interpreter with its standard-library prelude (so a .cvc file may
 * use <string>, <vector>, <map>, …), pointing it at the UnderC library prefix
 * `uclp` for the STL headers, and import the venv* native functions.
 *
 * `cfg` is kept by reference and mutated by the venv* functions, so it must
 * outlive every venv_underc_* call. `app_commands` is the `-ac` list, exposed
 * to the config through venvExecAppCommands() and venvAppCommandAt().
 *
 * Returns 0, or -1 with a message in `err`. */
int venv_underc_init(venv_config *cfg, const char *uclp,
                     char *const *app_commands, size_t app_command_count,
                     char *err, size_t errlen);

/* uc_load() one source file (an auto-load helper, or the .cvc config itself).
 * Returns 0, or -1 with the interpreter's error text in `err`. */
int venv_underc_load_source(const char *path, char *err, size_t errlen);

/* Run the loaded program's main(). `*exit_code` receives the exit status of
 * the last command the config executed (0 when it executed none). Returns 0,
 * or -1 with a message in `err` when main() could not be run. */
int venv_underc_run_main(int *exit_code, char *err, size_t errlen);

/* Stop the interpreter and release everything. Safe to call when init failed. */
void venv_underc_shutdown(void);

#ifdef __cplusplus
}
#endif

#endif /* VENV_UNDERC_BRIDGE_H */
