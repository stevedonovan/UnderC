// UnderC Development Project, 2001
#ifndef __STDLIB_H
#define __STDLIB_H

typedef void (*VOIDFN)();
typedef int (*COMPAREFN) (const void *, const void *);
#ifndef _SIZE_T_DEF
#define _SIZE_T_DEF
typedef unsigned int size_t;
#endif

#include <_shared_lib.h>
extern "C" {
  //char *getenv(char *);
  //double atof(const char *);
  //int atoi(const char *);
  long atol(const char *);
  double strtod(const char *, char **);
  long strtol(const char *, char **, int);
  unsigned long strtoul(const char *s, char **, int);
  int rand(void);
  void srand(unsigned int);
  void *malloc(size_t);
  void *realloc(void *, size_t);
  void free(void *);
  void exit(int);
  void abort(void);

  int atexit (VOIDFN);
  void *bsearch(const void *, const void *,
		size_t, size_t, COMPAREFN);
  void qsort(void *, size_t, size_t, COMPAREFN);
  int abs(int);
  long labs(long);

  struct div_t {
    int quot;
    int rem;
  };
  div_t div(int, int);

  struct ldiv_t {
    long quot;
    long rem;
  };
  ldiv_t ldiv(long, long);
}
#lib
#endif
