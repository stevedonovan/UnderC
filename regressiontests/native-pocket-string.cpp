#include "../lib/string_imp.cpp"

#include <stdio.h>

int main()
{
  int (string::*compare_c_string)(const char *) const = &string::compare;
  bool (string::*equal_c_string)(const char *) const = &string::operator==;
  bool (*not_equal_c_string)(const string&, const char *) = &operator!=;

  const char *null_string = NULL;
  string empty(null_string);
  string value("pocket");

  if (!empty.c_str() || !empty.empty() || empty.c_str()[0] != '\0') return 1;
  if ((value.*compare_c_string)("pocket") != 0) return 2;
  if (!(value.*equal_c_string)("pocket")) return 3;
  if (not_equal_c_string(value, "pocket")) return 4;
  if (!not_equal_c_string(value, "string")) return 5;

  printf("native-pocket-string-ok\n");
  return 0;
}
