/* limits.h
 */
#ifndef __LIMITS_H
#define __LIMITS_H


#define CHAR_BIT   8
#define SCHAR_MIN  (-128)
#define SCHAR_MAX  127
#define UCHAR_MAX  0xff

#define CHAR_MIN   SCHAR_MIN
#define CHAR_MAX   SCHAR_MAX

#define MB_LEN_MAX 5
#define SHRT_MIN   (-32768)
#define SHRT_MAX   32767
#define USHRT_MAX  0xffffU
#define INT_MIN    (-2147483647 - 1)
#define INT_MAX    2147483647
#define UINT_MAX   0xffffffffU
#define LONG_MIN   (-2147483647L - 1)
#define LONG_MAX   2147483647L
#define ULONG_MAX  0xffffffffUL

#define _I8_MIN    (-127 - 1)
#define _I8_MAX    127
#define _UI8_MAX   0xffu

#define _I16_MIN   (-32767 - 1)
#define _I16_MAX   32767
#define _UI16_MAX  0xffffu

#define _I32_MIN   (-2147483647 - 1)
#define _I32_MAX   2147483647
#define _UI32_MAX  0xffffffffu

#endif
