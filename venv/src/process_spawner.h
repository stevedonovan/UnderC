#ifndef VENV_PROCESS_SPAWNER_H
#define VENV_PROCESS_SPAWNER_H

#include "config.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* All platform-specific logic for creating a sandboxed child process with a
 * virtual root lives behind these functions. */

/* Launches `command` inside the environment described by `cfg`, as its own
 * child process. On success 0 is returned and `*exit_code` receives the
 * child's exit code; on failure -1 is returned and a message is written to
 * `err`. */
int venv_process_spawner_run(const venv_config *cfg,
                             const venv_command *command, int *exit_code,
                             char *err, size_t errlen);

/* Run `command_line` through the host command interpreter (`%COMSPEC%` /
 * `cmd.exe /s /c` on Windows, `/bin/sh -c` on Linux) inside the environment
 * described by `cfg`, and capture everything it writes to stdout.
 *
 * A shell is used rather than a direct exec because the point of this call is
 * to read back what a shell script leaves behind — `SET`, `env`, a `.bat` that
 * is `call`ed and then queried — none of which are executable images. The
 * child's stderr is left pointing at venv's own, so diagnostics still
 * reach the terminal instead of ending up in the captured text.
 *
 * On success 0 is returned, `*out_text` receives the freshly allocated,
 * NUL-terminated output (free it) and `*exit_code` the shell's exit status.
 * On failure -1 is returned with a message in `err`. `out_len` may be NULL. */
int venv_process_spawner_capture(const venv_config *cfg,
                                 const char *command_line, char **out_text,
                                 size_t *out_len, int *exit_code, char *err,
                                 size_t errlen);

/* ── Persistent shell sessions ───────────────────────────────────────────────
 *
 * A session is one long-lived shell process that receives commands through its
 * stdin (venvStartShell() opens it, venvExeCommand(cmd, true) feeds it). Because
 * all commands run inside the same shell, environment changes, the working
 * directory and shell functions survive from one command to the next.
 *
 * Usage:
 *     venv_shell_open(cfg, shell_path, &shell, err, errlen);
 *     for each command:  venv_shell_run(shell, line, &code, err, errlen);
 *     venv_shell_close(shell);
 */
typedef struct venv_shell venv_shell;

/* Start `shell_path` inside the environment described by `cfg`, with its
 * stdin connected to a pipe. Returns 0 and stores the session in `*out`, or
 * -1 with a message in `err`. */
int venv_shell_open(const venv_config *cfg, const char *shell_path,
                    venv_shell **out, char *err, size_t errlen);

/* Send one command line to the session and block until it has finished,
 * storing its exit status in `*exit_code`. Returns 0 on success, -1 when the
 * command could not be handed over or its status could not be read. */
int venv_shell_run(venv_shell *shell, const char *command_line, int *exit_code,
                   char *err, size_t errlen);

/* Ask the running shell to print its current environment and capture it out of
 * band, without disturbing the command stream. On success 0 is returned and
 * `*out_kv` points at `*out_count` freshly allocated "KEY=VALUE" strings
 * followed by a NULL terminator (free with venv_free_argv()); on failure -1 with
 * a message in `err`.
 *
 * This is what lets venvSnapShotEnv() / venvCompareSnapshotEnv() inside a
 * persistent-shell session see the shell's live environment — e.g. the
 * variables `vcvars64.bat` just set — rather than venv's own. */
int venv_shell_dump_env(venv_shell *shell, char ***out_kv, size_t *out_count,
                        char *err, size_t errlen);

/* Close the session's stdin, wait for the shell to exit and release it.
 * `shell` may be NULL. */
void venv_shell_close(venv_shell *shell);

#ifdef __cplusplus
}
#endif

#endif /* VENV_PROCESS_SPAWNER_H */
