struct V {
  int *b; int *e; int size; int cap;
  void alloc() { int *tmp=new int[cap]; b=tmp; e=b+cap; }
  void grow() { cap=size+10; alloc(); e=b+size; }
  V(int n=0) { b=0; size=n; grow(); }
};
int main() { V v; v.b[0]=7; printf("ctor=%d,%d,%d\n",v.cap,v.b[0],v.e-v.b); delete[] v.b; return 0; }
