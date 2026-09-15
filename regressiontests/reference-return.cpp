int value=7;
int& global_ref() { return value; }
struct Box {
  int member;
  Box() { member=11; }
  int& get() { return member; }
};
int main() {
  global_ref()=13;
  Box b; b.get()=17;
  printf("reference-return=%d,%d\n",value,b.member);
  return value==13 && b.member==17 ? 0 : 1;
}
