// regexp.h
// UnderC Development Project, 2002
// These are the POSIX regular expression functions.
// (Interface to the GNU RX library)

#ifndef __REGEXP_H
#define __REGEXP_H

#ifndef __unix__
#pragma dlink regex2.dll
#else
#pragma dlink libc.so.6
#endif

#ifndef _SIZE_T_DEF
#define _SIZE_T_DEF
typedef unsigned int size_t;
#endif

// really aren't interested in all the other fields...
struct regex_t {
  unsigned long int allocated;
  unsigned long int used;
  size_t re_nsub;
  char rest[20];
}; 

/* Type for byte offsets within the string.  POSIX mandates this.  */
typedef int regoff_t;

struct regmatch_t
{
  regoff_t rm_so; 		// Byte offset from string's start to substring's start.  
  regoff_t rm_eo;  		// Byte offset from string's start to substring's end. 
};

// POSIX `cflags' bits (i.e., information for `regcomp').
const int REG_EXTENDED = 1, REG_ICASE = 1 << 1, REG_NEWLINE = 1 << 2, REG_NOSUB = 1 << 3;

// POSIX 'eflags' biits (for regexec)
const int REG_NOTBOL = 1, REG_NOTEOL = 1 << 1, REG_ALLOC_REGS = 1 << 2;

typedef enum
{
  REG_NOERROR = 0,	/* Success.  */
  REG_NOMATCH,		/* Didn't find a match (for regexec).  */

  /* POSIX regcomp return error codes.  (In the order listed in the
     standard.)  */
  REG_BADPAT,		/* Invalid pattern.  */
  REG_ECOLLATE,		/* Inalid collating element.  */
  REG_ECTYPE,		/* Invalid character class name.  */
  REG_EESCAPE,		/* Trailing backslash.  */
  REG_ESUBREG,		/* Invalid back reference.  */
  REG_EBRACK,		/* Unmatched left bracket.  */
  REG_EPAREN,		/* Parenthesis imbalance.  */
  REG_EBRACE,		/* Unmatched \{.  */
  REG_BADBR,		/* Invalid contents of \{\}.  */
  REG_ERANGE,		/* Invalid range end.  */
  REG_ESPACE,		/* Ran out of memory.  */
  REG_BADRPT,		/* No preceding re for repetition op.  */

  /* Error codes we've added.  */
  REG_EEND,		/* Premature end.  */
  REG_ESIZE,		/* Compiled pattern bigger than 2^16 bytes.  */
  REG_ERPAREN		/* Unmatched ) or \); not returned from regcomp.  */
} reg_errcode_t;

extern "C" {
 int regcomp  (regex_t * preg, const char * pattern, int cflags);
 int regerror (int errcode, const regex_t *preg,
   		  char *errbuf, size_t errbuf_size);
 int regexec (const regex_t *preg, const char *str,
                 size_t nmatch, regmatch_t pmatch[], int eflags);
 void regfree (regex_t *preg);
}

#pragma dlink

#endif
