struct V {
  int x;
  V() { x=10; }
};
int main() { V v; printf("ctor=%d\n",v.x); return 0; }
