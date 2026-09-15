// CLASSLIB.H
// This concentrates all the assumptions about the iostreams
// and string libraries being used.  Personally I prefer the classic
// iostreams in console mode, and a hand-rolled string;  the std
// versions are too expensive in compilation time and executable size.
// The alternative libraries are all kept in the same directory to
// prevent confusion about include paths.
#ifndef _CLASSLIB_H
#define _CLASSLIB_H

//Use custom windows window instead of the dosbox _CONSOLE and _WCON can't be used together
#if defined(_WCON)
 #include "wcon.h"
#endif
//Implement string class with internal code or the system delivered implementation
#if defined(_MSTRING)
 #include "mstring.h"
#elif defined(NMSTRING)
 #include <string>
#endif
//Fake iostream with internal code or use the system implementation
//This has to be disabled for _WCON becouse all needed definitions are in wcon.h
#if defined(_FAKE_IOSTREAM) || defined(_WCON)
 #include "iostrm.h"
#elif defined(NFAKE_IOSTREAM) && !defined(_WCON)
 //#include <strstream> //Old include
 //#include <ostrstream> //Old include
 //#include <istrstream> //Old include
 #include <sstream> //New include replaces strstream/ostrstream/istrstream. This one actually supports the string class for streams strm.str()
 #include <iostream>
 #include <fstream>
 using std::string;
 using std::cout;
 using std::cerr;
 using std::cin;
 using std::endl;
 using std::ends;
 using std::ios;
 using std::ostream;
 using std::istream;
 using std::ifstream;
 using std::ostringstream;
 using std::istringstream;
#endif
//Use pointers for dll and plain console version and copys for the windows console
//Actually the wcon.h defines all things it needs on it's own
#if (defined(_CONSOLE) || defined(UCL_SHARED)) && !defined(_WCON)
 //*add 1.2.4 Redirection of cmsg and cerr is by redefining them to be pointer references
 //(see errors.cpp for the implementation)
 extern ostream* _cmsg_out;
 extern ostream* _cerr_out;
 //#undef cmsg
 #define cmsg *_cmsg_out //ASK: cmsg is not defined on msvc??
 //#undef cerr
 //#define cerr* _cerr_out //TEST: Don't know weather the relink works without this.
#elif defined(NCONSOLE) && defined(NUSRDLL)
 extern ostream str_cmsg;
 extern ostream str_cerr;
 //#undef cmsg
 #define cmsg str_cmsg
 //#undef cerr
 //#define cerr str_cerr
 //#undef cout
 //#define cout cmsg
#endif

// *ch 1.2.9 patch
// Use linux or windows function calls
#ifdef _WIN32
 #define __STDCALL __stdcall
 // disable warnings about template names being too long for the debugger..
 #pragma warning(disable:4786)
 #pragma warning(disable:4800)
#else
 // iscsym() and iscsymf() are useful <cctype> extensions found only on Windows
 #define iscsym(x)  (isalnum(x) || (x) == '_')
 #define iscsymf(x) (isalpha(x) || (x) == '_')
 // ditto for itoa()
 char *itoa(int, char *,int);
 #define __STDCALL
#endif

// a useful pattern for using STL containers
#define FORALL(i,ls) for(i = (ls).begin(); i != (ls).end(); ++i)

//FIXED: ios::in is c++ standart
#define IOS_IN_FLAGS ios::in

#endif

