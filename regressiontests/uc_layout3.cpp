struct V {
  int *b; int *e; int size; int cap;
  void init() { b=0; size=0; cap=size+10; b=new int[cap]; e=b+size; }
};
int main() { V v; v.init(); printf("layout=%d,%d,%d\n",v.size,v.cap,v.e-v.b); delete[] v.b; return 0; }
