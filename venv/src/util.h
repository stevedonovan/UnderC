#ifndef VENV_UTIL_H
#define VENV_UTIL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Allocation wrappers. venv is a short-lived CLI tool, so an
 * out-of-memory condition is fatal: these print a message and exit(1)
 * instead of returning NULL. */
void *venv_xmalloc(size_t size);
void *venv_xrealloc(void *ptr, size_t size);
char *venv_xstrdup(const char *s);
char *venv_xstrndup(const char *s, size_t n);

/* Growable character buffer. */
typedef struct {
    char  *data;
    size_t len;
    size_t cap;
} venv_buf;

void  venv_buf_init(venv_buf *buf);
void  venv_buf_push(venv_buf *buf, char c);
void  venv_buf_append(venv_buf *buf, const char *data, size_t len);
void  venv_buf_append_str(venv_buf *buf, const char *s);
/* Hand the NUL-terminated contents to the caller (who must free them) and
 * reset the buffer. Never returns NULL, even for an empty buffer. */
char *venv_buf_release(venv_buf *buf);
void  venv_buf_free(venv_buf *buf);

/* Case-insensitive ASCII comparison; returns non-zero when equal. */
int venv_iequals(const char *a, const char *b);
/* Same, but `a` is a length-delimited slice rather than NUL-terminated. */
int venv_iequals_n(const char *a, size_t alen, const char *b);

/* Lower-cased copy of an ASCII slice. */
char *venv_lower_n(const char *s, size_t n);

/* printf-style error message into a caller-provided buffer. `err` may be
 * NULL, in which case the message is discarded. */
void venv_set_error(char *err, size_t errlen, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* VENV_UTIL_H */
