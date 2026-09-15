int main() {
  int a=1 | 2 & 4;
  printf("bitwise-a=%d\n",a);
  if (a!=1) return 1;
  int b=1 ^ 3 | 4;
  printf("bitwise-b=%d\n",b);
  if (b!=6) return 2;
  int c=8 | 3 ^ 1 & 7;
  printf("bitwise-c=%d\n",c);
  if (c!=10) return 3;
  return 0;
}
