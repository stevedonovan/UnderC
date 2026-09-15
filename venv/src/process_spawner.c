#include "process_spawner.h"

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Markers that bracket an environment dump in the shell's output stream. */
#define VENV_ENV_BEGIN "__VENV_SPAWNER_ENV_BEGIN__"
#define VENV_ENV_END   "__VENV_SPAWNER_ENV_END__"

/* Split a block of `KEY=VALUE` lines into a NULL-terminated array of freshly
 * allocated strings. Lines without a `=` (blank lines, a stray banner) are
 * skipped. Never fails: an empty block yields a one-element array holding only
 * the NULL terminator. Free with venv_free_argv(). */
static char **split_env_lines(const char *data, size_t len, size_t *out_count)
{
    char **kv    = NULL;
    size_t count = 0;
    size_t cap   = 0;
    size_t start = 0;
    size_t i;

    for (i = 0; i <= len; ++i) {
        if (i == len || data[i] == '\n') {
            size_t line_len = i - start;
            const char *line = data + start;

            if (line_len > 0 && line[line_len - 1] == '\r') {
                --line_len;
            }
            if (line_len > 0 && memchr(line, '=', line_len) != NULL) {
                if (count == cap) {
                    cap = cap ? cap * 2 : 16;
                    kv  = (char **)venv_xrealloc(kv,
                                                 (cap + 1) * sizeof(*kv));
                }
                kv[count++] = venv_xstrndup(line, line_len);
            }
            start = i + 1;
        }
    }

    if (count == cap) {
        kv = (char **)venv_xrealloc(kv, (cap + 1) * sizeof(*kv));
    }
    if (!kv) {
        kv = (char **)venv_xmalloc(sizeof(*kv));
    }
    kv[count]  = NULL;
    *out_count = count;
    return kv;
}

/* ═════════════════════════════════════════════════════════════════════════
 *  LINUX implementation
 * ═════════════════════════════════════════════════════════════════════════ */
#if defined(PLATFORM_LINUX)

#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

/* File descriptor on which the persistent shell reports exit statuses back to
 * us. Keeping it out of band leaves the shell's stdout and stderr connected to
 * our own, so child output still reaches the terminal unfiltered. */
#define VENV_STATUS_FD 3

/* Appended after every command sent to a persistent shell: it reports the
 * status of the command that came just before it on VENV_STATUS_FD. `$?` is
 * expanded before the redirection is set up, so it is the status of the
 * command and not of the probe itself. */
static const char kStatusProbe[] = "echo \"$?\" >&3\n";

/* Build a NULL-terminated "KEY=VALUE" array for `environ`. Allocated in the
 * parent so the child does not have to allocate between fork() and exec(). */
static char **build_env_array(const venv_config *cfg)
{
    char **env = (char **)venv_xmalloc((cfg->env_count + 1) * sizeof(*env));
    size_t i;

    for (i = 0; i < cfg->env_count; ++i) {
        venv_buf entry;
        venv_buf_init(&entry);
        venv_buf_append_str(&entry, cfg->env_vars[i].key);
        venv_buf_push(&entry, '=');
        venv_buf_append_str(&entry, cfg->env_vars[i].value);
        env[i] = venv_buf_release(&entry);
    }
    env[cfg->env_count] = NULL;
    return env;
}

static void free_env_array(char **env)
{
    size_t i;

    for (i = 0; env[i]; ++i) {
        free(env[i]);
    }
    free(env);
}

/* chroot is only used when the config file defines `root_dir`; it is the one
 * step that needs root privileges, so a config without `root_dir` runs as an
 * ordinary user. */
static int check_chroot_privileges(const venv_config *cfg, char *err,
                                   size_t errlen)
{
    if (!cfg->root_dir_defaulted && geteuid() != 0) {
        venv_set_error(err, errlen,
                       "chroot requires root privileges. "
                       "Please run venv as root (or with sudo), "
                       "or omit application.root_dir from the config file to "
                       "run without chroot.");
        return -1;
    }
    return 0;
}

/* Enter the virtual root inside a freshly forked child. Never returns on
 * failure — the child exits with 127, matching a failed exec. */
static void child_enter_root(const venv_config *cfg)
{
    const int use_chroot = !cfg->root_dir_defaulted;

    /* 1. Change into the root directory. With chroot this also lets us chdir
     *    to "/" afterwards without relying on the old path still being valid;
     *    without chroot it is simply the child's cwd. */
    if (chdir(cfg->root_dir) != 0) {
        fprintf(stderr, "[child] chdir failed: %s\n", strerror(errno));
        _exit(127);
    }

    if (use_chroot) {
        /* 2. Pivot the root. */
        if (chroot(".") != 0) {
            fprintf(stderr, "[child] chroot failed: %s\n", strerror(errno));
            _exit(127);
        }

        /* 3. Make sure we're at "/" inside the new root. */
        if (chdir("/") != 0) {
            fprintf(stderr, "[child] chdir('/') after chroot failed: %s\n",
                    strerror(errno));
            _exit(127);
        }
    }
}

/* Turn a wait(2) status into an exit code. */
static int exit_code_of(int status)
{
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    if (WIFSIGNALED(status)) {
        return 128 + WTERMSIG(status);
    }
    return -1;
}

int venv_process_spawner_run(const venv_config *cfg,
                             const venv_command *command, int *exit_code,
                             char *err, size_t errlen)
{
    char **child_env;
    pid_t  pid;
    pid_t  waited;
    int    status = 0;

    if (check_chroot_privileges(cfg, err, errlen) != 0) {
        return -1;
    }

    child_env = build_env_array(cfg);

    pid = fork();
    if (pid < 0) {
        venv_set_error(err, errlen, "fork() failed: %s", strerror(errno));
        free_env_array(child_env);
        return -1;
    }

    if (pid == 0) {
        /* ── Child process ──────────────────────────────────────────────── */
        signal(SIGPIPE, SIG_DFL);
        child_enter_root(cfg);

        /* Replace the inherited environment with the configured one. */
        environ = child_env;

        execvp(command->argv[0], command->argv);

        /* execvp only returns on error. */
        fprintf(stderr, "[child] execvp('%s') failed: %s\n", command->argv[0],
                strerror(errno));
        _exit(127);
    }

    /* ── Parent process ─────────────────────────────────────────────────── */
    waited = waitpid(pid, &status, 0);
    free_env_array(child_env);
    if (waited < 0) {
        venv_set_error(err, errlen, "waitpid() failed: %s", strerror(errno));
        return -1;
    }

    if (WIFSIGNALED(status)) {
        fprintf(stderr, "Child terminated by signal %d\n", WTERMSIG(status));
    }
    *exit_code = exit_code_of(status);
    return 0;
}

/* ── Capturing a command's output ───────────────────────────────────────── */

int venv_process_spawner_capture(const venv_config *cfg,
                                 const char *command_line, char **out_text,
                                 size_t *out_len, int *exit_code, char *err,
                                 size_t errlen)
{
    char   **child_env;
    venv_buf out;
    pid_t    pid;
    pid_t    waited;
    int      pipe_fd[2];
    int      status = 0;

    if (check_chroot_privileges(cfg, err, errlen) != 0) {
        return -1;
    }
    if (pipe(pipe_fd) != 0) {
        venv_set_error(err, errlen, "pipe() failed: %s", strerror(errno));
        return -1;
    }

    child_env = build_env_array(cfg);

    /* Our own pending output has to be on the wire before the child starts
     * writing to the same terminal through the inherited stderr. */
    fflush(stdout);
    fflush(stderr);

    pid = fork();
    if (pid < 0) {
        venv_set_error(err, errlen, "fork() failed: %s", strerror(errno));
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        free_env_array(child_env);
        return -1;
    }

    if (pid == 0) {
        /* ── Child process ──────────────────────────────────────────────── */
        signal(SIGPIPE, SIG_DFL);
        close(pipe_fd[0]);
        if (dup2(pipe_fd[1], STDOUT_FILENO) < 0) {
            _exit(127);
        }
        close(pipe_fd[1]);
        child_enter_root(cfg);
        environ = child_env;

        execl("/bin/sh", "sh", "-c", command_line, (char *)NULL);
        fprintf(stderr, "[child] exec('/bin/sh') failed: %s\n",
                strerror(errno));
        _exit(127);
    }

    /* ── Parent process ─────────────────────────────────────────────────── */
    close(pipe_fd[1]);
    venv_buf_init(&out);
    for (;;) {
        char    chunk[4096];
        ssize_t n = read(pipe_fd[0], chunk, sizeof(chunk));

        if (n > 0) {
            venv_buf_append(&out, chunk, (size_t)n);
            continue;
        }
        if (n < 0 && errno == EINTR) {
            continue;
        }
        break;
    }
    close(pipe_fd[0]);

    waited = waitpid(pid, &status, 0);
    free_env_array(child_env);
    if (waited < 0) {
        venv_buf_free(&out);
        venv_set_error(err, errlen, "waitpid() failed: %s", strerror(errno));
        return -1;
    }

    if (out_len) {
        *out_len = out.len;
    }
    *out_text  = venv_buf_release(&out);
    *exit_code = exit_code_of(status);
    return 0;
}

/* ── Persistent shell session ───────────────────────────────────────────── */

struct venv_shell {
    pid_t pid;
    int   in_fd;     /* write end of the shell's stdin */
    int   status_fd; /* read end of the status channel (fd 3 in the shell) */
    int   reaped;
    int   status;    /* wait(2) status, valid once `reaped` is set */
};

static int write_all(int fd, const char *data, size_t len)
{
    size_t written = 0;

    while (written < len) {
        ssize_t n = write(fd, data + written, len - written);
        if (n < 0) {
            if (errno == EINTR) {
                continue;
            }
            return -1;
        }
        written += (size_t)n;
    }
    return 0;
}

/* Read one decimal status line from the status channel.
 * Returns 0 with `*value` set, 1 when the shell closed the channel (EOF), or
 * -1 on a read error. */
static int read_status(int fd, int *value, char *err, size_t errlen)
{
    char   buf[32];
    size_t len = 0;

    for (;;) {
        char    c;
        ssize_t n = read(fd, &c, 1);

        if (n == 0) {
            return 1;
        }
        if (n < 0) {
            if (errno == EINTR) {
                continue;
            }
            venv_set_error(err, errlen, "reading the shell status failed: %s",
                           strerror(errno));
            return -1;
        }
        if (c == '\n') {
            break;
        }
        if (len + 1 < sizeof(buf)) {
            buf[len++] = c;
        }
    }
    buf[len] = '\0';
    *value   = (int)strtol(buf, NULL, 10);
    return 0;
}

static void shell_reap(venv_shell *shell)
{
    if (!shell->reaped) {
        pid_t waited;
        do {
            waited = waitpid(shell->pid, &shell->status, 0);
        } while (waited < 0 && errno == EINTR);
        shell->reaped = 1;
    }
}

int venv_shell_open(const venv_config *cfg, const char *shell_path,
                    venv_shell **out, char *err, size_t errlen)
{
    char      **child_env;
    venv_shell *shell;
    int         in_pipe[2];
    int         status_pipe[2];
    pid_t       pid;

    *out = NULL;

    if (check_chroot_privileges(cfg, err, errlen) != 0) {
        return -1;
    }

    if (pipe(in_pipe) != 0) {
        venv_set_error(err, errlen, "pipe() failed: %s", strerror(errno));
        return -1;
    }
    if (pipe(status_pipe) != 0) {
        venv_set_error(err, errlen, "pipe() failed: %s", strerror(errno));
        close(in_pipe[0]);
        close(in_pipe[1]);
        return -1;
    }

    child_env = build_env_array(cfg);

    pid = fork();
    if (pid < 0) {
        venv_set_error(err, errlen, "fork() failed: %s", strerror(errno));
        free_env_array(child_env);
        close(in_pipe[0]);
        close(in_pipe[1]);
        close(status_pipe[0]);
        close(status_pipe[1]);
        return -1;
    }

    if (pid == 0) {
        /* ── Shell process ──────────────────────────────────────────────── */
        char *argv[2];

        signal(SIGPIPE, SIG_DFL);

        /* Keep only the ends this process needs. */
        close(in_pipe[1]);
        close(status_pipe[0]);

        if (in_pipe[0] != STDIN_FILENO) {
            if (dup2(in_pipe[0], STDIN_FILENO) < 0) {
                fprintf(stderr, "[shell] dup2(stdin) failed: %s\n",
                        strerror(errno));
                _exit(127);
            }
            close(in_pipe[0]);
        }
        if (status_pipe[1] != VENV_STATUS_FD) {
            if (dup2(status_pipe[1], VENV_STATUS_FD) < 0) {
                fprintf(stderr, "[shell] dup2(status) failed: %s\n",
                        strerror(errno));
                _exit(127);
            }
            close(status_pipe[1]);
        }

        child_enter_root(cfg);
        environ = child_env;

        /* stdout and stderr stay connected to ours, so everything the
         * commands print still goes straight to the terminal. */
        argv[0] = (char *)shell_path;
        argv[1] = NULL;
        execvp(argv[0], argv);

        fprintf(stderr, "[shell] execvp('%s') failed: %s\n", shell_path,
                strerror(errno));
        _exit(127);
    }

    /* ── Parent process ─────────────────────────────────────────────────── */
    free_env_array(child_env);
    close(in_pipe[0]);
    close(status_pipe[1]);

    /* A shell that dies early must surface as a write error, not as a signal
     * that kills venv. */
    signal(SIGPIPE, SIG_IGN);

    shell            = (venv_shell *)venv_xmalloc(sizeof(*shell));
    shell->pid       = pid;
    shell->in_fd     = in_pipe[1];
    shell->status_fd = status_pipe[0];
    shell->reaped    = 0;
    shell->status    = 0;

    *out = shell;
    return 0;
}

int venv_shell_run(venv_shell *shell, const char *command_line, int *exit_code,
                   char *err, size_t errlen)
{
    venv_buf message;
    char    *text;
    size_t   text_len;
    int      rc;

    if (shell->reaped) {
        venv_set_error(err, errlen,
                       "the shell exited before this command could run");
        return -1;
    }

    /* One command, then the probe that reports its status back on fd 3. */
    venv_buf_init(&message);
    venv_buf_append_str(&message, command_line);
    venv_buf_push(&message, '\n');
    venv_buf_append_str(&message, kStatusProbe);
    text_len = message.len;
    text     = venv_buf_release(&message);

    fflush(stdout);
    fflush(stderr);

    rc = write_all(shell->in_fd, text, text_len);
    if (rc != 0) {
        const int saved = errno;
        free(text);
        shell_reap(shell);
        venv_set_error(err, errlen, "the shell is no longer running: %s",
                       strerror(saved));
        return -1;
    }
    free(text);

    rc = read_status(shell->status_fd, exit_code, err, errlen);
    if (rc < 0) {
        return -1;
    }
    if (rc > 0) {
        /* The channel closed: the shell itself terminated, e.g. because the
         * command called `exit`. Its status becomes the command's status. */
        shell_reap(shell);
        *exit_code = exit_code_of(shell->status);
        return 0;
    }
    return 0;
}

/* Does the byte range [data, data+len) contain the C string `needle`? */
static int bytes_contain(const char *data, size_t len, const char *needle)
{
    size_t nlen = strlen(needle);
    size_t i;

    if (nlen == 0 || len < nlen) {
        return 0;
    }
    for (i = 0; i + nlen <= len; ++i) {
        if (memcmp(data + i, needle, nlen) == 0) {
            return 1;
        }
    }
    return 0;
}

int venv_shell_dump_env(venv_shell *shell, char ***out_kv, size_t *out_count,
                        char *err, size_t errlen)
{
    /* Route the dump through the out-of-band status channel (fd 3), so the
     * command output on stdout/stderr is left untouched. `env` writes one
     * KEY=VALUE per line; the markers let us find the block again. */
    static const char kDump[] =
        "echo " VENV_ENV_BEGIN " >&3\n"
        "env >&3\n"
        "echo " VENV_ENV_END " >&3\n";

    venv_buf     raw;
    char         chunk[4096];
    const size_t end_len = sizeof(VENV_ENV_END) - 1;
    char        *text;
    char        *begin;
    char        *end;
    char        *body;
    size_t       body_len;

    *out_kv    = NULL;
    *out_count = 0;

    if (shell->reaped) {
        venv_set_error(err, errlen, "the shell has already exited");
        return -1;
    }

    if (write_all(shell->in_fd, kDump, sizeof(kDump) - 1) != 0) {
        shell_reap(shell);
        venv_set_error(err, errlen, "the shell is no longer running: %s",
                       strerror(errno));
        return -1;
    }

    /* Read the status channel until the closing marker shows up. */
    venv_buf_init(&raw);
    for (;;) {
        ssize_t n = read(shell->status_fd, chunk, sizeof(chunk));

        if (n == 0) {
            venv_buf_free(&raw);
            shell_reap(shell);
            venv_set_error(err, errlen,
                           "the shell closed while dumping its environment");
            return -1;
        }
        if (n < 0) {
            if (errno == EINTR) {
                continue;
            }
            venv_buf_free(&raw);
            venv_set_error(err, errlen,
                           "reading the environment dump failed: %s",
                           strerror(errno));
            return -1;
        }
        venv_buf_append(&raw, chunk, (size_t)n);
        if (raw.len >= end_len &&
            bytes_contain(raw.data, raw.len, VENV_ENV_END)) {
            break;
        }
    }

    text  = venv_buf_release(&raw);
    begin = strstr(text, VENV_ENV_BEGIN);
    end   = strstr(text, VENV_ENV_END);
    if (begin && end && end > begin) {
        body = begin + (sizeof(VENV_ENV_BEGIN) - 1);
        while (*body == '\r' || *body == '\n') {
            ++body;
        }
        body_len = (size_t)(end - body);
        *out_kv  = split_env_lines(body, body_len, out_count);
    } else {
        *out_kv = split_env_lines("", 0, out_count);
    }
    free(text);
    return 0;
}

void venv_shell_close(venv_shell *shell)
{
    if (!shell) {
        return;
    }
    if (shell->in_fd >= 0) {
        close(shell->in_fd); /* EOF on stdin makes the shell exit */
        shell->in_fd = -1;
    }
    shell_reap(shell);
    if (shell->status_fd >= 0) {
        close(shell->status_fd);
        shell->status_fd = -1;
    }
    free(shell);
}

/* ═════════════════════════════════════════════════════════════════════════
 *  WINDOWS implementation
 * ═════════════════════════════════════════════════════════════════════════ */
#elif defined(PLATFORM_WINDOWS)

#ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

/* Written by the persistent shell after every command; the exit code follows
 * on the same line. cmd.exe has no spare file descriptor to report on, so the
 * status travels through the shell's stdout and is filtered out again here.
 *
 * Because the marker travels through the same stream as the command output,
 * the shell must not repeat the probe line back to us: cmd.exe echoes every
 * line it reads from a pipe *verbatim*, so an echoed probe would put a second,
 * bogus occurrence of the marker into the stream — one that carries the
 * unexpanded text `%ERRORLEVEL%` instead of a number. Two defences keep the
 * stream in step with the commands: the shell is started with `/Q` and put
 * into `echo off` (see venv_shell_open), and an occurrence that is not
 * followed by a number is treated as ordinary output (see
 * shell_find_status). */
static const char kStatusMarker[] = "__VENV_SPAWNER_STATUS__";

/* ── Helpers ────────────────────────────────────────────────────────────── */

/* Formats the last Win32 error into a freshly allocated string. */
static char *last_error_str(void)
{
    DWORD    err = GetLastError();
    LPSTR    sys = NULL;
    venv_buf out;
    char     code[32];

    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                   NULL, err, 0, (LPSTR)&sys, 0, NULL);

    venv_buf_init(&out);
    venv_buf_append_str(&out, sys ? sys : "unknown error");
    if (sys) {
        LocalFree(sys);
    }
    /* Trim the trailing newline FormatMessage appends. */
    while (out.len > 0 &&
           (out.data[out.len - 1] == '\n' || out.data[out.len - 1] == '\r')) {
        --out.len;
    }
    snprintf(code, sizeof(code), " (code=%lu)", (unsigned long)err);
    venv_buf_append_str(&out, code);
    return venv_buf_release(&out);
}

/* Build a Windows environment block: a sequence of KEY=VALUE\0 entries
 * terminated by an extra \0. */
static char *build_env_block(const venv_config *cfg)
{
    venv_buf block;
    size_t   i;

    venv_buf_init(&block);
    for (i = 0; i < cfg->env_count; ++i) {
        venv_buf_append_str(&block, cfg->env_vars[i].key);
        venv_buf_push(&block, '=');
        venv_buf_append_str(&block, cfg->env_vars[i].value);
        venv_buf_push(&block, '\0');
    }
    venv_buf_push(&block, '\0'); /* double-null terminator */
    return venv_buf_release(&block);
}

/* Build a command line string from argv tokens, quoting arguments that
 * contain whitespace. */
static char *build_cmdline(const venv_command *command)
{
    venv_buf out;
    size_t   i, j;

    venv_buf_init(&out);
    for (i = 0; i < command->argc; ++i) {
        const char *arg = command->argv[i];
        int         needs_quote;

        if (i > 0) {
            venv_buf_push(&out, ' ');
        }
        needs_quote = (arg[0] == '\0' || strpbrk(arg, " \t") != NULL);
        if (needs_quote) {
            venv_buf_push(&out, '"');
        }
        /* Escape embedded double-quotes. */
        for (j = 0; arg[j]; ++j) {
            if (arg[j] == '"') {
                venv_buf_push(&out, '\\');
            }
            venv_buf_push(&out, arg[j]);
        }
        if (needs_quote) {
            venv_buf_push(&out, '"');
        }
    }
    return venv_buf_release(&out);
}

/* Job object that keeps the child (and anything it starts) bounded. */
static HANDLE create_job(char *err, size_t errlen)
{
    HANDLE                               job;
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli;
    char                                *message;

    job = CreateJobObjectA(NULL, NULL);
    if (!job) {
        message = last_error_str();
        venv_set_error(err, errlen, "CreateJobObject failed: %s", message);
        free(message);
        return NULL;
    }

    memset(&jeli, 0, sizeof(jeli));
    jeli.BasicLimitInformation.LimitFlags =
        JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE |
        JOB_OBJECT_LIMIT_DIE_ON_UNHANDLED_EXCEPTION;
    if (!SetInformationJobObject(job, JobObjectExtendedLimitInformation, &jeli,
                                 sizeof(jeli))) {
        message = last_error_str();
        CloseHandle(job);
        venv_set_error(err, errlen, "SetInformationJobObject failed: %s",
                       message);
        free(message);
        return NULL;
    }
    return job;
}

/* ── Main implementation ────────────────────────────────────────────────── */

int venv_process_spawner_run(const venv_config *cfg,
                             const venv_command *command, int *exit_code,
                             char *err, size_t errlen)
{
    /* On Windows there is no true chroot syscall.
     * We emulate an isolated root by:
     *   1. Launching the child with CreateProcess, setting its working
     *      directory to cfg->root_dir (the child's "virtual /").
     *   2. Placing the child inside a Job Object so it stays bounded.
     *   3. Passing a custom environment block.
     *
     * Note: full filesystem isolation comparable to chroot requires either
     *   - Windows Sandbox / Hyper-V containers (heavy-weight), or
     *   - symbolic-link tricks with SeCreateSymbolicLinkPrivilege.
     * This implementation provides the working-directory pivot and env
     * isolation that is achievable without a hypervisor. */

    HANDLE              hJob;
    char               *env_block = NULL;
    char               *cmdline;
    STARTUPINFOA        si;
    PROCESS_INFORMATION pi;
    DWORD               code = 0;
    BOOL                ok;
    char               *message;

    hJob = create_job(err, errlen);
    if (!hJob) {
        return -1;
    }

    if (cfg->env_count > 0) {
        env_block = build_env_block(cfg);
    }

    /* CreateProcessA requires a mutable buffer for lpCommandLine. */
    cmdline = build_cmdline(command);

    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    memset(&pi, 0, sizeof(pi));

    /* The child writes to our own stdout/stderr, so what it prints lands in the
     * terminal that ran venv, interleaved with our own progress lines —
     * the same as the persistent-shell path, which relays the shell's output.
     * (CREATE_NEW_CONSOLE would open a separate window that closes with the
     * child, making a command like `cmake --help` look as if it never ran.) */
    {
        HANDLE h_in  = GetStdHandle(STD_INPUT_HANDLE);
        HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE h_err = GetStdHandle(STD_ERROR_HANDLE);

        /* When all three are real (the normal console or redirected case) hand
         * them over explicitly; otherwise leave STARTUPINFO alone and let the
         * child inherit whatever we have. */
        if (h_in && h_in != INVALID_HANDLE_VALUE && h_out &&
            h_out != INVALID_HANDLE_VALUE && h_err &&
            h_err != INVALID_HANDLE_VALUE) {
            si.dwFlags    = STARTF_USESTDHANDLES;
            si.hStdInput  = h_in;
            si.hStdOutput = h_out;
            si.hStdError  = h_err;
        }
    }

    /* Our progress line has to be on the wire before the child starts writing
     * to the same handle, or the two interleave in the wrong order. */
    fflush(stdout);
    fflush(stderr);

    ok = CreateProcessA(
        NULL,                 /* application name (from command line) */
        cmdline,              /* mutable command line */
        NULL,                 /* process security attributes */
        NULL,                 /* thread security attributes */
        TRUE,                 /* inherit handles: the std handles above */
        CREATE_SUSPENDED,     /* start suspended so we can add to the job */
        env_block,            /* environment block (NULL = inherit) */
        cfg->root_dir,        /* working directory = virtual root */
        &si, &pi);

    if (!ok) {
        message = last_error_str();
        CloseHandle(hJob);
        venv_set_error(err, errlen, "CreateProcess('%s') failed: %s", cmdline,
                       message);
        free(message);
        free(cmdline);
        free(env_block);
        return -1;
    }

    /* ── Assign child to job, then let it run ───────────────────────────── */
    if (!AssignProcessToJobObject(hJob, pi.hProcess)) {
        /* Non-fatal on older Windows where a process can only be in one job. */
        message = last_error_str();
        fprintf(stderr, "[warn] AssignProcessToJobObject failed: %s\n",
                message);
        free(message);
    }
    ResumeThread(pi.hThread);

    /* ── Wait for child and collect exit code ───────────────────────────── */
    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &code);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    CloseHandle(hJob);

    free(cmdline);
    free(env_block);

    *exit_code = (int)code;
    return 0;
}

/* ── Capturing a command's output ───────────────────────────────────────── */

/* The command interpreter to run `cmd /s /c <line>` with. */
static const char *comspec_of(const venv_config *cfg)
{
    const char *spec = venv_config_get_env(cfg, "COMSPEC");

    if (!spec || spec[0] == '\0') {
        spec = getenv("COMSPEC");
    }
    if (!spec || spec[0] == '\0') {
        spec = "cmd.exe";
    }
    return spec;
}

int venv_process_spawner_capture(const venv_config *cfg,
                                 const char *command_line, char **out_text,
                                 size_t *out_len, int *exit_code, char *err,
                                 size_t errlen)
{
    HANDLE              hJob;
    HANDLE              read_end  = NULL;
    HANDLE              write_end = NULL;
    SECURITY_ATTRIBUTES sa;
    STARTUPINFOA        si;
    PROCESS_INFORMATION pi;
    venv_buf            out;
    venv_buf            line;
    char               *env_block = NULL;
    char               *cmdline;
    char               *message;
    DWORD               code = 0;

    hJob = create_job(err, errlen);
    if (!hJob) {
        return -1;
    }

    memset(&sa, 0, sizeof(sa));
    sa.nLength        = sizeof(sa);
    sa.bInheritHandle = TRUE;
    if (!CreatePipe(&read_end, &write_end, &sa, 0)) {
        message = last_error_str();
        CloseHandle(hJob);
        venv_set_error(err, errlen, "CreatePipe failed: %s", message);
        free(message);
        return -1;
    }
    /* Only the child gets the write end; our read end must not leak into it,
     * or the pipe never reports EOF. */
    SetHandleInformation(read_end, HANDLE_FLAG_INHERIT, 0);

    /* `cmd /s /c "<line>"` hands the text over verbatim after stripping the
     * outer quotes, so an embedded `call "C:\...\vcvars64.bat" & SET`
     * survives with its own quoting intact. */
    venv_buf_init(&line);
    venv_buf_push(&line, '"');
    venv_buf_append_str(&line, comspec_of(cfg));
    venv_buf_append_str(&line, "\" /s /c \"");
    venv_buf_append_str(&line, command_line);
    venv_buf_append_str(&line, "\"");
    cmdline = venv_buf_release(&line);

    if (cfg->env_count > 0) {
        env_block = build_env_block(cfg);
    }

    memset(&si, 0, sizeof(si));
    si.cb         = sizeof(si);
    si.dwFlags    = STARTF_USESTDHANDLES;
    si.hStdInput  = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = write_end;
    si.hStdError  = GetStdHandle(STD_ERROR_HANDLE);
    if (si.hStdError == INVALID_HANDLE_VALUE) {
        si.hStdError = write_end;
    }
    memset(&pi, 0, sizeof(pi));

    fflush(stdout);
    fflush(stderr);

    if (!CreateProcessA(NULL, cmdline, NULL, NULL, TRUE, CREATE_SUSPENDED,
                        env_block, cfg->root_dir, &si, &pi)) {
        message = last_error_str();
        CloseHandle(read_end);
        CloseHandle(write_end);
        CloseHandle(hJob);
        venv_set_error(err, errlen, "CreateProcess('%s') failed: %s", cmdline,
                       message);
        free(message);
        free(cmdline);
        free(env_block);
        return -1;
    }

    if (!AssignProcessToJobObject(hJob, pi.hProcess)) {
        message = last_error_str();
        fprintf(stderr, "[warn] AssignProcessToJobObject failed: %s\n",
                message);
        free(message);
    }
    ResumeThread(pi.hThread);

    /* The child owns the write end now; drop ours so the read below sees EOF
     * when the child exits. */
    CloseHandle(write_end);

    venv_buf_init(&out);
    for (;;) {
        char  chunk[4096];
        DWORD got = 0;

        if (!ReadFile(read_end, chunk, sizeof(chunk), &got, NULL) || got == 0) {
            break; /* ERROR_BROKEN_PIPE = the child closed its stdout */
        }
        venv_buf_append(&out, chunk, (size_t)got);
    }
    CloseHandle(read_end);

    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &code);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    CloseHandle(hJob);
    free(cmdline);
    free(env_block);

    if (out_len) {
        *out_len = out.len;
    }
    *out_text  = venv_buf_release(&out);
    *exit_code = (int)code;
    return 0;
}

/* ── Persistent shell session ───────────────────────────────────────────── */

struct venv_shell {
    HANDLE   job;
    HANDLE   process;
    HANDLE   thread;
    HANDLE   stdin_write;   /* we write commands here */
    HANDLE   out_read;      /* the shell's stdout + stderr arrive here */
    int      dead;
    int      at_line_start; /* the last byte forwarded was a newline */
    venv_buf pending;       /* shell output read but not yet forwarded */
};

static int shell_write(venv_shell *shell, const char *text)
{
    size_t len     = strlen(text);
    size_t written = 0;

    while (written < len) {
        DWORD done = 0;
        if (!WriteFile(shell->stdin_write, text + written,
                       (DWORD)(len - written), &done, NULL) || done == 0) {
            return -1;
        }
        written += done;
    }
    return 0;
}

/* Remove `count` bytes from the front of the buffer without printing them. */
static void shell_drop(venv_shell *shell, size_t count)
{
    if (count == 0) {
        return;
    }
    memmove(shell->pending.data, shell->pending.data + count,
            shell->pending.len - count);
    shell->pending.len -= count;
}

/* Forward `count` bytes of buffered shell output to our stdout and drop them
 * from the buffer. */
static void shell_emit(venv_shell *shell, size_t count)
{
    if (count == 0) {
        return;
    }
    fwrite(shell->pending.data, 1, count, stdout);
    fflush(stdout);
    shell->at_line_start = (shell->pending.data[count - 1] == '\n');
    shell_drop(shell, count);
}

/* Finish a half-written line, so venv's own progress messages always
 * start in the first column instead of being appended to command output that
 * ended without a newline. */
static void shell_end_line(venv_shell *shell)
{
    if (!shell->at_line_start) {
        fputc('\n', stdout);
        fflush(stdout);
        shell->at_line_start = 1;
    }
}

/* Look for the status line of the command that is currently running: the
 * marker, a decimal number and the end of the line.
 *
 * Returns 1 when one was found; `*start` is then the offset of the marker and
 * `*end` the offset just past the terminating newline, so the bytes in front
 * of `*start` are the command's output. Returns 0 while the status is still
 * outstanding.
 *
 * An occurrence that is not followed by a number is not a status line but the
 * shell repeating the probe back at us, so it is left in the stream as
 * ordinary output; taking it for a status would report a wrong exit code and
 * shift every following command's output one command too late. */
static int shell_find_status(const venv_shell *shell, size_t *start,
                             size_t *end, int *exit_code)
{
    const char  *data       = shell->pending.data;
    const size_t len        = shell->pending.len;
    const size_t marker_len = sizeof(kStatusMarker) - 1;
    size_t       i;

    for (i = 0; i + marker_len <= len; ++i) {
        char   number[32];
        size_t number_start;
        size_t number_len;
        size_t digits = 0;
        size_t j;

        if (memcmp(data + i, kStatusMarker, marker_len) != 0) {
            continue;
        }

        j            = i + marker_len;
        number_start = j;
        if (j < len && (data[j] == '-' || data[j] == '+')) {
            ++j;
        }
        while (j < len && data[j] >= '0' && data[j] <= '9') {
            ++j;
            ++digits;
        }
        number_len = j - number_start;

        if (digits == 0) {
            /* No number: an echo of the probe line, or plain output that
             * happens to contain the marker. */
            continue;
        }

        if (j < len && data[j] == '\r') {
            ++j;
        }
        if (j >= len) {
            /* The line is still arriving; wait for the rest of it. */
            return 0;
        }
        if (data[j] != '\n') {
            continue;
        }

        if (number_len >= sizeof(number)) {
            number_len = sizeof(number) - 1;
        }
        memcpy(number, data + number_start, number_len);
        number[number_len] = '\0';

        *exit_code = (int)strtol(number, NULL, 10);
        *start     = i;
        *end       = j + 1;
        return 1;
    }
    return 0;
}

static size_t shell_last_newline(const venv_shell *shell, size_t limit)
{
    size_t i = limit;

    while (i > 0) {
        --i;
        if (shell->pending.data[i] == '\n') {
            return i + 1; /* number of bytes up to and including the newline */
        }
    }
    return 0;
}

/* Read one chunk of shell output into the buffer. Returns 0 on success and 1
 * when the shell closed its output, i.e. terminated. */
static int shell_fill(venv_shell *shell)
{
    char  chunk[4096];
    DWORD got = 0;

    if (!ReadFile(shell->out_read, chunk, sizeof(chunk), &got, NULL) ||
        got == 0) {
        return 1;
    }
    venv_buf_append(&shell->pending, chunk, (size_t)got);
    return 0;
}

/* Forward the shell's output until the status line of the command it is
 * running shows up, and swallow that line. */
static int shell_wait_status(venv_shell *shell, int *exit_code)
{
    for (;;) {
        size_t start = 0;
        size_t end   = 0;

        if (shell_find_status(shell, &start, &end, exit_code)) {
            shell_emit(shell, start);         /* everything the command wrote */
            shell_drop(shell, end - start);   /* the status line itself */
            shell_end_line(shell);
            return 0;
        }

        /* Pass on every line that is complete; an unfinished one may still
         * turn out to be the status line. */
        shell_emit(shell, shell_last_newline(shell, shell->pending.len));

        if (shell_fill(shell) != 0) {
            /* The shell closed its output: it has terminated, e.g. because a
             * command called `exit`. Its status becomes the command's. */
            DWORD code = 0;

            shell_emit(shell, shell->pending.len);
            shell_end_line(shell);
            shell->dead = 1;
            WaitForSingleObject(shell->process, INFINITE);
            GetExitCodeProcess(shell->process, &code);
            *exit_code = (int)code;
            return 0;
        }
    }
}

/* Send the probe that makes the shell report the status of whatever it did
 * last. `@` keeps the probe out of the output even with echo on, and
 * %ERRORLEVEL% is expanded when cmd reads the line, i.e. after the command
 * before it has finished. */
static void shell_append_probe(venv_buf *message)
{
    venv_buf_append_str(message, "@echo ");
    venv_buf_append_str(message, kStatusMarker);
    venv_buf_append_str(message, "%ERRORLEVEL%\r\n");
}

/* Last component of a Windows path. */
static const char *path_basename(const char *path)
{
    const char *base = path;
    const char *p;

    for (p = path; *p; ++p) {
        if (*p == '\\' || *p == '/' || *p == ':') {
            base = p + 1;
        }
    }
    return base;
}

/* Command line for the shell process.
 *
 * cmd.exe gets `/Q`, which stops it from echoing the lines it reads from the
 * pipe. Without it every command — the status probe included — would appear in
 * the output a second time, and the echoed probe line would be mistaken for
 * the status of the command that has not even run yet. Other shells are
 * started unchanged, because the switch means nothing to them. */
static char *build_shell_cmdline(const char *shell_path)
{
    const char *base  = path_basename(shell_path);
    const int   quote = strpbrk(shell_path, " \t") != NULL;
    venv_buf    out;

    venv_buf_init(&out);
    if (quote) {
        venv_buf_push(&out, '"');
    }
    venv_buf_append_str(&out, shell_path);
    if (quote) {
        venv_buf_push(&out, '"');
    }
    if (venv_iequals(base, "cmd.exe") || venv_iequals(base, "cmd")) {
        venv_buf_append_str(&out, " /Q");
    }
    return venv_buf_release(&out);
}

int venv_shell_open(const venv_config *cfg, const char *shell_path,
                    venv_shell **out, char *err, size_t errlen)
{
    SECURITY_ATTRIBUTES sa;
    STARTUPINFOA        si;
    PROCESS_INFORMATION pi;
    venv_shell         *shell;
    HANDLE              job        = NULL;
    HANDLE              in_read    = NULL;
    HANDLE              in_write   = NULL;
    HANDLE              out_read   = NULL;
    HANDLE              out_write  = NULL;
    char               *env_block  = NULL;
    char               *cmdline    = NULL;
    char               *text;
    char               *message;
    int                 startup_code = 0;

    *out = NULL;

    job = create_job(err, errlen);
    if (!job) {
        return -1;
    }

    memset(&sa, 0, sizeof(sa));
    sa.nLength              = sizeof(sa);
    sa.bInheritHandle       = TRUE;
    sa.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&in_read, &in_write, &sa, 0) ||
        !CreatePipe(&out_read, &out_write, &sa, 0)) {
        message = last_error_str();
        venv_set_error(err, errlen, "CreatePipe failed: %s", message);
        free(message);
        goto fail;
    }
    /* Our own ends must not leak into the shell. */
    SetHandleInformation(in_write, HANDLE_FLAG_INHERIT, 0);
    SetHandleInformation(out_read, HANDLE_FLAG_INHERIT, 0);

    if (cfg->env_count > 0) {
        env_block = build_env_block(cfg);
    }

    cmdline = build_shell_cmdline(shell_path);

    memset(&si, 0, sizeof(si));
    si.cb         = sizeof(si);
    si.dwFlags    = STARTF_USESTDHANDLES;
    si.hStdInput  = in_read;
    si.hStdOutput = out_write;
    si.hStdError  = out_write;
    memset(&pi, 0, sizeof(pi));

    if (!CreateProcessA(NULL, cmdline, NULL, NULL,
                        TRUE, /* the shell inherits the pipe ends */
                        CREATE_SUSPENDED | CREATE_NO_WINDOW, env_block,
                        cfg->root_dir, &si, &pi)) {
        message = last_error_str();
        venv_set_error(err, errlen, "CreateProcess('%s') failed: %s", cmdline,
                       message);
        free(message);
        goto fail;
    }

    if (!AssignProcessToJobObject(job, pi.hProcess)) {
        message = last_error_str();
        fprintf(stderr, "[warn] AssignProcessToJobObject failed: %s\n",
                message);
        free(message);
    }
    ResumeThread(pi.hThread);

    /* The shell owns these ends now. */
    CloseHandle(in_read);
    CloseHandle(out_write);
    free(cmdline);
    free(env_block);

    shell                = (venv_shell *)venv_xmalloc(sizeof(*shell));
    shell->job           = job;
    shell->process       = pi.hProcess;
    shell->thread        = pi.hThread;
    shell->stdin_write   = in_write;
    shell->out_read      = out_read;
    shell->dead          = 0;
    shell->at_line_start = 1;
    venv_buf_init(&shell->pending);

    /* Quiet cmd.exe down. `echo off` also stops it from printing a prompt in
     * front of every command's output; `/Q` on the command line above is what
     * silences the echo of the input lines themselves — one does not imply the
     * other. */
    {
        venv_buf startup;

        venv_buf_init(&startup);
        venv_buf_append_str(&startup, "@echo off\r\n");
        /* A probe on its own: waiting for its status drains everything the
         * shell prints while starting up — the cmd.exe banner and its first
         * prompt — so that greeting appears here, before the first command is
         * announced, instead of in the middle of that command's output. */
        shell_append_probe(&startup);
        text = venv_buf_release(&startup);

        fflush(stdout);
        if (shell_write(shell, text) != 0) {
            free(text);
            venv_set_error(err, errlen, "the shell exited immediately");
            venv_shell_close(shell);
            return -1;
        }
        free(text);
    }

    shell_wait_status(shell, &startup_code);
    if (shell->dead) {
        venv_set_error(err, errlen,
                       "the shell exited immediately, with code %d",
                       startup_code);
        venv_shell_close(shell);
        return -1;
    }

    *out = shell;
    return 0;

fail:
    if (in_read) {
        CloseHandle(in_read);
    }
    if (in_write) {
        CloseHandle(in_write);
    }
    if (out_read) {
        CloseHandle(out_read);
    }
    if (out_write) {
        CloseHandle(out_write);
    }
    if (job) {
        CloseHandle(job);
    }
    free(cmdline);
    free(env_block);
    return -1;
}

int venv_shell_run(venv_shell *shell, const char *command_line, int *exit_code,
                   char *err, size_t errlen)
{
    venv_buf message;
    char    *text;
    int      rc;

    if (shell->dead) {
        venv_set_error(err, errlen,
                       "the shell exited before this command could run");
        return -1;
    }

    /* One command, then the probe reporting its status. */
    venv_buf_init(&message);
    venv_buf_append_str(&message, command_line);
    venv_buf_append_str(&message, "\r\n");
    shell_append_probe(&message);
    text = venv_buf_release(&message);

    fflush(stdout);
    rc = shell_write(shell, text);
    free(text);
    if (rc != 0) {
        shell->dead = 1;
        WaitForSingleObject(shell->process, INFINITE);
        venv_set_error(err, errlen, "the shell is no longer running");
        return -1;
    }

    /* Forward everything the shell prints until the status line shows up, so
     * the command's output is on the terminal before its exit code is
     * reported. */
    return shell_wait_status(shell, exit_code);
}

/* Offset of the byte just past `needle` and its trailing newline within the
 * pending buffer, or (size_t)-1 when the marker line has not fully arrived. */
static size_t shell_marker_line_end(const venv_shell *shell, const char *needle,
                                    size_t *marker_start)
{
    const char  *data = shell->pending.data;
    const size_t len  = shell->pending.len;
    const size_t nlen = strlen(needle);
    size_t       i;

    for (i = 0; i + nlen <= len; ++i) {
        if (memcmp(data + i, needle, nlen) == 0) {
            size_t j = i + nlen;
            while (j < len && data[j] != '\n') {
                ++j;
            }
            if (j >= len) {
                return (size_t)-1; /* rest of the line still coming */
            }
            if (marker_start) {
                *marker_start = i;
            }
            return j + 1;
        }
    }
    return (size_t)-1;
}

int venv_shell_dump_env(venv_shell *shell, char ***out_kv, size_t *out_count,
                        char *err, size_t errlen)
{
    venv_buf collected;
    int      in_block = 0;

    *out_kv    = NULL;
    *out_count = 0;

    if (shell->dead) {
        venv_set_error(err, errlen, "the shell has already exited");
        return -1;
    }

    if (shell_write(shell,
                    "@echo " VENV_ENV_BEGIN "\r\nset\r\n@echo " VENV_ENV_END
                    "\r\n") != 0) {
        shell->dead = 1;
        WaitForSingleObject(shell->process, INFINITE);
        venv_set_error(err, errlen, "the shell is no longer running");
        return -1;
    }

    venv_buf_init(&collected);
    for (;;) {
        size_t marker_start = 0;
        size_t line_end;

        if (!in_block) {
            line_end = shell_marker_line_end(shell, VENV_ENV_BEGIN,
                                             &marker_start);
            if (line_end != (size_t)-1) {
                shell_emit(shell, marker_start); /* prior command output */
                shell_drop(shell, line_end - marker_start);
                in_block = 1;
                continue;
            }
        } else {
            line_end = shell_marker_line_end(shell, VENV_ENV_END,
                                             &marker_start);
            if (line_end != (size_t)-1) {
                venv_buf_append(&collected, shell->pending.data, marker_start);
                shell_drop(shell, line_end);
                break;
            }
            /* Everything up to the last newline is real `set` output. */
            {
                size_t safe = shell_last_newline(shell, shell->pending.len);
                venv_buf_append(&collected, shell->pending.data, safe);
                shell_drop(shell, safe);
            }
        }

        if (shell_fill(shell) != 0) {
            venv_buf_free(&collected);
            shell->dead = 1;
            WaitForSingleObject(shell->process, INFINITE);
            venv_set_error(err, errlen,
                           "the shell closed while dumping its environment");
            return -1;
        }
    }

    {
        size_t total = collected.len;
        char  *text  = venv_buf_release(&collected);
        *out_kv      = split_env_lines(text, total, out_count);
        free(text);
    }
    return 0;
}

void venv_shell_close(venv_shell *shell)
{
    if (!shell) {
        return;
    }
    if (shell->stdin_write) {
        CloseHandle(shell->stdin_write); /* EOF makes the shell exit */
        shell->stdin_write = NULL;
    }
    if (shell->out_read) {
        /* Whatever the shell still had to say belongs on the terminal too, and
         * reading the pipe empty is also what keeps the shell from blocking on
         * a full one while we wait for it to exit. */
        while (shell_fill(shell) == 0) {
            shell_emit(shell, shell_last_newline(shell, shell->pending.len));
        }
        shell_emit(shell, shell->pending.len);
        shell_end_line(shell);
        CloseHandle(shell->out_read);
        shell->out_read = NULL;
    }
    if (!shell->dead) {
        WaitForSingleObject(shell->process, INFINITE);
        shell->dead = 1;
    }
    CloseHandle(shell->thread);
    CloseHandle(shell->process);
    CloseHandle(shell->job);
    venv_buf_free(&shell->pending);
    free(shell);
}

/* ═════════════════════════════════════════════════════════════════════════
 *  Unsupported platform
 * ═════════════════════════════════════════════════════════════════════════ */
#else
#error "Unsupported platform: define PLATFORM_LINUX or PLATFORM_WINDOWS"
#endif
