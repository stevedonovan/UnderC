struct V { int *b; int *e; int size; int cap; };
int main() {
  V v;
  v.b=0; v.size=0; v.cap=v.size+10;
  v.b=new int[v.cap]; v.e=v.b+v.size;
  printf("layout=%d,%d,%d\n",v.size,v.cap,v.e-v.b);
  delete[] v.b;
  return 0;
}
