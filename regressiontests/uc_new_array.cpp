int main() {
  int *p = new int[10];
  p[0] = 7;
  p[9] = 9;
  printf("new-array=%d,%d,diff=%d\n",p[0],p[9],p+1-p);
  delete[] p;
  return 0;
}
