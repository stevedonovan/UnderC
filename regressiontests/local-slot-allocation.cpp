// Locals are addressed in whole VM words, but the frame cursor used to advance
// by the raw byte size of each variable, so anything narrower than a word left
// the cursor mid-word and the next declaration truncated back on top of it.
// On a 64-bit build that made "int p; int q;" a single variable, and put the
// scalar declared after an array on top of the array's first element.
int scalars() {
  int p;
  int q;
  p = 5;
  q = 6;
  if (p != 5) return 1;

  char a;
  char b;
  a = 'A';
  b = 'B';
  if (a != 'A') return 2;

  short s;
  short t;
  s = 11;
  t = 22;
  if (s != 11) return 3;
  return 0;
}

int array_then_scalar() {
  int a[3];
  int i;
  a[0] = 2; a[1] = 4; a[2] = 6;
  for (i = 0; i < 3; i++)
    if (a[i] != 2*(i+1)) return 10 + i;
  if (i != 3) return 20;
  if (a[0] != 2) return 21;   // the loop counter used to live in a[0]
  return 0;
}

int main() {
  int r;
  r = scalars();
  if (r) { printf("scalars failed %d\n", r); return r; }
  r = array_then_scalar();
  if (r) { printf("array_then_scalar failed %d\n", r); return r; }
  printf("local-slot-allocation-ok\n");
  return 0;
}
