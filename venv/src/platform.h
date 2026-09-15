#ifndef VENV_PLATFORM_H
#define VENV_PLATFORM_H

#include "config.h"
#include "process_spawner.h"

#include <stddef.h>

/* Platform-specific entry point that:
 *   1. Sets up the virtual root (chroot on Linux when the config defines
 *      `application.root_dir`, Job Object on Windows)
 *   2. Applies environment variables
 *   3. Spawns `command` as a child process
 *
 * `command` is one entry of a venv_exec_group; the environment and the
 * virtual root come from `cfg`.
 *
 * Returns 0 on success, with the child's exit code stored in `*exit_code`,
 * or -1 on error, with a message written to `err`.
 *
 * Groups that define `exec.<group>.shell` do not use this path: they drive a
 * persistent shell through venv_shell_open() / venv_shell_run() /
 * venv_shell_close(), declared in process_spawner.h. */
int venv_spawn_in_venv(const venv_config *cfg, const venv_command *command,
                       int *exit_code, char *err, size_t errlen);

#endif /* VENV_PLATFORM_H */
