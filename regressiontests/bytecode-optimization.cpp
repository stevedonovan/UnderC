#include <stdio.h>

int folded()
{
    return (6 * 7) + (10 - 3);
}

int identity(int value)
{
    return ((value + 0) * 1) << 0;
}

int main()
{
    int value = folded() + identity(5);
    printf("optimized=%d\n", value);
    return value == 54 ? 0 : 1;
}
