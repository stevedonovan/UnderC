#include <stdio.h>
int first(char *s) { return s[0]; }
int main(int argc, char **argv) { printf("argc=%d arg=%s first=%d\n", argc, argv[1], first(argv[1])); return 0; }
