#include <vector>
using std::vector;

int main() {
  vector<int> v;
  v.push_back(3); v.push_back(5);
  printf("vector-before=%d,%d,%d,%d\n",v.size(),v.capacity(),v[0],v[1]);
  v.reserve(20);
  printf("vector-state=%d,%d,%d,%d\n",v.size(),v.capacity(),v[0],v[1]);
  if (v.size()!=2) return 11;
  if (v.capacity()!=20) return 12;
  v.resize(4); v[2]=7; v[3]=9;
  v.pop_back();
  vector<int> copy(v);
  copy=copy;
  if (!(copy==v)) return 21;
  if (copy.size()!=3) return 22;
  int copied=copy[2]; if (copied!=7) return 23;
  int values[3]; values[0]=11; values[1]=13; values[2]=17;
  copy.assign(values,values+3);
  int assigned0=copy[0]; if (assigned0!=11) return 31;
  int assigned2=copy[2]; if (assigned2!=17) return 32;
  copy.assign(copy.begin(),copy.end());
  if (copy.size()!=3) return 41;
  int overlap=copy[1]; if (overlap!=13) return 42;
  copy.clear();
  if (copy.size()!=0) return 51;
  if (copy.capacity()!=0) return 52;
  if (copy.begin()!=copy.end()) return 53;
  printf("vector-operations=ok\n");
  return 0;
}
