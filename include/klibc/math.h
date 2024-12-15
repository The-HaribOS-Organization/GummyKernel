#ifndef _MATH_
#define _MATH_

#include <stdint.h>


#define PI 3.141592653589793
#define FLT_RADIX 2


double acos(double cosinus);
float acosf(float cosinus);
long double acosl(long double cosinus);
double acosh(double value);
float acoshf(float value);
long double acoshl(long double value);
double cos(double angle);
float cosf(float angle);
long double cosl(long double angle);
double cosh(double value);
float coshf(float value);
long double coshl(long double value);

double asin(double sinus);
float asinf(float sinus);
long double asinl(long double sinus);
double asinh(double value);
float asinhf(float value);
long double asinhl(long double value);
double sin(double angle);
float sinf(float angle);
long double sinl(long double angle);
double sinh(double value);
float sinhf(float value);
long double sinhl(long double value);

double atan(double value);
float atanf(float value);
long double atanl(long double value);
double atanh(double value);
float atanhf(float value);
long double atanhl(long double value);
double tan(double angle);
float tanf(float angle);
long double tanl(long double angle);
double tanh(double value);
float tanhf(float value);
long double tanhl(long double value);

double exp(double x);
float expf(float x);
long double expl(long double x);

double cbrt(double value);
float cbrtf(float value);
long double cbrtl(long double value);

double frexp(double value, int *exp);
float frexpf(float value, int *exp);
long double frexpl(long double value, int *exp);
int ilogb(double x);
int ilogbf(float x);
int ilogbl(long double x);

double log(double x);
float logf(float x);
long double logl(long double x);

double round(double value);
float roundf(float value);
long double roundl(long double value);

double factorial(double Number);
double modf(double value, double *intPtr);
float modff(float value, float *intPtr);
long double modfl(long double value, long double *intPtr);
double pow(double value, double power);
float powf(float value, float power);
long double powl(long double value, long double power);
double sqrt(double value);
float sqrtf(float value);
long double sqrtl(long double value);

inline double ceil(double value) {

    return ((value >= 0.0) ? (double)((int)value + 1) : (double)((int)value));
}

inline float ceilf(float value) {

    return ((value >= 0.0) ? (float)((int)value + 1) : (float)((int)value));
}

inline long double ceill(long double value) {

    return ((value >= 0.0) ? (long double)((int)value + 1) : (long double)((int)value));
}

inline double trunc(double value) {

    return (int)value;
}

inline double floor(double value) {

    return (int)value;
}

inline float floorf(float value) {

    return (int)value;
}

inline long double floorl(long double value) {

    return (int)value;
}

inline double fmax(double x, double y) {

    return ((x > y) ? x : y);
}

inline float fmaxf(float x, float y) {

    return ((x > y) ? x : y);
}

inline long double fmaxl(long double x, long double y) {

    return ((x > y) ? x : y);
}

inline double fmin(double x, double y) {

    return ((x < y) ? x : y);
}

inline float fminf(float x, float y) {

    return ((x < y) ? x : y);
}

inline long double fminl(long double x, long double y) {

    return ((x < y) ? x : y);
}

inline double fdim(double x, double y) {

    return fmax(x - y, 0);
}

inline float fdimf(float x, float y) {

    return fmaxf(x - y, 0);
}

inline long double fdiml(long double x, long double y) {

    return fmaxl(x - y, 0);
}

inline double log10(double x) {

    return (log(x) / log(10));
}

inline float log10f(float x) {

    return (logf(x) / logf(10));
}

inline long double log10l(long double x) {

    return (logl(x) / logl(10));
}

inline double log10p1(double x) {

    return log10(x + 1);
}

inline float log10p1f(float x) {

    return log10f(x + 1);
}

inline long double log10p1l(long double x) {

    return log10l(x + 1);
}

inline double log2(double x) {

    return (log(x) / log(2));
}

inline float log2f(float x) {

    return (logf(x) / logf(2));
}

inline long double log2l(long double x) {

    return (logl(x) / logl(2));
}

inline double logp12(double x) {

    return log2(1 + x);
}

inline float log2p1f(float x) {

    return log2f(1 + x);
}

inline long double log2p1l(long double x) {

    return log2l(1 + x);
}

inline double expm1(double x) {

    return exp(x) - 1;
}

inline float expm1f(float x) {

    return expf(x) - 1;
}

inline long double expm1l(long double x) {

    return expl(x) - 1;
}

inline double exp2(double x) {

    return pow(2, x);
}

inline float exp2f(float x) {

    return powf(2, x);
}

inline long double exp2l(long double x) {

    return powl(2, x);
}

inline double exp2m1(double x) {

    return pow(2, x) - 1;   
}

inline float exp2m1f(float x) {

    return powf(2, x) - 1;
}

inline long double exp2m1l(long double x) {

    return powl(2, x) - 1;
}

inline double exp10(double x) {

    return pow(10, x);
}

inline float exp10f(float x) {

    return powf(10, x);
}

inline long double exp10l(long double x) {
    
    return powl(10, x);
}

inline double exp10m1(double x) {

    return pow(10, x) - 1;
}

inline float exp10m1f(float x) {

    return powf(10, x) - 1;
}

inline long double exp10m1l(long double x) {

    return powl(10, x) - 1;
}

inline double atan2(double y, double x) {

    return atan(y / x);
}

inline float atan2f(float y, float x) {

    return atanf(y / x);
}

inline long double atan2l(long double y, long double x) {

    return atanl(y / x);
}

inline double log1p(double x) {

    return log(x + 1);
}

inline double logp1(double x) {
    
    return log(x + 1);
}

inline float log1pf(float x) {

    return logf(x + 1);
}

inline float logp1f(float x) {

    return logf(x + 1);
}

inline long double log1pl(long double x) {

    return logl(x + 1);
}

inline long double logp1l(long double x) {

    return logl(x + 1);
}

inline double ldexp(double x, int exp) {

    return (x * pow(2, exp));
}

inline float ldexpf(float x, int exp) {

    return (x * powf(2, exp));
}

inline long double ldexpl(long double x, int exp) {

    return (x * powl(2, exp));
}

inline double scalbln(double value, long exp) {

    return (value * pow(FLT_RADIX, exp));
}

inline float scalblnf(float value, long exp) {

    return (value * powf(FLT_RADIX, exp));
}

inline long double scalblnl(long double value, long exp) {

    return (value * powl(FLT_RADIX, exp));
}

inline double scalbn(double value, int exp) {

    return (value * pow(FLT_RADIX, exp));
}

inline float scalbnf(float value, int exp) {

    return (value * powf(FLT_RADIX, exp));
}

inline long double scalbnl(long double value, int exp) {

    return (value * powl(FLT_RADIX, exp));
}

#endif
