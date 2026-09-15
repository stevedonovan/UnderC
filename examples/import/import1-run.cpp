#include <stdio.h>
#include "import1.h"

int main()
{
    int integer_sum = add(19, 23);
    double real_sum = sum(1.25, 2.5);
    printf("add=%d sum-ok=%d\n", integer_sum, real_sum == 3.75);
    return integer_sum == 42 && real_sum == 3.75 ? 0 : 1;
}
