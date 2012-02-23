/* fnmatch.h
 */
#ifndef _FNMATCH_H
#define _FNMATCH_H

#include <_shared_lib.h>
extern "C" {  
  int fnmatch(const char *pat, const char *str, int flags);
}

enum {
  FNM_PATHNAME = 1 << 0,
  FNM_NOESCAPE = 1 << 1,
  FNM_PERIOD = 1 << 2,
  FNM_LEADING_DIR = 1 << 3,
  FNM_CASEFOLD = 1 << 4
}
;

#endif



