// ftw.h
#ifndef __FTW_H
#define __FTW_H
#include <sys/stat.h>

typedef int (*WALKFN)(const char *file, const stat *sb, int flag);

#include <_shared_lib.h>
extern "C" {
  int ftw(const char *dir, WALKFN fn, int depth);
}
#lib

enum {
  FTW_F,   // regular file
  FTW_D,   //  directory
  FTW_DNR, // unreadable directory
  FTW_NS,  // unstatable file
  FTW_SL   // symbolic link
}
;


#endif  
