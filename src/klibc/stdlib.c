#include "klibc/stdlib.h"

/////////////////
//  Functions  //
/////////////////



/////////////////////////////
//  Non standard fucntion  //
/////////////////////////////

char *itoa(int num, char *str, int base)
{
    int i = 0;
    bool isNegative = false;

    // Special cases
    if(num == 0)
    {
        str[i++] = '0'; // str[0] but i is now 1
        str[i] = '\0';
        return str;
    }

    if(num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Conversion
    while(num != 0)
    {
        int modulo = num % base;
        str[i++] = (modulo > 9) ? (modulo - 10) + 'a' : modulo + '0';
        num = num / base;
    }

    if(isNegative)
    {
        str[i++] = '-';
    }

    str[i] = '\0';

    // Final reverse
    strrev(str);
}