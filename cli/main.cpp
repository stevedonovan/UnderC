#include <underc/ucdl.h>

#include <string.h>

// The UnderC library keeps no OS-specific "where am I" logic.  ucc locates its
// own runtime tree here and hands the prefix to the library through
// uc_set_home_dir().  The expected layout is a single $PREFIX with bin/,
// include/ and lib/ subdirectories, so ucc at $PREFIX/bin/ucc[.exe] finds
// $PREFIX/include/underc/uclstl and $PREFIX/lib/uclr at run time.  UC_HOME and
// the -H option still override this.
#if defined(_WIN32)
#  include <windows.h>
#elif defined(__APPLE__)
#  include <mach-o/dyld.h>
#  include <limits.h>
#else
#  include <unistd.h>
#  include <limits.h>
#endif

static void strip_trailing_component(char *path)
{
    char *last = 0;
    for (char *p = path; *p; ++p)
        if (*p == '/' || *p == '\\') last = p;
    if (last) *last = '\0';
    else path[0] = '\0';
}

static int executable_path(char *buff, size_t size)
{
#if defined(_WIN32)
    DWORD n = GetModuleFileNameA(NULL, buff, (DWORD)size);
    if (n == 0 || n >= size) return 0;
    return 1;
#elif defined(__APPLE__)
    uint32_t n = (uint32_t)size;
    if (_NSGetExecutablePath(buff, &n) != 0) return 0;
    buff[size - 1] = '\0';
    return 1;
#else
    ssize_t n = readlink("/proc/self/exe", buff, size - 1);
    if (n <= 0) return 0;
    buff[n] = '\0';
    return 1;
#endif
}

static void configure_runtime_paths()
{
    char buff[4096];
    if (!executable_path(buff, sizeof(buff))) return;
    strip_trailing_component(buff);  // drop "ucc[.exe]"  -> $PREFIX/bin
    strip_trailing_component(buff);  // drop "bin"        -> $PREFIX
    if (buff[0] != '\0')
        uc_set_home_dir(buff);
}

int main(int argc, char **argv)
{
    configure_runtime_paths();
    return uc_main(argc, argv);
}
