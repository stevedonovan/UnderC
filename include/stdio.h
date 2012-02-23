/* 
 this file is deliberately empty (the stdio functions are built-in)
 * but FILE is often needed...
*/
#ifndef __stdio_h
#define __stdio_h
typedef int FILE;
FILE *stdin = _get_std_stream(1);
FILE *stdout = _get_std_stream(2);
FILE *stderr = _get_std_stream(3);

#include <_shared_lib.h>
extern "C" {
       int fputc(int c, FILE *stream);
       int fputs(const char *s, FILE *stream);
       int putc(int c, FILE *stream);
       int putchar(int c);
  //       int puts(const char *s);
}
#lib
#endif

