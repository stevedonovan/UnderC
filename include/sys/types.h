// sys/types.h
#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

typedef unsigned int uint;
struct int64
{
  int low,high;
};

typedef int64 dev_t;
typedef uint ino_t;
typedef uint mode_t;
typedef uint nlink_t;
typedef uint uid_t;
typedef uint gid_t;
typedef uint off_t;

// no. of seconds since midnight Jan 1, 1970
#ifndef _TIME_T_DEFINED
typedef long time_t;             /* time value */
typedef unsigned long _fsize_t;
#define _TIME_T_DEFINED          /* avoid multiple def's of time_t */
#endif

#endif

    
  
