#include <vector>
using std::vector;
int main() {
  vector<int> v(0);
  int raw[] = {7,8};
  v.assign(raw,raw+2);
  printf("using=%d\n",v[1]);
  return 0;
}
