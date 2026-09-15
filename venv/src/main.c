#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmdline.h"
#include "config.h"
#include "util.h"

/* Carries VENV_DEFAULT_UCLP, which the usage text needs, and the interpreter
 * lifecycle used below. */
#include "underc_bridge.h"

static const char kUsage[] =
    "venv - virtual environment process launcher\n"
    "\n"
    "Usage:\n"
    "  venv <config.cvc> [-uclp <prefix>] [-ucll <file>]...\n"
    "                            [-ac <command>]...\n"
    "  venv --config <config.cvc> [options]...\n"
    "\n"
    "A .cvc file is C++ source run by the embedded UnderC interpreter. Its\n"
    "main() drives the run through the venv* API: venvRootDir, venvSetEnv,\n"
    "venvPreEnv, venvAppEnv, venvExeCommand, venvExeCommandString,\n"
    "venvStartShell, venvStopShell, venvSnapShotEnv, venvCompareSnapshotEnv,\n"
    "venvExecAppCommands.\n"
    "\n"
    "A <config.cvc> or -ucll <file> that is not an absolute path and does not\n"
    "start with ./ or .\\ is looked up in the per-user venv directory (the\n"
    "same place whose .c / .cpp files are auto-loaded), falling back to the\n"
    "path as written when it is not there.\n"
    "\n"
    "Options:\n"
    "  -h, --help            Show this help message\n"
    "  -c, --config <path>   Path to the .cvc configuration file\n"
    "  -uclp <prefix>        UnderC library prefix: the directory holding\n"
    "                        include/underc/uclstl (STL headers, engine\n"
    "                        resources). When omitted it is auto-detected\n"
    "                        from $UC_HOME, $DEP_DIR/underc, the directory\n"
    "                        holding venv, then " VENV_DEFAULT_UCLP "\n"
    "  -ucll <file>          Load <file> (C / C++ source) into the interpreter\n"
    "                        after the auto-loaded venv directory sources and\n"
    "                        before the configuration. May be given several\n"
    "                        times; the files are loaded in the order given.\n"
    "  -ac <command>         Append <command> to the list read back from the\n"
    "                        config via venvAppCommand*/venvExecAppCommands().\n"
    "                        May be given several times; order is preserved.\n";

typedef struct {
    const char  *config_path;
    const char  *uclp;
    const char **appends;
    size_t       append_count;
    const char **preloads;      /* -ucll, in the order given */
    size_t       preload_count;
    int          help;
} options;

static void options_free(options *opts)
{
    free((void *)opts->appends);
    opts->appends      = NULL;
    opts->append_count = 0;
    free((void *)opts->preloads);
    opts->preloads      = NULL;
    opts->preload_count = 0;
}

static void options_add_append(options *opts, const char *value)
{
    opts->appends = (const char **)venv_xrealloc(
        (void *)opts->appends, (opts->append_count + 1) * sizeof(*opts->appends));
    opts->appends[opts->append_count++] = value;
}

static void options_add_preload(options *opts, const char *value)
{
    opts->preloads = (const char **)venv_xrealloc(
        (void *)opts->preloads,
        (opts->preload_count + 1) * sizeof(*opts->preloads));
    opts->preloads[opts->preload_count++] = value;
}

static int parse_args(int argc, char *argv[], options *opts, char *err,
                      size_t errlen)
{
    int positional_seen = 0;
    int i;

    opts->config_path   = NULL;
    opts->uclp          = NULL; /* NULL => auto-detect, see venv_underc_resolve_prefix */
    opts->appends       = NULL;
    opts->append_count  = 0;
    opts->preloads      = NULL;
    opts->preload_count = 0;
    opts->help          = 0;

    for (i = 1; i < argc; ++i) {
        const char *arg = argv[i];

        if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
            opts->help = 1;
            continue;
        }
        if (strcmp(arg, "-c") == 0 || strcmp(arg, "--config") == 0) {
            if (i + 1 >= argc) {
                venv_set_error(err, errlen, "missing value for option %s", arg);
                return -1;
            }
            opts->config_path = argv[++i];
            continue;
        }
        if (strncmp(arg, "--config=", 9) == 0) {
            opts->config_path = arg + 9;
            continue;
        }
        if (strcmp(arg, "-uclp") == 0 || strcmp(arg, "--underc-prefix") == 0) {
            if (i + 1 >= argc) {
                venv_set_error(err, errlen, "missing value for option %s", arg);
                return -1;
            }
            opts->uclp = argv[++i];
            continue;
        }
        if (strncmp(arg, "-uclp=", 6) == 0) {
            opts->uclp = arg + 6;
            continue;
        }
        if (strcmp(arg, "-ucll") == 0 || strcmp(arg, "--underc-load") == 0) {
            if (i + 1 >= argc) {
                venv_set_error(err, errlen, "option %s needs a value: <file>",
                               arg);
                return -1;
            }
            options_add_preload(opts, argv[++i]);
            continue;
        }
        if (strncmp(arg, "-ucll=", 6) == 0) {
            options_add_preload(opts, arg + 6);
            continue;
        }
        if (strcmp(arg, "-ac") == 0 || strcmp(arg, "--append-command") == 0) {
            if (i + 1 >= argc) {
                venv_set_error(err, errlen,
                               "option %s needs a value: <command>", arg);
                return -1;
            }
            options_add_append(opts, argv[++i]);
            continue;
        }
        if (arg[0] == '-' && arg[1] != '\0') {
            venv_set_error(err, errlen, "unknown option: %s", arg);
            return -1;
        }
        if (positional_seen) {
            venv_set_error(err, errlen, "unexpected extra argument: %s", arg);
            return -1;
        }
        opts->config_path = arg;
        positional_seen   = 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    char        errbuf[1024];
    options     opts;
    venv_config cfg;
    char      **sources = NULL;
    size_t      source_count = 0;
    size_t      i;
    int         exit_code = 0;
    int         rc        = 0;
    char       *uclp        = NULL;
    const char *uclp_source = "";
    char       *config_path = NULL;

    errbuf[0] = '\0';
    if (parse_args(argc, argv, &opts, errbuf, sizeof(errbuf)) != 0) {
        fprintf(stderr, "Argument error: %s\n\n%s", errbuf, kUsage);
        options_free(&opts);
        return 1;
    }
    if (opts.help || !opts.config_path || opts.config_path[0] == '\0') {
        fputs(kUsage, opts.help ? stdout : stderr);
        options_free(&opts);
        return opts.help ? 0 : 1;
    }

    /* Settle the UnderC prefix first: an unusable one is fatal, and finding
     * that out only once the interpreter starts costs a silent crash. */
    if (venv_underc_resolve_prefix(opts.uclp, &uclp, &uclp_source, errbuf,
                                   sizeof(errbuf)) != 0) {
        fprintf(stderr, "venv: %s\n", errbuf);
        options_free(&opts);
        return 1;
    }

    venv_config_init(&cfg);
    if (venv_config_prepare(&cfg, errbuf, sizeof(errbuf)) != 0) {
        fprintf(stderr, "venv: %s\n", errbuf);
        venv_config_free(&cfg);
        free(uclp);
        options_free(&opts);
        return 1;
    }

    /* A bare name means "the one in the venv directory"; see
     * venv_config_resolve_source_path(). */
    config_path = venv_config_resolve_source_path(&cfg, opts.config_path);

    printf("venv: starting\n"
           "  config   : %s\n"
           "  uclp     : %s (%s)\n"
           "  env vars : %lu inherited\n",
           config_path, uclp, uclp_source, (unsigned long)cfg.env_count);
    if (cfg.venv_dir) {
        printf("  venv dir : %s\n", cfg.venv_dir);
    }
    for (i = 0; i < opts.preload_count; ++i) {
        printf("  -ucll    : %s\n", opts.preloads[i]);
    }
    for (i = 0; i < opts.append_count; ++i) {
        printf("  -ac      : %s\n", opts.appends[i]);
    }
    fflush(stdout);

    if (venv_underc_init(&cfg, uclp, (char *const *)opts.appends,
                         opts.append_count, errbuf, sizeof(errbuf)) != 0) {
        fprintf(stderr, "UnderC error: %s\n", errbuf);
        venv_underc_shutdown();
        venv_config_free(&cfg);
        free(config_path);
        free(uclp);
        options_free(&opts);
        return 1;
    }

    /* Auto-load every .c / .cpp file in the per-user venv source directory. */
    sources = venv_config_collect_sources(cfg.venv_dir, &source_count);
    for (i = 0; i < source_count && rc == 0; ++i) {
        rc = venv_underc_load_source(sources[i], errbuf, sizeof(errbuf));
    }
    venv_free_argv(sources, source_count);

    /* Then the -ucll files, in the order given: helpers the configuration is
     * about to call, so they have to be defined before it is loaded. */
    for (i = 0; i < opts.preload_count && rc == 0; ++i) {
        char *path = venv_config_resolve_source_path(&cfg, opts.preloads[i]);
        rc         = venv_underc_load_source(path, errbuf, sizeof(errbuf));
        free(path);
    }

    /* Then the configuration file itself. */
    if (rc == 0) {
        rc = venv_underc_load_source(config_path, errbuf, sizeof(errbuf));
    }
    if (rc != 0) {
        fprintf(stderr, "UnderC error: %s\n", errbuf);
        venv_underc_shutdown();
        venv_config_free(&cfg);
        free(config_path);
        free(uclp);
        options_free(&opts);
        return 1;
    }

    if (venv_underc_run_main(&exit_code, errbuf, sizeof(errbuf)) != 0) {
        fprintf(stderr, "UnderC error: %s\n", errbuf);
        venv_underc_shutdown();
        venv_config_free(&cfg);
        free(config_path);
        free(uclp);
        options_free(&opts);
        return 1;
    }

    venv_underc_shutdown();
    venv_config_free(&cfg);
    free(config_path);
    free(uclp);
    options_free(&opts);
    return exit_code;
}
