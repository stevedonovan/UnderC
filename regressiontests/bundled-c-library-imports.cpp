/* The parts of the bundled C library that are imported from the platform C
 * runtime rather than provided as interpreter built-ins.  On Windows the
 * library used to name msvcrt40.dll, which no longer exists, so every
 * declaration under it failed to link.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *block;
    char buffer[32];

    block = (char *)malloc(64);
    if (block == 0) return 1;
    strcpy(block, "hello");
    strncat(block, "-world", 32);
    if (strncmp(block, "hello-world", 11) != 0) return 2;
    if (strlen(block) != 11) return 3;
    free(block);

    if (atol("42") != 42) return 4;
    if (strtol("17", 0, 10) != 17) return 5;
    if (abs(-5) != 5) return 6;
    if (strspn("abcxyz", "abc") != 3) return 7;

    memset(buffer, 0, sizeof(buffer));
    memcpy(buffer, "copied", 7);
    if (memcmp(buffer, "copied", 6) != 0) return 8;

    printf("bundled-c-library-imports-ok\n");
    return 0;
}
