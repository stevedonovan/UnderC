// math.h
// UnderC Pocket C++ Library, Steve Donovan 2001-2003
// UC already has as builtins:
// sin cos tan atan2 pow exp log sqrt atof
#ifndef __MATH_H
#define __MATH_H
#ifdef __win32__
#lib msvcrt40.dll
#else
#lib libm.so
#endif
extern "C" {
/* From Appendix B4 of K&R2 */
// double sin(double);
//double cos(double);
//double tan(double);
  double asin(double);
  double acos(double);
  double atan(double);
//double atan2(double, double);
  double sinh(double);
  double cosh(double);
  double tanh(double); 
//double exp(double); 
//double log(double); 
  double log10(double); 
//double pow(double, double); 
//double sqrt(double); 
  double ceil(double);       // was typed as 'ciel'
  double floor(double);
  double fabs(double);
  double ldexp(double, int);
  double frexp(double, int *);
  //* double mod(double, double *); *not in Linux?*
  double fmod(double, double);  
}
#lib
#endif