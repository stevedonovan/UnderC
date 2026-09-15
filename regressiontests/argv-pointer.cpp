#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2) return 1;
    printf("argument=%s\n", argv[1]);
    return argv[1][0] == 'o' ? 0 : 2;
}
