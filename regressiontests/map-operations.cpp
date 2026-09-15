#include <map>
using std::map;
int main() {
  map<int,int> m;
  m.insert(2,20); m.insert(1,10); m.insert(3,30);
  if (m.size()!=3) return 1;
  printf("map-insert-destroy=ok\n");
  return 0;
}
