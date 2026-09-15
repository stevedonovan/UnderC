#include <map>
#include <string>
using std::map;
using std::string;
int main() {
  map<string,int> m;
  m["one"]++;
  m["two"] += 2;
  map<string,int>::iterator i = m.find("two");
  printf("map=%d\n",i->second);
  return 0;
}
