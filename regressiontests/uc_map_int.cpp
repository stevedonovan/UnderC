#include <map>
using std::map;
int main() {
  map<int,int> m;
  m[1]=2;
  int value=m[1];
  printf("map-int=%d\n",value);
  return value==2 ? 0 : 1;
}
