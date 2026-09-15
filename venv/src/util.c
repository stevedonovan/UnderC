#include "util.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── Allocation ─────────────────────────────────────────────────────────── */

static void out_of_memory(void)
{
    fputs("venv: out of memory\n", stderr);
    exit(1);
}

void *venv_xmalloc(size_t size)
{
    void *p = malloc(size ? size : 1);
    if (!p) {
        out_of_memory();
    }
    return p;
}

void *venv_xrealloc(void *ptr, size_t size)
{
    void *p = realloc(ptr, size ? size : 1);
    if (!p) {
        out_of_memory();
    }
    return p;
}

char *venv_xstrdup(const char *s)
{
    return venv_xstrndup(s, strlen(s));
}

char *venv_xstrndup(const char *s, size_t n)
{
    char *p = (char *)venv_xmalloc(n + 1);
    if (n) {
        memcpy(p, s, n);
    }
    p[n] = '\0';
    return p;
}

/* ── Growable buffer ────────────────────────────────────────────────────── */

void venv_buf_init(venv_buf *buf)
{
    buf->data = NULL;
    buf->len  = 0;
    buf->cap  = 0;
}

static void buf_reserve(venv_buf *buf, size_t extra)
{
    size_t needed = buf->len + extra + 1; /* +1 for the terminator */
    size_t cap;

    if (needed <= buf->cap) {
        return;
    }
    cap = buf->cap ? buf->cap : 32;
    while (cap < needed) {
        cap *= 2;
    }
    buf->data = (char *)venv_xrealloc(buf->data, cap);
    buf->cap  = cap;
}

void venv_buf_push(venv_buf *buf, char c)
{
    buf_reserve(buf, 1);
    buf->data[buf->len++] = c;
}

void venv_buf_append(venv_buf *buf, const char *data, size_t len)
{
    if (!len) {
        return;
    }
    buf_reserve(buf, len);
    memcpy(buf->data + buf->len, data, len);
    buf->len += len;
}

void venv_buf_append_str(venv_buf *buf, const char *s)
{
    venv_buf_append(buf, s, strlen(s));
}

char *venv_buf_release(venv_buf *buf)
{
    char *out;

    buf_reserve(buf, 0);
    buf->data[buf->len] = '\0';
    out = buf->data;
    venv_buf_init(buf);
    return out;
}

void venv_buf_free(venv_buf *buf)
{
    free(buf->data);
    venv_buf_init(buf);
}

/* ── String helpers ─────────────────────────────────────────────────────── */

static char lower_char(char c)
{
    return (char)tolower((unsigned char)c);
}

int venv_iequals(const char *a, const char *b)
{
    return venv_iequals_n(a, strlen(a), b);
}

int venv_iequals_n(const char *a, size_t alen, const char *b)
{
    size_t i;

    for (i = 0; i < alen; ++i) {
        if (b[i] == '\0' || lower_char(a[i]) != lower_char(b[i])) {
            return 0;
        }
    }
    return b[alen] == '\0';
}

char *venv_lower_n(const char *s, size_t n)
{
    char  *out = venv_xstrndup(s, n);
    size_t i;

    for (i = 0; i < n; ++i) {
        out[i] = lower_char(out[i]);
    }
    return out;
}

void venv_set_error(char *err, size_t errlen, const char *fmt, ...)
{
    va_list ap;

    if (!err || errlen == 0) {
        return;
    }
    va_start(ap, fmt);
    vsnprintf(err, errlen, fmt, ap);
    va_end(ap);
}
