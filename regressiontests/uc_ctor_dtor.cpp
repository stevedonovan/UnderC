struct V {
  int *b; int cap;
  V(int n=0) { cap=10; b=new int[cap]; }
  ~V() { printf("dtor-p=%p cap=%d\n",b,cap); }
};
int main() { V v(0); return 0; }
