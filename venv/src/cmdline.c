#include "cmdline.h"

#include "util.h"

#include <stdlib.h>
#include <string.h>

static int is_space(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\f' ||
           c == '\v';
}

int venv_split_command_line(const char *line, char ***out_argv, size_t *out_argc,
                            char *err, size_t errlen)
{
    char   **argv       = NULL;
    size_t   argc       = 0;
    size_t   cap        = 0;
    venv_buf token;
    int      in_quotes  = 0;
    int      have_token = 0;
    size_t   i;
    size_t   line_len   = strlen(line);

    venv_buf_init(&token);

    for (i = 0; i < line_len; ++i) {
        const char c = line[i];

        if (c == '"') {
            if (in_quotes && i + 1 < line_len && line[i + 1] == '"') {
                venv_buf_push(&token, '"'); /* "" inside quotes -> literal " */
                ++i;
            } else {
                in_quotes = !in_quotes;
            }
            have_token = 1;
            continue;
        }

        if (!in_quotes && is_space(c)) {
            if (have_token) {
                if (argc == cap) {
                    cap  = cap ? cap * 2 : 8;
                    argv = (char **)venv_xrealloc(argv,
                                                  (cap + 1) * sizeof(*argv));
                }
                argv[argc++] = venv_buf_release(&token);
                have_token   = 0;
            }
            continue;
        }

        venv_buf_push(&token, c);
        have_token = 1;
    }

    if (in_quotes) {
        venv_buf_free(&token);
        venv_free_argv(argv, argc);
        venv_set_error(err, errlen, "unterminated quote in command line: %s",
                       line);
        return -1;
    }
    if (have_token) {
        if (argc == cap) {
            cap  = cap ? cap * 2 : 8;
            argv = (char **)venv_xrealloc(argv, (cap + 1) * sizeof(*argv));
        }
        argv[argc++] = venv_buf_release(&token);
    }
    venv_buf_free(&token);

    /* Always hand back a NULL-terminated array, ready for execvp(). */
    if (argc == cap) {
        argv = (char **)venv_xrealloc(argv, (argc + 1) * sizeof(*argv));
    }
    argv[argc] = NULL;

    *out_argv = argv;
    *out_argc = argc;
    return 0;
}

void venv_free_argv(char **argv, size_t argc)
{
    size_t i;

    if (!argv) {
        return;
    }
    for (i = 0; i < argc; ++i) {
        free(argv[i]);
    }
    free(argv);
}
