// A vector<string> with more than one element used to corrupt the heap: the
// elements past the first were never default-constructed, so string::resize()
// ran on a garbage m_len and m_str the first time one was assigned to.
#include <vector>
#include <string>
using std::vector;
using std::string;

int grow(int n) {
  vector<string> v;
  int i;
  for (i = 0; i < n; i++) v.push_back("value");
  if (v.size() != n) return 1;
  for (i = 0; i < n; i++)
    if (strcmp(v[i].c_str(), "value") != 0) return 2;
  return 0;
}

int fresh_elements(int n) {
  string *p = new string[n];
  int i;
  // every element must already be a real, empty string - not NULL, not garbage
  for (i = 0; i < n; i++) {
    if (p[i].c_str() == NULL) return 3;
    if (p[i].length() != 0) return 4;
  }
  for (i = 0; i < n; i++) p[i] = "assigned";
  for (i = 0; i < n; i++)
    if (strcmp(p[i].c_str(), "assigned") != 0) return 5;
  delete[] p;
  return 0;
}

int main() {
  int sizes[7];
  int k;
  int r;
  sizes[0]=2; sizes[1]=4; sizes[2]=5; sizes[3]=6;
  sizes[4]=10; sizes[5]=16; sizes[6]=100;
  for (k = 0; k < 7; k++) {
    r = grow(sizes[k]);
    if (r) { printf("vector<string> n=%d failed %d\n", sizes[k], r); return r; }
    r = fresh_elements(sizes[k]);
    if (r) { printf("new string[%d] failed %d\n", sizes[k], r); return r; }
  }
  printf("vector-of-string-ok\n");
  return 0;
}
