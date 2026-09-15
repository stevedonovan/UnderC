int main() { int *p = _new_vect(10, 4); if (p == 0) return 3; p[0] = 17; return p[0] == 17 ? 0 : 4; }
