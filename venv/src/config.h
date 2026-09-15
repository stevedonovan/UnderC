#ifndef VENV_CONFIG_H
#define VENV_CONFIG_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* One command to spawn as its own child process. `argv` is the tokenised
 * command line, NULL-terminated and ready for execvp() / CreateProcess. */
typedef struct {
    char  *line;         /* the command line as written, for diagnostics */
    char **argv;         /* NULL-terminated */
    size_t argc;
} venv_command;

/* One environment variable of the child processes. */
typedef struct {
    char *key;
    char *value;
} venv_env_var;

/* The mutable state a .cvc configuration builds up through the venv* API.
 *
 * There is no configuration-file parser any more: a .cvc file is C++ source
 * run by the embedded UnderC interpreter, and every venv* call it makes lands
 * here through the native bridge (see underc_bridge.h). */
typedef struct {
    /* Root directory of the virtual environment. The child processes see this
     * directory as their working directory (Windows) or filesystem root
     * (Linux chroot). When `venvRootDir()` is never called this is filled in
     * with venv's current working directory and `root_dir_defaulted`
     * is set, in which case Linux does *not* chroot and no privileges are
     * needed. */
    char *root_dir;
    int   root_dir_defaulted;

    /* Environment variables handed to the child processes. Seeded from
     * venv's own environment, then edited by venvSetEnv() /
     * venvPreEnv() / venvAppEnv(). */
    venv_env_var *env_vars;
    size_t        env_count;

    /* The per-user venv source directory whose .c / .cpp files are auto-loaded
     * into the interpreter: %APPDATA%\venv on Windows, $XDG_CONFIG_HOME/venv or
     * $HOME/.config/venv on Linux. NULL when it could not be determined. */
    char *venv_dir;
} venv_config;

/* Zero-initialise a config so it is safe to pass to venv_config_free(). */
void venv_config_init(venv_config *cfg);
void venv_config_free(venv_config *cfg);

/* Seed the environment table from the process environment and fill in
 * `venv_dir` and a default `root_dir` (the current working directory).
 * Returns 0, or -1 with a message in `err`. */
int venv_config_prepare(venv_config *cfg, char *err, size_t errlen);

/* venvRootDir(): validate `path` (must be an existing directory) and make it
 * the virtual root. Returns 0, or -1 with a message in `err`. */
int venv_config_set_root_dir(venv_config *cfg, const char *path, char *err,
                             size_t errlen);

/* venvSetEnv(): set/replace a child-process environment variable. Name
 * matching follows the host rules (case-insensitive on Windows). */
void venv_config_set_env(venv_config *cfg, const char *key, const char *value);

/* venvPreEnv() / venvAppEnv(): prepend / append `fragment` to the current
 * value of `key` (verbatim — no separator is inserted). The variable is
 * created when it does not exist yet. */
void venv_config_prepend_env(venv_config *cfg, const char *key,
                             const char *fragment);
void venv_config_append_env(venv_config *cfg, const char *key,
                            const char *fragment);

/* Current value of a child-process environment variable, or NULL when unset. */
const char *venv_config_get_env(const venv_config *cfg, const char *key);

/* Resolve a configuration / source file argument to the path that should be
 * opened.
 *
 * A path that says where it lives is used verbatim: an absolute path, and one
 * that is explicitly relative to the current directory (`./x.cvc`, `.\x.cvc`,
 * `../x.cvc`). Anything else is a bare name and is looked up in the per-user
 * venv directory (`cfg->venv_dir`, the same place the auto-loaded .c / .cpp
 * files come from), so `venv msvc.cvc` picks up
 * `%APPDATA%\venv\msvc.cvc`. When it is not there the argument is kept as
 * written, so the current directory still works as a fallback and the error
 * message names what the user typed.
 *
 * Returns a freshly allocated path; never NULL. */
char *venv_config_resolve_source_path(const venv_config *cfg, const char *path);

/* Collect the auto-load source files (*.c, *.cpp) in `dir`, sorted by name.
 * Returns a NULL-terminated, freshly allocated array of freshly allocated
 * absolute paths (free with venv_free_argv()); `*count` receives the number of
 * entries. A missing directory yields an empty list, not an error. */
char **venv_config_collect_sources(const char *dir, size_t *count);

#ifdef __cplusplus
}
#endif

#endif /* VENV_CONFIG_H */
