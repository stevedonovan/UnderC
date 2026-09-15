struct V {
  int *b; int cap;
  V(int n=0) { cap=10; b=new int[cap]; }
  void clear() { printf("clear-p=%p\n",b); delete[] b; b=0; }
};
int main() { V v(0); v.clear(); return 0; }
