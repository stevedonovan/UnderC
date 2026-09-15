#include <stdio.h>
double twice(double x) { return x * 2.0; }
int main() { double x = twice(3.5); printf("%g\n", x); return x == 7.0 ? 0 : 1; }
