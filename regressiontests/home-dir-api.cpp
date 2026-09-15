// Verifies uc_set_home_dir(): with UC_HOME cleared from the environment, the
// runtime prefix supplied through the API is enough to locate the interpreted
// include tree (<prefix>/include/underc/uclstl) and the default prelude
// (<prefix>/lib/uclr/defs.h).  argv[1] is the prefix.
#include <underc/ucdl.h>
#include <stdio.h>
#include <stdlib.h>

static int fail(int code)
{
    char error[512] = { 0 };
    uc_error(error, sizeof(error));
    fprintf(stderr, "home-dir-api failure %d: %s\n", code, error);
    return code;
}

int main(int argc, char** argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <prefix>\n", argv[0]); return 2; }

#if defined(_WIN32)
    _putenv("UC_HOME=");
#else
    unsetenv("UC_HOME");
#endif

    uc_set_home_dir(argv[1]);
    uc_init(NULL, 1);                       // load the default prelude (defs.h)

    if (!uc_exec("string api_home = \"home-dir-api\";")) return fail(1);
    if (!uc_exec("printf(\"%s-ok\\n\", api_home.c_str());")) return fail(2);

    uc_finis();
    return 0;
}
