#include <vector>
using std::vector;
int main() {
  vector<int> v;
  printf("made size=%d cap=%d begin=%p end=%p\n",v.size(),v.capacity(),v.begin(),v.end());
  int raw[] = {7,8};
  v.assign(raw,raw+2);
  printf("assigned=%d begin=%p end=%p\n",v[1],v.begin(),v.end());
  return 0;
}
