#include "config.h"

#include "cmdline.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#if defined(PLATFORM_WINDOWS)
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#  include <windows.h>
#  include <direct.h>
#  define venv_getcwd _getcwd
#  define venv_environ _environ
#else
#  include <dirent.h>
#  include <unistd.h>
#  define venv_getcwd getcwd
extern char **environ;
#  define venv_environ environ
#endif

#ifndef S_ISDIR
#  define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#endif

/* ── Filesystem helpers ─────────────────────────────────────────────────── */

static int path_exists(const char *path, int *is_dir)
{
    struct stat st;

    if (stat(path, &st) != 0) {
        return 0;
    }
    if (is_dir) {
        *is_dir = S_ISDIR(st.st_mode) ? 1 : 0;
    }
    return 1;
}

static char *join_path(const char *dir, const char *name)
{
    venv_buf b;

    venv_buf_init(&b);
    venv_buf_append_str(&b, dir);
#if defined(PLATFORM_WINDOWS)
    if (b.len > 0 && b.data[b.len - 1] != '\\' && b.data[b.len - 1] != '/') {
        venv_buf_push(&b, '\\');
    }
#else
    if (b.len > 0 && b.data[b.len - 1] != '/') {
        venv_buf_push(&b, '/');
    }
#endif
    venv_buf_append_str(&b, name);
    return venv_buf_release(&b);
}

/* The per-user directory whose sources are auto-loaded, freshly allocated, or
 * NULL when the environment does not point at a home. */
static char *venv_source_dir(void)
{
    venv_buf out;

#if defined(PLATFORM_WINDOWS)
    const char *base = getenv("APPDATA");

    if (!base || base[0] == '\0') {
        return NULL;
    }
    venv_buf_init(&out);
    venv_buf_append_str(&out, base);
    venv_buf_append_str(&out, "\\venv");
#else
    const char *xdg  = getenv("XDG_CONFIG_HOME");
    const char *home = getenv("HOME");

    venv_buf_init(&out);
    if (xdg && xdg[0] != '\0') {
        venv_buf_append_str(&out, xdg);
        venv_buf_append_str(&out, "/venv");
    } else if (home && home[0] != '\0') {
        venv_buf_append_str(&out, home);
        venv_buf_append_str(&out, "/.config/venv");
    } else {
        venv_buf_free(&out);
        return NULL;
    }
#endif
    return venv_buf_release(&out);
}

static char *current_directory(void)
{
    size_t size = 512;

    for (;;) {
        char *buf = (char *)venv_xmalloc(size);
        if (venv_getcwd(buf, (int)size)) {
            return buf;
        }
        free(buf);
        if (size >= 65536) {
            return NULL;
        }
        size *= 2;
    }
}

/* ── Environment name matching ──────────────────────────────────────────── */

static int env_name_equals(const char *a, const char *b)
{
#if defined(PLATFORM_WINDOWS)
    return venv_iequals(a, b);
#else
    return strcmp(a, b) == 0;
#endif
}

/* ── Lifecycle ─────────────────────────────────────────────────────────── */

void venv_config_init(venv_config *cfg)
{
    memset(cfg, 0, sizeof(*cfg));
}

void venv_config_free(venv_config *cfg)
{
    size_t i;

    free(cfg->root_dir);
    for (i = 0; i < cfg->env_count; ++i) {
        free(cfg->env_vars[i].key);
        free(cfg->env_vars[i].value);
    }
    free(cfg->env_vars);
    free(cfg->venv_dir);
    venv_config_init(cfg);
}

static void seed_environment(venv_config *cfg)
{
    char **env = venv_environ;
    size_t i;

    if (!env) {
        return;
    }
    for (i = 0; env[i]; ++i) {
        const char *entry = env[i];
        const char *eq    = strchr(entry, '=');
        char       *key;

        if (!eq || eq == entry) {
            continue; /* no name, or a Windows "=C:" drive-cwd entry */
        }
        key = venv_xstrndup(entry, (size_t)(eq - entry));
        venv_config_set_env(cfg, key, eq + 1);
        free(key);
    }
}

int venv_config_prepare(venv_config *cfg, char *err, size_t errlen)
{
    seed_environment(cfg);

    cfg->venv_dir = venv_source_dir();

    cfg->root_dir = current_directory();
    if (!cfg->root_dir) {
        venv_set_error(err, errlen,
                       "the current working directory could not be determined");
        return -1;
    }
    cfg->root_dir_defaulted = 1;
    return 0;
}

int venv_config_set_root_dir(venv_config *cfg, const char *path, char *err,
                             size_t errlen)
{
    int is_dir = 0;

    if (!path || path[0] == '\0') {
        venv_set_error(err, errlen, "venvRootDir(): empty path");
        return -1;
    }
    if (!path_exists(path, &is_dir)) {
        venv_set_error(err, errlen, "venvRootDir(): does not exist: %s", path);
        return -1;
    }
    if (!is_dir) {
        venv_set_error(err, errlen, "venvRootDir(): not a directory: %s", path);
        return -1;
    }
    free(cfg->root_dir);
    cfg->root_dir           = venv_xstrdup(path);
    cfg->root_dir_defaulted = 0;
    return 0;
}

/* ── Environment editing ───────────────────────────────────────────────── */

void venv_config_set_env(venv_config *cfg, const char *key, const char *value)
{
    size_t i;

    for (i = 0; i < cfg->env_count; ++i) {
        if (env_name_equals(cfg->env_vars[i].key, key)) {
            free(cfg->env_vars[i].value);
            cfg->env_vars[i].value = venv_xstrdup(value ? value : "");
            return;
        }
    }
    cfg->env_vars = (venv_env_var *)venv_xrealloc(
        cfg->env_vars, (cfg->env_count + 1) * sizeof(*cfg->env_vars));
    cfg->env_vars[cfg->env_count].key   = venv_xstrdup(key);
    cfg->env_vars[cfg->env_count].value = venv_xstrdup(value ? value : "");
    ++cfg->env_count;
}

const char *venv_config_get_env(const venv_config *cfg, const char *key)
{
    size_t i;

    for (i = 0; i < cfg->env_count; ++i) {
        if (env_name_equals(cfg->env_vars[i].key, key)) {
            return cfg->env_vars[i].value;
        }
    }
    return NULL;
}

static void env_combine(venv_config *cfg, const char *key, const char *fragment,
                        int prepend)
{
    const char *current = venv_config_get_env(cfg, key);
    venv_buf    b;

    if (!fragment) {
        fragment = "";
    }
    if (!current) {
        venv_config_set_env(cfg, key, fragment);
        return;
    }
    venv_buf_init(&b);
    if (prepend) {
        venv_buf_append_str(&b, fragment);
        venv_buf_append_str(&b, current);
    } else {
        venv_buf_append_str(&b, current);
        venv_buf_append_str(&b, fragment);
    }
    {
        char *joined = venv_buf_release(&b);
        venv_config_set_env(cfg, key, joined);
        free(joined);
    }
}

void venv_config_prepend_env(venv_config *cfg, const char *key,
                             const char *fragment)
{
    env_combine(cfg, key, fragment, 1);
}

void venv_config_append_env(venv_config *cfg, const char *key,
                            const char *fragment)
{
    env_combine(cfg, key, fragment, 0);
}

/* ── Configuration file lookup ─────────────────────────────────────────── */

/* Does `path` say for itself where it lives? Absolute paths do, and so do the
 * explicitly current-directory-relative spellings `./x`, `.\x`, `../x`, `..\x`.
 * Everything else is a bare name that we look up in the venv directory. */
static int path_is_explicit(const char *path)
{
    if (!path || path[0] == '\0') {
        return 1;
    }
    if (path[0] == '/' || path[0] == '\\') {
        return 1; /* absolute, or a UNC / rooted Windows path */
    }
#if defined(PLATFORM_WINDOWS)
    if (path[0] != '\0' && path[1] == ':') {
        return 1; /* C:\... or C:x */
    }
#endif
    if (path[0] == '.') {
        if (path[1] == '/' || path[1] == '\\') {
            return 1;
        }
        if (path[1] == '.' && (path[2] == '/' || path[2] == '\\')) {
            return 1;
        }
    }
    return 0;
}

char *venv_config_resolve_source_path(const venv_config *cfg, const char *path)
{
    char *candidate;
    int   is_dir = 0;

    if (!path) {
        path = "";
    }
    if (path_is_explicit(path) || !cfg || !cfg->venv_dir) {
        return venv_xstrdup(path);
    }

    candidate = join_path(cfg->venv_dir, path);
    if (path_exists(candidate, &is_dir) && !is_dir) {
        return candidate;
    }
    free(candidate);
    return venv_xstrdup(path);
}

/* ── Auto-load source discovery ────────────────────────────────────────── */

static int has_source_suffix(const char *name)
{
    size_t n = strlen(name);

    if (n >= 4 && venv_iequals(name + n - 4, ".cpp")) {
        return 1;
    }
    if (n >= 2 && venv_iequals(name + n - 2, ".c")) {
        return 1;
    }
    return 0;
}

static int str_cmp_qsort(const void *a, const void *b)
{
    return strcmp(*(const char *const *)a, *(const char *const *)b);
}

char **venv_config_collect_sources(const char *dir, size_t *count)
{
    char **list = NULL;
    size_t n    = 0;
    size_t cap  = 0;

    *count = 0;
    if (!dir) {
        list = (char **)venv_xmalloc(sizeof(*list));
        list[0] = NULL;
        return list;
    }

#if defined(PLATFORM_WINDOWS)
    {
        WIN32_FIND_DATAA fd;
        HANDLE           h;
        char            *pattern = join_path(dir, "*");

        h = FindFirstFileA(pattern, &fd);
        free(pattern);
        if (h != INVALID_HANDLE_VALUE) {
            do {
                if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    continue;
                }
                if (!has_source_suffix(fd.cFileName)) {
                    continue;
                }
                if (n == cap) {
                    cap  = cap ? cap * 2 : 8;
                    list = (char **)venv_xrealloc(list,
                                                  (cap + 1) * sizeof(*list));
                }
                list[n++] = join_path(dir, fd.cFileName);
            } while (FindNextFileA(h, &fd));
            FindClose(h);
        }
    }
#else
    {
        DIR *d = opendir(dir);

        if (d) {
            struct dirent *ent;
            while ((ent = readdir(d)) != NULL) {
                if (!has_source_suffix(ent->d_name)) {
                    continue;
                }
                if (n == cap) {
                    cap  = cap ? cap * 2 : 8;
                    list = (char **)venv_xrealloc(list,
                                                  (cap + 1) * sizeof(*list));
                }
                list[n++] = join_path(dir, ent->d_name);
            }
            closedir(d);
        }
    }
#endif

    if (n == cap) {
        list = (char **)venv_xrealloc(list, (n + 1) * sizeof(*list));
    }
    if (!list) {
        list = (char **)venv_xmalloc(sizeof(*list));
    }
    if (n > 1) {
        qsort(list, n, sizeof(*list), str_cmp_qsort);
    }
    list[n] = NULL;
    *count  = n;
    return list;
}
