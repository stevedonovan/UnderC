// _shared_lib.h
// UnderC Pocket C++ Library, Steve Donovan 2001.
// *note: there's no #elif yet!
#ifdef __win32__
#lib msvcrt40.dll
#else
#ifdef __linux__
#lib libc.so.6
#else
#lib libc.so
#endif
#endif
