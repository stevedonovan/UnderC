template <class T,int N> struct Arr {
  T m_arr[N];
  template <class IT> void assign(IT s, IT e) {
    int i = 0;
    for (; s != e; ++s) m_arr[i++] = *s;
  }
};
int main() {
  int raw[] = {1,2,3};
  Arr<int,3> a;
  a.assign(raw,raw+3);
  printf("member-template=%d\n",a.m_arr[2]);
  return 0;
}
