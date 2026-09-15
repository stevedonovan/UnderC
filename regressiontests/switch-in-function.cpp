#include <stdio.h>

int choose(int value)
{
    switch (value) {
    case 1: return 11;
    case 2: return 22;
    default: return 0;
    }
}

int main()
{
    printf("switch=%d\n", choose(2));
    return choose(2) == 22 ? 0 : 1;
}
