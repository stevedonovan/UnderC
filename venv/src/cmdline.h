#ifndef VENV_CMDLINE_H
#define VENV_CMDLINE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Split a command line into argv-style tokens.
 * Whitespace separates tokens; double quotes group text containing
 * whitespace; a doubled `""` inside a quoted run yields a literal quote.
 * Backslashes are not escape characters here, so Windows paths survive intact.
 *
 * On success 0 is returned and `*out_argv` points at `*out_argc` freshly
 * allocated strings followed by a NULL terminator; free it with
 * venv_free_argv(). Returns -1 on an unterminated quote (message in `err`). */
int venv_split_command_line(const char *line, char ***out_argv, size_t *out_argc,
                            char *err, size_t errlen);

void venv_free_argv(char **argv, size_t argc);

#ifdef __cplusplus
}
#endif

#endif /* VENV_CMDLINE_H */
