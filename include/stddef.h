/* stddef.h
 */
#ifndef _SIZE_T_DEF
#define _SIZE_T_DEF
typedef unsigned int size_t;
#endif

#ifndef NULL
#ifdef __cplusplus
  #define NULL 0
#else
  #define NULL ((void *)0)
#endif
#endif
