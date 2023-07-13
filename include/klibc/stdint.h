/*
    File          : stdint.h
    Creation date : 11/07/2023
 */

#ifndef KLIBC_STDINT_H_INCLUDED
#define KLIBC_STDINT_H_INCLUDED

// +------------------+
// |  Unsigned types  |
// +------------------+

// exact size
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

// fast
typedef unsigned char uint_fast8_t;
typedef unsigned short uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long uint_fast64_t;

// least
typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long uint_least64_t;

// +----------------+
// |  Signed types  |
// +----------------+

// exact size
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

// fast
typedef signed char int_fast8_t;
typedef short int_fast16_t;
typedef int int_fast32_t;
typedef long long int_fast64_t;

// least
typedef signed char int_least8_t;
typedef short int_least16_t;
typedef int int_least32_t;
typedef long long int_least64_t;

// +--------------------------------+
// |  Maximum-width signed integer  |
// +--------------------------------+

typedef long long intmax_t;

// +----------------------------------+
// |  Maximum-width unsigned integer  |
// +----------------------------------+

typedef unsigned long long uintmax_t;

// +--------------------------------------------------+
// |  Signed integer type capable of holding a void*  |
// +--------------------------------------------------+

typedef int64_t intptr_t;

// +----------------------------------------------------+
// |  Unsigned integer type capable of holding a void*  |
// +----------------------------------------------------+

typedef uint64_t uintptr_t;

// +--------------------+
// | MAX and MIN values |
// +--------------------+

#define INT8_MIN (-128)
#define INT16_MIN (-32768)
#define INT32_MIN (-2147483647 - 1)
#define INT64_MIN  (-9223372036854775807LL - 1)

#define INT8_MAX 127
#define INT16_MAX 32767
#define INT32_MAX 2147483647
#define INT64_MAX 9223372036854775807LL

#define UINT8_MAX 255
#define UINT16_MAX 65535
#define UINT32_MAX 0xffffffffU  /* 4294967295U */
#define UINT64_MAX 0xffffffffffffffffULL /* 18446744073709551615ULL */

#endif // KLIBC_STDINT_H_INCLUDED