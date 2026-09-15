// The element count lives in a side map keyed on the pointer, so the entry has
// to be retired when the block is freed.  A stale count found again on a
// recycled address would drive the ctor/dtor loops past the end of the new
// block, so churn a lot of differently sized arrays through the allocator and
// check that every one still constructs and destroys exactly n elements.
int ctors;
int dtors;

struct P {
  int tag;
  P() { tag = 1; ctors++; }
  ~P() { dtors++; }
};

int main() {
  int i;
  int n;
  for (i = 0; i < 20000; i++) {
    n = 1 + (i % 17);
    ctors = 0; dtors = 0;
    P *p = new P[n];
    if (ctors != n) { printf("iter %d ctors=%d want %d\n", i, ctors, n); return 1; }
    if (p[n-1].tag != 1) { printf("iter %d last element unconstructed\n", i); return 2; }
    delete[] p;
    if (dtors != n) { printf("iter %d dtors=%d want %d\n", i, dtors, n); return 3; }
  }
  printf("array-allocation-churn-ok\n");
  return 0;
}
