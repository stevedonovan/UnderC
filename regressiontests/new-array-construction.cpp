// "new T[n]" used to run the constructor and destructor loops exactly once,
// whatever n was: the element count never reached the CCALLV opcode, so
// elements 1..n-1 were raw memory.  Static arrays took a different branch and
// were always correct, so they are checked here too as a guard.
int ctors;
int dtors;

struct Probe {
  int tag;
  Probe() { tag = 7; ctors++; }
  ~Probe() { dtors++; }
};

Probe g[10];

int dynamic_array(int n) {
  int i;
  ctors = 0; dtors = 0;
  Probe *p = new Probe[n];
  if (ctors != n) { printf("  n=%d ctors=%d\n", n, ctors); return 1; }
  for (i = 0; i < n; i++)
    if (p[i].tag != 7) { printf("  n=%d elem %d unconstructed\n", n, i); return 2; }
  delete[] p;
  if (dtors != n) { printf("  n=%d dtors=%d\n", n, dtors); return 3; }
  return 0;
}

int static_array() {
  int i;
  ctors = 0; dtors = 0;
  Probe a[10];
  for (i = 0; i < 10; i++)
    if (a[i].tag != 7) return 4;
  if (ctors != 10) return 5;
  return 0;
}

int main() {
  int sizes[8];
  int k;
  int r;
  sizes[0]=1; sizes[1]=2; sizes[2]=4; sizes[3]=5;
  sizes[4]=6; sizes[5]=10; sizes[6]=16; sizes[7]=100;
  for (k = 0; k < 8; k++) {
    r = dynamic_array(sizes[k]);
    if (r) { printf("new Probe[%d] failed %d\n", sizes[k], r); return r; }
  }
  r = static_array();
  if (r) { printf("static array failed %d\n", r); return r; }
  printf("new-array-construction-ok\n");
  return 0;
}
