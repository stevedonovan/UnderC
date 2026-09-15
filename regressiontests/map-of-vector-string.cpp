// The combination that blocked venv_spawner's parseEnvironment(): a
// map<string, vector<string> > built up in a function and returned by value.
// It needed the array constructor fix (for the vectors' string elements) and
// the map copy constructor together.  Note the space in "> >" - ">>" is still
// a syntax error to this parser.
#include <map>
#include <vector>
#include <string>
using std::map;
using std::vector;
using std::string;

map<string, vector<string> > parse() {
  map<string, vector<string> > env;
  env["PATH"].push_back("/usr/bin");
  env["PATH"].push_back("/usr/local/bin");
  env["PATH"].push_back("/opt/bin");
  env["HOME"].push_back("/home/me");
  env["LIB"].push_back("a");
  env["LIB"].push_back("b");
  return env;
}

int main() {
  map<string, vector<string> > e = parse();
  int total;
  if (e.size() != 3) { printf("keys=%d\n", e.size()); return 1; }
  if (e["PATH"].size() != 3) return 2;
  if (e["HOME"].size() != 1) return 3;
  if (e["LIB"].size() != 2) return 4;
  if (strcmp(e["PATH"][0].c_str(), "/usr/bin")) return 5;
  if (strcmp(e["PATH"][2].c_str(), "/opt/bin")) return 6;
  if (strcmp(e["LIB"][1].c_str(), "b")) return 7;

  total = 0;
  map<string, vector<string> >::iterator it;
  for (it = e.begin(); it != e.end(); ++it)
    total += it->second.size();
  if (total != 6) { printf("total=%d\n", total); return 8; }

  printf("map-of-vector-string-ok\n");
  return 0;
}
