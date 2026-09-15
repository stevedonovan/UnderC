// map used to declare a private copy constructor and assignment operator and
// define neither, so a map could not be returned by value - the engine reported
// "is not defined yet".  Both are now deep copies of the node tree.
#include <map>
#include <string>
using std::map;
using std::string;

map<string,string> build() {
  map<string,string> m;
  m["A"] = "x";
  m["B"] = "y";
  m["C"] = "z";
  return m;
}

int main() {
  map<string,string> m = build();
  if (m.size() != 3) { printf("returned size=%d\n", m.size()); return 1; }
  if (strcmp(m["A"].c_str(),"x")) return 2;
  if (strcmp(m["C"].c_str(),"z")) return 3;

  // assignment must deep copy: touching the copy must not touch the original
  map<string,string> n;
  n = m;
  n["D"] = "w";
  if (n.size() != 4) return 4;
  if (m.size() != 3) return 5;

  // self assignment must not destroy the tree
  n = n;
  if (n.size() != 4) return 6;
  if (strcmp(n["A"].c_str(),"x")) return 7;

  if (n.count("A") != 1) return 8;
  if (n.count("ZZ") != 0) return 9;
  n.clear();
  if (! n.empty()) return 10;

  printf("map-copy-semantics-ok\n");
  return 0;
}
