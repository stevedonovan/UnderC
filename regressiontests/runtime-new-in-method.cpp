struct Owner {
  int *member;
  int count;

  Owner() {
    count = 10;
    int *local = new int[count];
    local[0] = 17;
    member = local;
  }

  ~Owner() { delete[] member; }
};

int main() {
  Owner value;
  printf("new-in-method=%d,%d\n", value.count, value.member[0]);
  return value.count == 10 && value.member[0] == 17 ? 0 : 1;
}
