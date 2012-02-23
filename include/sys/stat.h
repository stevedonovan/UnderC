// sys/stat.h
#ifndef _SYS_STAT_H
#define _SYS_STAT_H
#include <sys/types.h>
typedef unsigned short ushort;

/* note: this is unlikely to work for anything except x86 Linux. */

#pragma pack(1)
    struct stat
    {
                  dev_t         st_dev;      /* device */
                  ushort        _pad1;      
                  ino_t         st_ino;      /* inode */
                  mode_t        st_mode;     /* protection */
                  nlink_t       st_nlink;    /* number of hard links */
                  uid_t         st_uid;      /* user ID of owner */
                  gid_t         st_gid;      /* group ID of owner */
                  dev_t         st_rdev;     /* device type (if inode device) */
                  ushort        _pad2;
                  uint         _padx;
                  off_t         st_size;     /* total size, in bytes */
                  unsigned long st_blksize;  /* blocksize for filesystem I/O */
                  unsigned long st_blocks;   /* number of blocks allocated */
                  time_t        st_atime;    /* time of last access */
                  uint          _pad3;
                  time_t        st_mtime;    /* time of last modification */
                  uint          _pad4;
                  time_t        st_ctime;    /* time of last change */
                  uint          _pad5;
                  uint          _pad6;
                  uint          _pad7;      
    };

#include <_shared_lib.h>
extern "C" {
  int __lxstat(int vs, const char *file_name, struct stat *buf);
  int __xstat(int vs, const char *file_name, struct stat *buf);
#lib

  // see <bits/stat.h> for this bit of redirection  
#define lstat(f,b) __lxstat(3,f,b)

const int  
    S_IFMT   =   0170000, //   bitmask for the file type bitfields
    S_IFSOCK =   0140000, //   socket
    S_IFLNK  =  0120000, //   symbolic link
    S_IFREG  =  0100000, //   regular file
    S_IFBLK  =  0060000, //   block device
    S_IFDIR  =  0040000, //   directory
    S_IFCHR  =  0020000, //   character device
    S_IFIFO  =  0010000, //   fifo
    S_ISUID  =  0004000, //   set UID bit
    S_ISGID  =  0002000, //   set GID bit (see below)
    S_ISVTX  =  0001000, //   sticky bit (see below)
    S_IRWXU  =  00700,   //     mask for file owner permissions
    S_IRUSR  =  00400,   //     owner has read permission
    S_IWUSR  =  00200,   //     owner has write permission
    S_IXUSR  =  00100,   //     owner has execute permission
    S_IRWXG  =  00070,   //     mask for group permissions
    S_IRGRP  =  00040,   //     group has read permission
    S_IWGRP  =  00020,   //     group has write permission
    S_IXGRP  =  00010,   //     group has execute permission
    S_IRWXO  =  00007,   //     mask for permissions for others (not in group)
    S_IROTH  =  00004,   //     others have read permission
    S_IWOTH  =  00002,   //     others have write permisson
    S_IXOTH  =  00001;   //     others have execute permission
 
#endif
