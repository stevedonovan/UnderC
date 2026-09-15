#ifndef __DIRECT_H
#define __DIRECT_H
const int _MAX_PATH=256;
#lib msvcrt.dll
extern "C" {
  char* _getcwd(char* buff, int sz);
}
#lib
#endif
