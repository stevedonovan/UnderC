/* dirent.h
 */
#ifndef _DIRENT_H
#define _DIRENT_H

typedef unsigned int __ino_t;
typedef unsigned int __off_t;

// UC defaults to 32-bit alignment in structures
#pragma pack(1)

// this is implementation-dependent - POSIX only guarantees d_name
struct dirent
  {
    __ino_t d_ino;
    __off_t d_off;
    unsigned short int d_reclen;
    unsigned char d_type;
    char d_name[256];	
  };

#pragma pack(4)

typedef int DIR;

#include <_shared_lib.h>
extern "C" {
  DIR *opendir(const char *name);
  int closedir(DIR *dir);
  dirent *readdir(DIR *dir);
}
#lib

#endif
