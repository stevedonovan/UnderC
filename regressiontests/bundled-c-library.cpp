#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <uc_except.h>

void report_exit()
{
    puts("atexit-ok");
}

int main()
{
    char buffer[64];
    char *home;
    int result;
    RangeError range;

    if (SEEK_SET != 0 || SEEK_CUR != 1 || SEEK_END != 2) return 1;
    home = getenv("UC_HOME");
    if (home == 0) return 2;
    if (system("") != 0) return 3;
    result = _access(home, 0);
    if (result != 0) return 5;
    result = strcmp(range.what(), "range check");
    if (result != 0) return 6;
    result = atexit(report_exit);
    if (result != 0) return 7;

    _gcvt(12.5, 4, buffer);
    printf("gcvt=%s bundled-c-library-ok ", buffer);
    return 0;
}
