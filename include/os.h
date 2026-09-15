// os.h
// *ch 1.2.9 patch (argues with standard BeOS header)
#ifndef _UNDERC_OS_H
#define _UNDERC_OS_H

#include <stddef.h>

typedef void *Handle;
long get_file_time(const char *file);
// Copies size bytes of machine code into a page that the host permits to be
// executed.  Generated call stubs must not live on the C++ heap: every current
// desktop OS marks heap pages no-execute, so calling into one faults.
void *alloc_executable(const void *code, size_t size);
Handle load_library(const char *name);
void free_library(Handle h);
void *get_proc_address(Handle h, const char *name);
Handle get_process_handle();

#endif

