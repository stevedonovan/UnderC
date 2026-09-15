#include "mstring.h"
#include "utils.h"

#include <stdio.h>

int main()
{
#ifdef _WIN32
    const char *qualified_path = "directory\\module-name.cpp";
    const char *absolute_path = "C:\\source\\module-name.cpp";
#else
    const char *qualified_path = "directory/module-name.cpp";
    const char *absolute_path = "/source/module-name.cpp";
#endif

    if (Utils::get_filepart(qualified_path, false) != "module-name.cpp") return 1;
    if (Utils::get_filepart(absolute_path, true) != "module-name") return 2;
    if (Utils::get_filepart("module-name.cpp", true) != "module-name") return 3;

    printf("basename-handling-ok\n");
    return 0;
}
