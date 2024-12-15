#include <stdint.h>
#include "klibc/math.h"


int ilogb(double x) {

    double i = 0;
    while (x > pow(2, i)) i++;

    return (int)i;
}

int ilogbf(float x) {
    
    float i = 0;
    while (x > powf(2, i)) i++;

    return (int)i;
}

int ilogbl(long double x) {

    long double i = 0;
    while (x > powl(2, i)) i++;

    return (int)i;
}

double acos(double cosinus) {

    double result = PI / 2;
    for (uint8_t i = 0; i < 20; i++)
        result += -(((factorial(2 * i) / (pow(2, 2 * i) * pow(factorial(i), 2)))) * (pow(cosinus, 2 * i + 1) / (2 * i + 1)));

    return result;
}

float acosf(float cosinus) {

    float result = PI / 2;
    for (uint8_t i = 0; i < 20; i++)
        result += -((((float)factorial(2 * i) / (powf(2, 2 * i) * powf((float)factorial(i), 2)))) * (powf(cosinus, 2 * i + 1) / (2 * i + 1)));

    return result;
}

long double acosl(long double cosinus) {

    double result = PI / 2;
    for (uint8_t i = 0; i < 20; i++)
        result += -((((long double)factorial(2 * i) / (powl(2, 2 * i) * powl((long double)factorial(i), 2)))) * (powl(cosinus, 2 * i + 1) / (2 * i + 1)));

    return result;
}

double acosh(double value) {

    return (log(value + sqrt(pow(value, 2) - 1)));
}

float acoshf(float value) {

    return (logf(value + sqrtf(powf(value, 2) - 1)));
}

long double acoshl(long double value) {

    return (logl(value + sqrtl(powl(value, 2) - 1)));
}

double modf(double value, double *intPtr) {

    *intPtr = value - (double)((int)value);
    return (double)((int)value);
}

float modff(float value, float *intPtr) {

    *intPtr = value - (float)((int)value);
    return (float)((int)value);
}

long double modfl(long double value, long double *intPtr) {

    *intPtr = value - (long double)((int)value);
    return (long double)((int)value);
}

double frexp(double value, int *exp) {

    double i = 0;
    while (value > pow(2, i)) i++;

    *exp = (int)i;
    return (value / pow(2, i));
}

float frexpf(float value, int *exp) {

    float i = 0;
    while (value > powf(2, i)) i++;

    *exp = (int)i;
    return (value / powf(2, i));
}

long double frexpl(long double value, int *exp) {

    long double i = 0;
    while (value > powl(2, i)) i++;

    *exp = (int)i;
    return (value / powl(2, i));
}

double cbrt(double value) {

    double result = 1;
    for (uint8_t i = 0; i < 10; i++)
        result = (1 / 3) * ((2 * result) + (value / (result * result)));

    return result;
}

float cbrtf(float value) {

    float result = 1;
    for (uint8_t i = 0; i < 10; i++)
        result = (1 / 3) * ((2 * result) + (value / (result * result)));

    return result;
}

long double cbrtl(long double value) {

    long double result = 1;
    for (uint8_t i = 0; i < 10; i++)
        result = (1 / 3) * ((2 * result) + (value / (result * result)));

    return result;
}

double sqrt(double value) {

    double result = 1;
    for (uint8_t i = 1; i < 21; i++)
        result += pow(-1, i) * (((2 * i - 3) / (2 * i)) * pow(value, i));

    return result;
}

float sqrtf(float value) {

    float result = 1;
    for (uint8_t i = 1; i < 21; i++)
        result += powf(-1, i) * (((2 * i - 3) / (2 * i)) * powf(value, i));

    return result;
}

long double sqrtl(long double value) {

    long double result = 1;
    for (uint8_t i = 1; i < 21; i++)
        result += powl(-1, i) * (((2 * i - 3) / (2 * i)) * powl(value, i));

    return result;
}

double pow(double value, double power) {

    if (power == 0) return 1;
    else return value * pow(value, power - 1);
}

float powf(float value, float power) {

    if (power == 0) return 1;
    else return value * powf(value, power - 1);
}

long double powl(long double value, long double power) {

    if (power == 0) return 1;
    else return value * powl(value, power - 1);
}

double factorial(double Number) {

    if (Number == 0) return 1;
    return Number * factorial(Number-1);
}

double exp(double x) {

    double result = 1;
    for (uint8_t i = 1; i < 21; i++) result += pow(x, i) / factorial(i);

    return result;
}

float expf(float x) {

    float result = 1;
    for (uint8_t i = 1; i < 21; i++) result += powf(x, i) / (float)factorial(i);

    return result;
}

long double expl(long double x) {

    long double result = 1;
    for (uint8_t i = 1; i < 21; i++) result += powl(x, i) / (long double)factorial(i);

    return result;
}

double log(double x) {
    
    double result = x;

    if (x <= 0) return -1;
    for (uint8_t i = 1; i < 21; i++)
        result += pow(-1, i - 1) * (pow(x, i) / i);
    
    return result;
}

float logf(float x) {

    double result = x;

    if (x <= 0) return -1;
    for (uint8_t i = 1; i < 21; i++)
        result += powf(-1, i - 1) * (powf(x, i) / i);
    
    return result;
}

long double logl(long double x) {

    double result = x;

    if (x <= 0) return -1;
    for (uint8_t i = 1; i < 21; i++)
        result += powl(-1, i - 1) * (powl(x, i) / i);
    
    return result;
}

double round(double value) {

    double diff = value - (int)value;
    return ((diff >= 0.5) ? (double)((int)value + 1) : (double)((int)value));
}

float roundf(float value) {

    float diff = value - (int)value;
    return ((diff >= 0.5) ? (float)((int)value + 1) : (float)((int)value));
}

long double roundl(long double value) {

    long double diff = value - (int)value;
    return ((diff >= 0.5) ? (long double)((int)value + 1) : (long double)((int)value));
}

double cos(double angle) {

    double result = 1.0;
    angle = (PI * angle) / 180;
    for (uint8_t i = 1; i < 21; i++)
        result += pow(-1, i) * (pow(angle, 2 * i) / factorial(2 * i));

    return result;
}

float cosf(float angle) {

    float result = 1.0;
    angle = (PI * angle) / 180;
    for (uint8_t i = 1; i < 21; i++)
        result += pow(-1, i) * (pow(angle, 2 * i) / (float)factorial(2 * i));

    return result;
}

long double cosl(long double angle) {

    long double result = 1.0;
    angle = (PI * angle) / 180;
    for (uint8_t i = 1; i < 21; i++)
        result += pow(-1, i) * (pow(angle, 2 * i) / (long double)factorial(2 * i));

    return result;
}

double cosh(double value) {

    double result = 1;
    for (uint8_t i = 1; i < 21; i++)
        result += (pow(value, 2 * i) / factorial(2 * i));

    return result;
}

float coshf(float value) {

    float result = 1;
    for (uint8_t i = 1; i < 21; i++)
        result += (powf(value, 2 * i) / (float)factorial(2 * i));

    return result;
}

long double coshl(long double value) {

    long double result = 1;
    for (int i = 1; i < 21; i++)
        result += (powl(value, 2 * i) / (long double)factorial(2 * i));

    return result;
}

double asin(double sinus) {

    double result = sinus;
    for (uint8_t i = 1; i < 21; i++)
        result += ((2 * i - 1) / (2 * i)) * (pow(sinus, 2 * i + 1) / (2 * i + 1));

    return result;
}

float asinf(float sinus) {

    float result = sinus;
    for (uint8_t i = 1; i < 21; i++)
        result += ((2 * i - 1) / (2 * i)) * (powf(sinus, 2 * i + 1) / (2 * i + 1));

    return result;
}

long double asinl(long double sinus) {

    long double result = sinus;
    for (uint8_t i = 1; i < 21; i++)
        result += ((2 * i - 1) / (2 * i)) * (powl(sinus, 2 * i + 1) / (2 * i + 1));

    return result;
}

double asinh(double value) {

    return (log(value + sqrt(pow(value, 2) + 1)));
}

float asinhf(float value) {

    return (logf(value + sqrtf(powf(value, 2) + 1)));
}

long double asinhl(long double value) {

    return (logl(value + sqrtl(powl(value, 2) + 1)));
}

double sin(double angle) {

    double result = 1.0;
    angle = (PI * angle) / 180;
    for (uint8_t i = 1; i < 21; i++)
        result += pow(-1, i) * (pow(angle, 2 * i + 1) / factorial(2 * i + 1));

    return result;
}

float sinf(float angle) {

    float result = 1.0;
    angle = (PI * angle) / 180;
    for (uint8_t i = 1; i < 21; i++)
        result += powf(-1, i) * (powf(angle, 2 * i + 1) / (float)factorial(2 * i + 1));

    return result;
}

long double sinl(long double angle) {

    long double result = 1.0;
    angle = (PI * angle) / 180;
    for (uint8_t i = 1; i < 21; i++)
        result += powl(-1, i) * (powl(angle, 2 * i + 1) / (long double)factorial(2 * i + 1));

    return result;
}

double sinh(double value) {

    double result = value;
    for (uint8_t i = 1; i < 21; i++)
        result += (pow(value, 2 * i + 1) / factorial(2 * i + 1));

    return result;
}

float sinhf(float value) {

    float result = value;
    for (uint8_t i = 1; i < 21; i++)
        result += (powf(value, 2 * i + 1) / (float)factorial(2 * i + 1));

    return result;
}

long double sinhl(long double value) {

    long double result = value;
    for (uint8_t i = 1; i < 21; i++)
        result += (powl(value, 2 * i + 1) / (long double)factorial(2 * i + 1));

    return result;
}

double atan(double value) {

    double result = value;
    for (uint8_t i = 1; i < 21; i++)
        result += pow(-1, i) * (pow(value, 2 * i + 1) / (2 * i + 1));

    return result;
}

float atanf(float value) {

    float result = value;
    for (uint8_t i = 1; i < 21; i++)
        result += powf(-1, i) * (powf(value, 2 * i + 1) / (2 * i + 1));

    return result;
}

long double atanl(long double value) {

    long double result = value;
    for (uint8_t i = 1; i < 21; i++)
        result += powl(-1, i) * (powl(value, 2 * i + 1) / (2 * i + 1));

    return result;
}

double atanh(double value) {

    return ((1 / 2) * log((1 + value) / (1 - value)));
}

float atanhf(float value) {

    return ((1 / 2) * logf((1 + value) / (1 - value)));
}

long double atanhl(long double value) {

    return ((1 / 2) * logl((1 + value) / (1 - value)));
}

double tan(double angle) {

    angle = (PI * angle) / 180;
    return (angle + (pow(angle, 3) / 3) + ((2 * pow(angle, 5)) / 15) + ((17 * pow(angle, 7)) / 315));
}

float tanf(float angle) {

    angle = (PI * angle) / 180;
    return (angle + (powf(angle, 3) / 3) + ((2 * powf(angle, 5)) / 15) + ((17 * powf(angle, 7)) / 315));
}

long double tanl(long double angle) {

    angle = (PI * angle) / 180;
    return (angle + (powl(angle, 3) / 3) + ((2 * powl(angle, 5)) / 15) + ((17 * powl(angle, 7)) / 315));
}

double tanh(double value) {

    return (value - (pow(value, 3) / 3) + ((2 * pow(value, 5)) / 15) - ((17 * pow(value, 7)) / 315));
}

float tanhf(float value) {

    return (value - (powf(value, 3) / 3) + ((2 * powf(value, 5)) / 15) - ((17 * powf(value, 7)) / 315));
}

long double tanhl(long double value) {

    return (value - (powl(value, 3) / 3) + ((2 * powl(value, 5)) / 15) - ((17 * powl(value, 7)) / 315));
}
