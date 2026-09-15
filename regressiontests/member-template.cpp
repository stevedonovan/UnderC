template <class T, int N>
struct Array {
  T values[N];
  template <class Iterator>
  void assign(Iterator first, Iterator last)
  {
    int i = 0;
    for (; first != last; ++first) values[i++] = *first;
  }
};
int main()
{
  int source[] = {1, 2, 3};
  Array<int, 3> values;
  values.assign(source, source + 3);
  printf("member-template=%d\n", values.values[2]);
  return 0;
}
