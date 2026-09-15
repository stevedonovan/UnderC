struct V {
  int *b;
  int cap;
  V() { b=0; cap=10; }
};
int main() { V v; printf("ctor=%d,%p\n",v.cap,v.b); return 0; }
