struct V {
  int *b;
  int cap;
  V() { cap=10; b=new int[cap]; }
};
int main() { V v; v.b[0]=7; printf("ctor=%d,%d\n",v.cap,v.b[0]); delete[] v.b; return 0; }
