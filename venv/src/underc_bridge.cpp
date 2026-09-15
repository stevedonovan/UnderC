/* Bridge between venv (C) and the embedded UnderC interpreter.
 *
 * Only this translation unit is C++, and only it is aware of UnderC.
 *
 * A .cvc configuration file is ordinary C++ source. The interpreter is started
 * WITH its standard-library prelude (uc_init(NULL, 1) => `#include <classlib.h>`
 * + `using namespace std;`), so a .cvc file may use <string>, <vector>, <map>,
 * <iostream> and friends. The STL headers are found under
 * <uclp>/include/underc/uclstl; venv points UnderC there by setting
 * UC_HOME before uc_init().
 *
 * Every venv* function the config calls is a native function imported below.
 * They edit the child environment and actually spawn the commands, so this
 * file drives execution — main.c only sets things up and runs main(). */

extern "C" {
#include "underc_bridge.h"
#include "cmdline.h"
#include "process_spawner.h"
#include "util.h"
}

#include <underc/ucdl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#if defined(PLATFORM_WINDOWS)
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#  include <windows.h>
#  define venv_environ _environ
#else
#  include <unistd.h>
extern char **environ;
#  define venv_environ environ
#endif

/* ── State ──────────────────────────────────────────────────────────────── */

static venv_config *g_cfg        = NULL;
static int          g_uc_started = 0;

static venv_shell  *g_shell      = NULL;
static char        *g_shell_path = NULL;

static char       **g_app_commands      = NULL;
static size_t       g_app_command_count = 0;

static int          g_last_exit_code = 0;
static unsigned     g_command_index  = 0;

/* Environment override installed while a snapshot runs inside a persistent
 * shell: a NULL-terminated array of freshly allocated "KEY=VALUE" strings. */
static char       **g_env_override       = NULL;
static size_t       g_env_override_count = 0;
static int          g_env_override_on    = 0;

static char        *g_ret_buf = NULL;

static const char *ret_copy(const char *s)
{
    free(g_ret_buf);
    g_ret_buf = venv_xstrdup(s ? s : "");
    return g_ret_buf;
}

/* ── Environment snapshots ──────────────────────────────────────────────── */

struct EnvSet {
    char **kv;
    size_t n;
};

struct NamedSnapshot {
    char  *id;
    EnvSet set;
};

static NamedSnapshot *g_snaps      = NULL;
static size_t         g_snap_count = 0;

static void env_set_free(EnvSet *s)
{
    size_t i;
    for (i = 0; i < s->n; ++i) {
        free(s->kv[i]);
    }
    free(s->kv);
    s->kv = NULL;
    s->n  = 0;
}

/* Capture the environment a snapshot should currently see:
 *   - the shell override, when one is installed;
 *   - otherwise the child environment the config has built so far;
 *   - otherwise venv's own environment. */
static EnvSet env_capture(void)
{
    EnvSet out;
    size_t i;

    out.kv = NULL;
    out.n  = 0;

    if (g_env_override_on) {
        out.kv = (char **)venv_xmalloc((g_env_override_count + 1) *
                                       sizeof(*out.kv));
        for (i = 0; i < g_env_override_count; ++i) {
            out.kv[i] = venv_xstrdup(g_env_override[i]);
        }
        out.kv[g_env_override_count] = NULL;
        out.n                        = g_env_override_count;
        return out;
    }

    if (g_cfg && g_cfg->env_count > 0) {
        out.kv = (char **)venv_xmalloc((g_cfg->env_count + 1) * sizeof(*out.kv));
        for (i = 0; i < g_cfg->env_count; ++i) {
            venv_buf b;
            venv_buf_init(&b);
            venv_buf_append_str(&b, g_cfg->env_vars[i].key);
            venv_buf_push(&b, '=');
            venv_buf_append_str(&b, g_cfg->env_vars[i].value);
            out.kv[i] = venv_buf_release(&b);
        }
        out.kv[g_cfg->env_count] = NULL;
        out.n                    = g_cfg->env_count;
        return out;
    }

    {
        char **env   = venv_environ;
        size_t count = 0;
        if (env) {
            while (env[count]) {
                ++count;
            }
        }
        out.kv = (char **)venv_xmalloc((count + 1) * sizeof(*out.kv));
        for (i = 0; i < count; ++i) {
            if (env[i][0] == '=') {
                continue; /* Windows "=C:" drive-cwd pseudo-entries */
            }
            out.kv[out.n++] = venv_xstrdup(env[i]);
        }
        out.kv[out.n] = NULL;
    }
    return out;
}

static void kv_split(const char *entry, char **key, const char **val)
{
    const char *eq = strchr(entry, '=');
    if (!eq) {
        *key = venv_xstrdup(entry);
        *val = "";
        return;
    }
    *key = venv_xstrndup(entry, (size_t)(eq - entry));
    *val = eq + 1;
}

#if defined(PLATFORM_WINDOWS)
#  define venv_key_equals(a, b) (_stricmp((a), (b)) == 0)
#else
#  define venv_key_equals(a, b) (strcmp((a), (b)) == 0)
#endif

static const char *env_set_lookup(const EnvSet *s, const char *key)
{
    size_t i;
    for (i = 0; i < s->n; ++i) {
        char       *k;
        const char *v;
        int         hit;
        kv_split(s->kv[i], &k, &v);
        hit = venv_key_equals(k, key);
        free(k);
        if (hit) {
            return v;
        }
    }
    return NULL;
}

static NamedSnapshot *snap_find(const char *id)
{
    size_t i;
    for (i = 0; i < g_snap_count; ++i) {
        if (strcmp(g_snaps[i].id, id) == 0) {
            return &g_snaps[i];
        }
    }
    return NULL;
}

static void env_override_clear(void)
{
    size_t i;
    if (g_env_override) {
        for (i = 0; i < g_env_override_count; ++i) {
            free(g_env_override[i]);
        }
        free(g_env_override);
    }
    g_env_override       = NULL;
    g_env_override_count = 0;
    g_env_override_on    = 0;
}

static void env_override_install(char *const *kv, size_t n)
{
    size_t i;
    env_override_clear();
    if (!kv || n == 0) {
        return;
    }
    g_env_override = (char **)venv_xmalloc((n + 1) * sizeof(*g_env_override));
    for (i = 0; i < n; ++i) {
        g_env_override[i] = venv_xstrdup(kv[i]);
    }
    g_env_override[n]    = NULL;
    g_env_override_count = n;
    g_env_override_on    = 1;
}

/* When a persistent shell is open, load its live environment so a following
 * snapshot / compare reflects what commands like vcvars64.bat changed. */
static void refresh_snapshot_source(void)
{
    char **kv = NULL;
    size_t n  = 0;
    char   err[512];

    env_override_clear();
    if (!g_shell) {
        return;
    }
    if (venv_shell_dump_env(g_shell, &kv, &n, err, sizeof(err)) == 0) {
        env_override_install(kv, n);
        venv_free_argv(kv, n);
    } else {
        fprintf(stderr,
                "venv: warning: could not read the shell environment: "
                "%s\n",
                err);
    }
}

static void do_snapshot(const char *id)
{
    NamedSnapshot *s;
    const char    *name = (id && id[0]) ? id : "default";

    s = snap_find(name);
    if (s) {
        env_set_free(&s->set);
    } else {
        g_snaps = (NamedSnapshot *)venv_xrealloc(
            g_snaps, (g_snap_count + 1) * sizeof(*g_snaps));
        s     = &g_snaps[g_snap_count++];
        s->id = venv_xstrdup(name);
    }
    s->set = env_capture();
    printf("venv: snapshot '%s' captured (%lu variables)\n", name,
           (unsigned long)s->set.n);
    fflush(stdout);
}

static void do_snapshot_compare(const char *id)
{
    const char          *name = (id && id[0]) ? id : "default";
    const NamedSnapshot *s    = snap_find(name);
    EnvSet               now;
    size_t               i;
    size_t               changes = 0;

    if (!s) {
        printf("venv: no snapshot '%s' to compare against\n", name);
        fflush(stdout);
        return;
    }

    now = env_capture();
    printf("venv: snapshot '%s' vs current environment:\n", name);

    for (i = 0; i < now.n; ++i) {
        char       *key;
        const char *newv;
        const char *oldv;
        kv_split(now.kv[i], &key, &newv);
        oldv = env_set_lookup(&s->set, key);
        if (!oldv) {
            printf("  + %s=%s\n", key, newv);
            ++changes;
        } else if (strcmp(oldv, newv) != 0) {
            printf("  ~ %s\n      old: %s\n      new: %s\n", key, oldv, newv);
            ++changes;
        }
        free(key);
    }
    for (i = 0; i < s->set.n; ++i) {
        char       *key;
        const char *oldv;
        kv_split(s->set.kv[i], &key, &oldv);
        if (!env_set_lookup(&now, key)) {
            printf("  - %s  (was: %s)\n", key, oldv);
            ++changes;
        }
        free(key);
    }

    if (changes == 0) {
        printf("  (no differences)\n");
    }
    printf("venv: %lu environment change(s)\n", (unsigned long)changes);
    fflush(stdout);
    env_set_free(&now);
}

/* ── Environment editing (venvSetEnv / venvPreEnv / venvAppEnv) ─────────── */

enum env_edit_mode { ENV_SET = 0, ENV_PREPEND = 1, ENV_APPEND = 2 };

/* Mutate venv's OWN process environment.
 *
 * This is what makes a shell-less env edit actually take effect: a following
 * venvExeCommand() child inherits our environment, and — the subtle part on
 * Windows — CreateProcess() resolves the executable image through the PATH of
 * the *calling* process, never through the environment block handed to the
 * child. Without this, `venvPreEnv("PATH", "...cmake\\bin;")` followed by
 * `venvExeCommand("cmake --help")` fails with "cannot find the file
 * specified", because the new PATH only ever reached the child. */
static void proc_env_set(const char *name, const char *value)
{
#if defined(PLATFORM_WINDOWS)
    _putenv_s(name, value ? value : "");
#else
    setenv(name, value ? value : "", 1);
#endif
}

/* Which flavour of shell is open, so an `inShell` env edit uses its syntax. */
enum shell_kind { SHELL_POSIX = 0, SHELL_CMD, SHELL_PWSH };

static shell_kind current_shell_kind(void)
{
    const char *base;
    const char *p;

    if (!g_shell_path) {
        return SHELL_POSIX;
    }
    base = g_shell_path;
    for (p = g_shell_path; *p; ++p) {
        if (*p == '\\' || *p == '/' || *p == ':') {
            base = p + 1;
        }
    }
    if (venv_iequals(base, "cmd.exe") || venv_iequals(base, "cmd")) {
        return SHELL_CMD;
    }
    if (venv_iequals(base, "powershell.exe") ||
        venv_iequals(base, "powershell") || venv_iequals(base, "pwsh.exe") ||
        venv_iequals(base, "pwsh")) {
        return SHELL_PWSH;
    }
    return SHELL_POSIX;
}

/* Append `s` as a PowerShell single-quoted literal (embedded ' is doubled). */
static void append_pwsh_quoted(venv_buf *b, const char *s)
{
    size_t i;
    venv_buf_push(b, '\'');
    for (i = 0; s[i]; ++i) {
        if (s[i] == '\'') {
            venv_buf_push(b, '\'');
        }
        venv_buf_push(b, s[i]);
    }
    venv_buf_push(b, '\'');
}

/* Build the shell statement that performs `mode` on `name` with `value` in the
 * syntax of the open shell, and send it in — so the change lands in the live
 * shell process and is felt by every following venvExeCommand(cmd, true). */
static void env_edit_in_shell(const char *name, const char *value, int mode)
{
    venv_buf line;
    char    *text;
    char     err[512];
    int      code = 0;

    venv_buf_init(&line);
    switch (current_shell_kind()) {
    case SHELL_CMD:
        /* set "NAME=[frag]%NAME%[frag]" */
        venv_buf_append_str(&line, "set \"");
        venv_buf_append_str(&line, name);
        venv_buf_push(&line, '=');
        if (mode == ENV_PREPEND) {
            venv_buf_append_str(&line, value);
        }
        if (mode != ENV_SET) {
            venv_buf_push(&line, '%');
            venv_buf_append_str(&line, name);
            venv_buf_push(&line, '%');
        }
        if (mode == ENV_APPEND || mode == ENV_SET) {
            venv_buf_append_str(&line, value);
        }
        venv_buf_push(&line, '"');
        break;
    case SHELL_PWSH:
        /* $env:NAME = 'frag' + $env:NAME + 'frag' */
        venv_buf_append_str(&line, "$env:");
        venv_buf_append_str(&line, name);
        venv_buf_append_str(&line, " = ");
        if (mode == ENV_PREPEND) {
            append_pwsh_quoted(&line, value);
            venv_buf_append_str(&line, " + ");
        }
        if (mode != ENV_SET) {
            venv_buf_append_str(&line, "$env:");
            venv_buf_append_str(&line, name);
        }
        if (mode == ENV_APPEND) {
            venv_buf_append_str(&line, " + ");
            append_pwsh_quoted(&line, value);
        }
        if (mode == ENV_SET) {
            append_pwsh_quoted(&line, value);
        }
        break;
    default: /* SHELL_POSIX */
        /* export NAME="[frag]${NAME}[frag]" */
        venv_buf_append_str(&line, "export ");
        venv_buf_append_str(&line, name);
        venv_buf_append_str(&line, "=\"");
        if (mode == ENV_PREPEND) {
            venv_buf_append_str(&line, value);
        }
        if (mode != ENV_SET) {
            venv_buf_append_str(&line, "${");
            venv_buf_append_str(&line, name);
            venv_buf_push(&line, '}');
        }
        if (mode == ENV_APPEND || mode == ENV_SET) {
            venv_buf_append_str(&line, value);
        }
        venv_buf_push(&line, '"');
        break;
    }

    text = venv_buf_release(&line);
    printf("venv: env (shell): %s\n", text);
    fflush(stdout);

    if (venv_shell_run(g_shell, text, &code, err, sizeof(err)) != 0) {
        fprintf(stderr, "venv: %s\n", err);
        g_last_exit_code = 1;
    }
    free(text);
}

/* Shared back end of venvSetEnv / venvPreEnv / venvAppEnv.
 *   in_shell == 0 (default): edit the child environment table AND mirror the
 *       result into venv's own environment (see proc_env_set).
 *   in_shell != 0: inject the change into the running persistent shell
 *       (venvStartShell must have been called first). */
static void env_edit(const char *name, const char *value, int mode, int in_shell)
{
    if (!g_cfg || !name || !name[0]) {
        return;
    }
    if (!value) {
        value = "";
    }

    if (in_shell) {
        if (!g_shell) {
            fprintf(stderr,
                    "venv: venvSetEnv/venvPreEnv/venvAppEnv(..., true) "
                    "but no shell is open (call venvStartShell first)\n");
            g_last_exit_code = 1;
            return;
        }
        env_edit_in_shell(name, value, mode);
        return;
    }

    switch (mode) {
    case ENV_PREPEND:
        venv_config_prepend_env(g_cfg, name, value);
        break;
    case ENV_APPEND:
        venv_config_append_env(g_cfg, name, value);
        break;
    default:
        venv_config_set_env(g_cfg, name, value);
        break;
    }
    proc_env_set(name, venv_config_get_env(g_cfg, name));
}

/* ── Command execution ─────────────────────────────────────────────────── */

static int run_standalone(const char *cmd)
{
    char       **argv = NULL;
    size_t       argc = 0;
    char         err[1024];
    venv_command command;
    int          code = 0;

    if (venv_split_command_line(cmd, &argv, &argc, err, sizeof(err)) != 0 ||
        argc == 0) {
        fprintf(stderr, "venv: %s\n",
                argc == 0 ? "empty command" : err);
        venv_free_argv(argv, argc);
        g_last_exit_code = 1;
        return 1;
    }

    command.line = (char *)cmd;
    command.argv = argv;
    command.argc = argc;

    printf("venv: [%u] running: %s\n", g_command_index, cmd);
    fflush(stdout);

    if (venv_process_spawner_run(g_cfg, &command, &code, err, sizeof(err)) !=
        0) {
        fprintf(stderr, "venv: %s\n", err);
        venv_free_argv(argv, argc);
        g_last_exit_code = 1;
        return 1;
    }
    venv_free_argv(argv, argc);

    printf("venv: [%u] child exited with code %d\n", g_command_index,
           code);
    fflush(stdout);
    g_last_exit_code = code;
    return code;
}

static int run_in_shell(const char *cmd)
{
    char err[1024];
    int  code = 0;

    if (!g_shell) {
        fprintf(stderr,
                "venv: venvExeCommand(..., true) but no shell is open "
                "(call venvStartShell first)\n");
        g_last_exit_code = 1;
        return 1;
    }
    printf("venv: [%u] shell: %s\n", g_command_index, cmd);
    fflush(stdout);

    if (venv_shell_run(g_shell, cmd, &code, err, sizeof(err)) != 0) {
        fprintf(stderr, "venv: %s\n", err);
        g_last_exit_code = 1;
        return 1;
    }
    printf("venv: [%u] command exited with code %d\n", g_command_index,
           code);
    fflush(stdout);
    g_last_exit_code = code;
    return code;
}

static int exec_command(const char *cmd, int in_shell)
{
    if (!cmd || cmd[0] == '\0') {
        return 0;
    }
    ++g_command_index;
    return in_shell ? run_in_shell(cmd) : run_standalone(cmd);
}

/* venvExeCommandString(): run `cmd` through the host command interpreter in the
 * environment built so far and hand its stdout back to the interpreter.
 *
 * Unlike venvExeCommand() this always goes through a shell, because what a
 * config wants to read back is usually a shell built-in or a script's effect
 * (`SET`, `env`, `call vcvars64.bat & SET`) rather than an executable image.
 * The captured text is stdout only; the child's stderr still reaches the
 * terminal, so a failing command explains itself instead of poisoning the
 * string. */
static const char *exec_command_capture(const char *cmd)
{
    char       *text = NULL;
    size_t      len  = 0;
    char        err[1024];
    int         code = 0;
    const char *out;

    if (!cmd || cmd[0] == '\0') {
        return ret_copy("");
    }
    ++g_command_index;
    printf("venv: [%u] capturing: %s\n", g_command_index, cmd);
    fflush(stdout);

    if (venv_process_spawner_capture(g_cfg, cmd, &text, &len, &code, err,
                                     sizeof(err)) != 0) {
        fprintf(stderr, "venv: %s\n", err);
        g_last_exit_code = 1;
        return ret_copy("");
    }

    printf("venv: [%u] command exited with code %d "
           "(%lu bytes captured)\n",
           g_command_index, code, (unsigned long)len);
    fflush(stdout);
    g_last_exit_code = code;

    out = ret_copy(text);
    free(text);
    return out;
}

/* ── Native interop functions (imported into the interpreter) ────────────── */

extern "C" void venv_uc_print(const char *s)
{
    printf("%s\n", s ? s : "");
    fflush(stdout);
}

extern "C" void venv_uc_root_dir(const char *path)
{
    char err[1024];

    if (!g_cfg) {
        return;
    }
    if (venv_config_set_root_dir(g_cfg, path ? path : "", err, sizeof(err)) !=
        0) {
        fprintf(stderr, "venv: %s\n", err);
        g_last_exit_code = 1;
        return;
    }
    printf("venv: root dir = %s\n", g_cfg->root_dir);
    fflush(stdout);
}

extern "C" void venv_uc_set_env(const char *name, const char *value)
{
    env_edit(name, value, ENV_SET, 0);
}

extern "C" void venv_uc_set_env_s(const char *name, const char *value,
                                  int in_shell)
{
    env_edit(name, value, ENV_SET, in_shell ? 1 : 0);
}

extern "C" void venv_uc_pre_env(const char *name, const char *value)
{
    env_edit(name, value, ENV_PREPEND, 0);
}

extern "C" void venv_uc_pre_env_s(const char *name, const char *value,
                                  int in_shell)
{
    env_edit(name, value, ENV_PREPEND, in_shell ? 1 : 0);
}

extern "C" void venv_uc_app_env(const char *name, const char *value)
{
    env_edit(name, value, ENV_APPEND, 0);
}

extern "C" void venv_uc_app_env_s(const char *name, const char *value,
                                  int in_shell)
{
    env_edit(name, value, ENV_APPEND, in_shell ? 1 : 0);
}

extern "C" const char *venv_uc_env_get(const char *name)
{
    const char *v = (g_cfg && name) ? venv_config_get_env(g_cfg, name) : NULL;
    if (!v) {
        v = name ? getenv(name) : NULL;
    }
    return ret_copy(v);
}

extern "C" void venv_uc_snapshot_env(void)
{
    refresh_snapshot_source();
    do_snapshot("default");
    env_override_clear();
}

extern "C" void venv_uc_compare_snapshot_env(void)
{
    refresh_snapshot_source();
    do_snapshot_compare("default");
    env_override_clear();
}

extern "C" void venv_uc_exe_command_1(const char *cmd)
{
    exec_command(cmd, 0);
}

extern "C" void venv_uc_exe_command_2(const char *cmd, int in_shell)
{
    exec_command(cmd, in_shell ? 1 : 0);
}

extern "C" const char *venv_uc_exe_command_string(const char *cmd)
{
    return exec_command_capture(cmd);
}

extern "C" void venv_uc_start_shell(const char *shell_path)
{
    char err[1024];

    if (g_shell) {
        fprintf(stderr,
                "venv: a shell is already open; call venvStopShell "
                "first\n");
        return;
    }
    if (!shell_path || shell_path[0] == '\0') {
        fprintf(stderr, "venv: venvStartShell(): empty shell path\n");
        g_last_exit_code = 1;
        return;
    }
    printf("venv: starting persistent shell (%s)\n", shell_path);
    fflush(stdout);

    if (venv_shell_open(g_cfg, shell_path, &g_shell, err, sizeof(err)) != 0) {
        fprintf(stderr, "venv: %s\n", err);
        g_shell          = NULL;
        g_last_exit_code = 1;
        return;
    }
    free(g_shell_path);
    g_shell_path = venv_xstrdup(shell_path);
}

extern "C" void venv_uc_stop_shell(void)
{
    if (!g_shell) {
        return;
    }
    venv_shell_close(g_shell);
    g_shell = NULL;
    free(g_shell_path);
    g_shell_path = NULL;
    printf("venv: persistent shell stopped\n");
    fflush(stdout);
}

extern "C" void venv_uc_exec_app_commands(void)
{
    size_t i;

    if (g_app_command_count == 0) {
        printf("venv: no -ac commands to execute\n");
        fflush(stdout);
        return;
    }
    for (i = 0; i < g_app_command_count; ++i) {
        exec_command(g_app_commands[i], g_shell ? 1 : 0);
    }
}

extern "C" int venv_uc_app_command_count(void)
{
    return (int)g_app_command_count;
}

extern "C" const char *venv_uc_app_command_at(int index)
{
    if (index < 0 || (size_t)index >= g_app_command_count) {
        return ret_copy("");
    }
    return ret_copy(g_app_commands[index]);
}

extern "C" int venv_uc_last_exit_code(void)
{
    return g_last_exit_code;
}

/* ── UnderC library prefix (UC_HOME) resolution ─────────────────────────── */

/* UnderC appends "include/underc/uclstl" to UC_HOME and gives up when that
 * directory is missing — but uc_init() ignores that failure and carries on to
 * evaluate its prelude with no include path set at all, which segfaults. The
 * prefix therefore has to be validated here, before uc_init() is ever called;
 * otherwise a stale or mistyped -uclp makes venv die silently right
 * after its banner, without ever loading the .cvc or running a command. */

static int is_directory(const char *path)
{
    struct stat st;

    if (!path || !path[0]) {
        return 0;
    }
    if (stat(path, &st) != 0) {
        return 0;
    }
    return (st.st_mode & S_IFMT) == S_IFDIR;
}

static int is_sep(char c)
{
#if defined(PLATFORM_WINDOWS)
    return c == '\\' || c == '/';
#else
    return c == '/';
#endif
}

static char *path_join(const char *dir, const char *name)
{
    venv_buf b;

    venv_buf_init(&b);
    venv_buf_append_str(&b, dir);
    if (b.len > 0 && !is_sep(b.data[b.len - 1])) {
#if defined(PLATFORM_WINDOWS)
        venv_buf_push(&b, '\\');
#else
        venv_buf_push(&b, '/');
#endif
    }
    venv_buf_append_str(&b, name);
    return venv_buf_release(&b);
}

/* The directory UnderC itself looks for: <prefix>/include/underc/uclstl. */
static char *uclstl_dir(const char *prefix)
{
    char *include = path_join(prefix, "include");
    char *underc  = path_join(include, "underc");
    char *uclstl  = path_join(underc, "uclstl");

    free(include);
    free(underc);
    return uclstl;
}

static int prefix_is_valid(const char *prefix)
{
    char *uclstl;
    int   ok;

    if (!prefix || !prefix[0]) {
        return 0;
    }
    uclstl = uclstl_dir(prefix);
    ok     = is_directory(uclstl);
    free(uclstl);
    return ok;
}

/* Everything up to (but not including) the last separator, or NULL when there
 * is no parent left. */
static char *parent_dir(const char *path)
{
    size_t n;

    if (!path) {
        return NULL;
    }
    n = strlen(path);
    while (n > 0 && is_sep(path[n - 1])) {
        --n; /* trailing separators */
    }
    while (n > 0 && !is_sep(path[n - 1])) {
        --n; /* the last component */
    }
    while (n > 1 && is_sep(path[n - 1])) {
        --n; /* the separator itself */
    }
    if (n == 0) {
        return NULL;
    }
    return venv_xstrndup(path, n);
}

/* Directory holding the running venv executable, or NULL. */
static char *executable_dir(void)
{
#if defined(PLATFORM_WINDOWS)
    char  buf[MAX_PATH];
    DWORD n = GetModuleFileNameA(NULL, buf, (DWORD)sizeof(buf));

    if (n == 0 || n >= sizeof(buf)) {
        return NULL;
    }
    buf[n] = '\0';
    return parent_dir(buf);
#else
    char    buf[4096];
    ssize_t n = readlink("/proc/self/exe", buf, sizeof(buf) - 1);

    if (n <= 0) {
        return NULL;
    }
    buf[n] = '\0';
    return parent_dir(buf);
#endif
}

/* An ordered list of places a prefix may come from, kept together with a label
 * so both the banner and the failure message can name the source. */
struct prefix_candidate {
    const char *label;
    char       *path; /* owned, may be NULL */
};

#define VENV_MAX_PREFIX_CANDIDATES 8

static void candidate_add(prefix_candidate *list, size_t *n, const char *label,
                          char *path)
{
    if (!path || !path[0] || *n >= VENV_MAX_PREFIX_CANDIDATES) {
        free(path);
        return;
    }
    list[*n].label = label;
    list[*n].path  = path;
    ++(*n);
}

static size_t collect_candidates(prefix_candidate *list)
{
    size_t n       = 0;
    char  *exe_dir = executable_dir();

    candidate_add(list, &n, "UC_HOME", getenv("UC_HOME")
                                           ? venv_xstrdup(getenv("UC_HOME"))
                                           : NULL);
    if (getenv("DEP_DIR")) {
        candidate_add(list, &n, "$DEP_DIR/underc",
                      path_join(getenv("DEP_DIR"), "underc"));
    }
    if (exe_dir) {
        char *parent = parent_dir(exe_dir);
        candidate_add(list, &n, "next to venv", venv_xstrdup(exe_dir));
        /* An installed layout: <prefix>/bin/venv. */
        candidate_add(list, &n, "above venv", parent);
        free(exe_dir);
    }
    candidate_add(list, &n, "built-in default", venv_xstrdup(VENV_DEFAULT_UCLP));
    return n;
}

static void candidates_free(prefix_candidate *list, size_t n)
{
    size_t i;
    for (i = 0; i < n; ++i) {
        free(list[i].path);
    }
}

int venv_underc_resolve_prefix(const char *requested, char **out_prefix,
                               const char **out_source, char *err,
                               size_t errlen)
{
    prefix_candidate candidates[VENV_MAX_PREFIX_CANDIDATES];
    size_t           count;
    size_t           i;
    venv_buf         msg;
    char            *text;

    *out_prefix = NULL;
    if (out_source) {
        *out_source = "";
    }

    /* An explicit -uclp is an instruction, not a hint: when it does not hold an
     * UnderC install, say so instead of quietly running against another one. */
    if (requested && requested[0]) {
        char *uclstl;

        if (prefix_is_valid(requested)) {
            *out_prefix = venv_xstrdup(requested);
            if (out_source) {
                *out_source = "-uclp";
            }
            return 0;
        }
        uclstl = uclstl_dir(requested);
        venv_buf_init(&msg);
        venv_buf_append_str(&msg, "-uclp '");
        venv_buf_append_str(&msg, requested);
        venv_buf_append_str(&msg,
                            "' is not an UnderC library prefix: no such "
                            "directory '");
        venv_buf_append_str(&msg, uclstl);
        venv_buf_push(&msg, '\'');
        free(uclstl);

        count = collect_candidates(candidates);
        for (i = 0; i < count; ++i) {
            if (prefix_is_valid(candidates[i].path)) {
                venv_buf_append_str(&msg, "; a usable prefix was found at '");
                venv_buf_append_str(&msg, candidates[i].path);
                venv_buf_append_str(&msg, "' (");
                venv_buf_append_str(&msg, candidates[i].label);
                venv_buf_push(&msg, ')');
                break;
            }
        }
        candidates_free(candidates, count);

        text = venv_buf_release(&msg);
        venv_set_error(err, errlen, "%s", text);
        free(text);
        return -1;
    }

    count = collect_candidates(candidates);
    for (i = 0; i < count; ++i) {
        if (prefix_is_valid(candidates[i].path)) {
            *out_prefix = venv_xstrdup(candidates[i].path);
            if (out_source) {
                *out_source = candidates[i].label;
            }
            candidates_free(candidates, count);
            return 0;
        }
    }

    venv_buf_init(&msg);
    venv_buf_append_str(&msg,
                        "no UnderC library prefix found - pass -uclp <prefix> "
                        "(a directory containing include/underc/uclstl). "
                        "Tried:");
    for (i = 0; i < count; ++i) {
        venv_buf_append_str(&msg, "\n    ");
        venv_buf_append_str(&msg, candidates[i].path);
        venv_buf_append_str(&msg, "  (");
        venv_buf_append_str(&msg, candidates[i].label);
        venv_buf_push(&msg, ')');
    }
    if (count == 0) {
        venv_buf_append_str(&msg, " (nothing)");
    }
    candidates_free(candidates, count);

    text = venv_buf_release(&msg);
    venv_set_error(err, errlen, "%s", text);
    free(text);
    return -1;
}

/* ── Interpreter lifecycle ─────────────────────────────────────────────── */

static void import_native(const char *decl, void *fn)
{
    char *buf = venv_xstrdup(decl);
    uc_import(buf, fn);
    free(buf);
}

static int uc_ok(int rc)
{
    return rc == 1;
}

static void pull_uc_error(char *err, size_t errlen, const char *what)
{
    char buf[1024];
    buf[0] = '\0';
    uc_error(buf, (int)sizeof(buf));
    if (buf[0]) {
        venv_set_error(err, errlen, "%s: %s", what, buf);
    } else {
        venv_set_error(err, errlen, "%s (see the UnderC diagnostic above)",
                       what);
    }
}

int venv_underc_init(venv_config *cfg, const char *uclp,
                     char *const *app_commands, size_t app_command_count,
                     char *err, size_t errlen)
{
    size_t i;

    g_cfg = cfg;

    /* Point UnderC at its library prefix so uc_init()'s prelude can find the
     * STL headers under <uclp>/include/underc/uclstl. Refuse to start when it
     * is not there: uc_init() would carry on with no include path and crash on
     * the prelude's first #include. */
    if (!prefix_is_valid(uclp)) {
        char *uclstl = uclstl_dir(uclp ? uclp : "");
        venv_set_error(err, errlen,
                       "the UnderC library prefix '%s' has no '%s' directory",
                       uclp ? uclp : "", uclstl);
        free(uclstl);
        return -1;
    }
#if defined(PLATFORM_WINDOWS)
    _putenv_s("UC_HOME", uclp);
#else
    setenv("UC_HOME", uclp, 1);
#endif

    g_app_command_count = app_command_count;
    if (app_command_count > 0) {
        g_app_commands =
            (char **)venv_xmalloc(app_command_count * sizeof(*g_app_commands));
        for (i = 0; i < app_command_count; ++i) {
            g_app_commands[i] = venv_xstrdup(app_commands[i]);
        }
    }

    /* use_defs = 1 => `#include <classlib.h>` + `using namespace std;`, so a
     * .cvc file can use the STL. */
    if (!uc_ok(uc_init(NULL, 1))) {
        g_uc_started = 1; /* the interpreter did initialise; let shutdown run */
        pull_uc_error(err, errlen, "starting the UnderC interpreter");
        return -1;
    }
    g_uc_started = 1;

    import_native("void venvPrint(const char*)", (void *)&venv_uc_print);
    import_native("void venvRootDir(const char*)", (void *)&venv_uc_root_dir);
    import_native("void venvSetEnv(const char*,const char*)",
                  (void *)&venv_uc_set_env);
    import_native("void venvSetEnv(const char*,const char*,int)",
                  (void *)&venv_uc_set_env_s);
    import_native("void venvPreEnv(const char*,const char*)",
                  (void *)&venv_uc_pre_env);
    import_native("void venvPreEnv(const char*,const char*,int)",
                  (void *)&venv_uc_pre_env_s);
    import_native("void venvAppEnv(const char*,const char*)",
                  (void *)&venv_uc_app_env);
    import_native("void venvAppEnv(const char*,const char*,int)",
                  (void *)&venv_uc_app_env_s);
    import_native("const char* venvEnvGet(const char*)",
                  (void *)&venv_uc_env_get);
    import_native("void venvSnapShotEnv()", (void *)&venv_uc_snapshot_env);
    import_native("void venvCompareSnapshotEnv()",
                  (void *)&venv_uc_compare_snapshot_env);
    import_native("void venvExeCommand(const char*)",
                  (void *)&venv_uc_exe_command_1);
    import_native("void venvExeCommand(const char*,int)",
                  (void *)&venv_uc_exe_command_2);
    import_native("const char* venvExeCommandString(const char*)",
                  (void *)&venv_uc_exe_command_string);
    import_native("void venvStartShell(const char*)",
                  (void *)&venv_uc_start_shell);
    import_native("void venvStopShell()", (void *)&venv_uc_stop_shell);
    import_native("void venvExecAppCommands()",
                  (void *)&venv_uc_exec_app_commands);
    import_native("int venvAppCommandCount()",
                  (void *)&venv_uc_app_command_count);
    import_native("const char* venvAppCommandAt(int)",
                  (void *)&venv_uc_app_command_at);
    import_native("int venvLastExitCode()", (void *)&venv_uc_last_exit_code);
    return 0;
}

int venv_underc_load_source(const char *path, char *err, size_t errlen)
{
    if (!g_uc_started) {
        venv_set_error(err, errlen, "UnderC is not initialised");
        return -1;
    }
    printf("venv: loading %s\n", path);
    fflush(stdout);
    if (!uc_ok(uc_load(path))) {
        char what[1200];
        snprintf(what, sizeof(what), "loading '%s'", path);
        pull_uc_error(err, errlen, what);
        return -1;
    }
    return 0;
}

int venv_underc_run_main(int *exit_code, char *err, size_t errlen)
{
    int rc;

    if (!g_uc_started) {
        venv_set_error(err, errlen, "UnderC is not initialised");
        return -1;
    }

    g_command_index  = 0;
    g_last_exit_code = 0;

    /* uc_run() => `#r`: runs the loaded program's main() synchronously, after
     * the interpreter's library / module initialisation. */
    rc = uc_run();

    /* If the config forgot to close its shell, close it now. */
    if (g_shell) {
        venv_shell_close(g_shell);
        g_shell = NULL;
        free(g_shell_path);
        g_shell_path = NULL;
    }

    if (!uc_ok(rc)) {
        pull_uc_error(err, errlen, "running the configuration's main()");
        return -1;
    }

    *exit_code = g_last_exit_code;
    return 0;
}

void venv_underc_shutdown(void)
{
    size_t i;

    if (g_shell) {
        venv_shell_close(g_shell);
        g_shell = NULL;
    }
    free(g_shell_path);
    g_shell_path = NULL;

    if (g_uc_started) {
        uc_finis();
        g_uc_started = 0;
    }

    env_override_clear();
    for (i = 0; i < g_snap_count; ++i) {
        free(g_snaps[i].id);
        env_set_free(&g_snaps[i].set);
    }
    free(g_snaps);
    g_snaps      = NULL;
    g_snap_count = 0;

    for (i = 0; i < g_app_command_count; ++i) {
        free(g_app_commands[i]);
    }
    free(g_app_commands);
    g_app_commands      = NULL;
    g_app_command_count = 0;

    free(g_ret_buf);
    g_ret_buf = NULL;
    g_cfg     = NULL;
}
