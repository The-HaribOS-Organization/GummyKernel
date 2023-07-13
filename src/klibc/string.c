#include "klibc/string.h"

/////////////////
//  Functions  //
/////////////////

void *memcpy(void *dest, const void *src, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        ((uint8_t *)dest)[i] = ((uint8_t *)src)[i];
    }

    return dest;
}

void *memmove(void *dest, const void *src, size_t n)
{
    uint8_t *from = (uint8_t *)src;
    uint8_t *to = (uint8_t *)dest;

    // from -> |--------|
    // to   -> |--------|
    if (from == to || n == 0)
    {
        return dest;
    }

    // from -> |--------|
    // to   ->      |--------|
    if (to > from && to - from < (ptrdiff_t)n)
    {
        for (size_t i = n-1; i >= 0; --i)
        {
            to[i] = from[i];
        }
        return dest;
    }

    // from ->      |--------|
    // to   -> |--------|
    if (from > to && from - to < (ptrdiff_t)n)
    {
        for (size_t i = 0; i < n; i++)
        {
            to[i] = from[i];
        }
        return dest;
    }

    memcpy(dest, src, n);
    return dest;
}

void *memchr(const void *str, int c, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        if(((int *)str)[i] == c)
        {
            return (void*)str + i;
        }
    }

    return NULL;
}

int memcmp(const void *ptr1, const void *ptr2, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        int v1 = ((int *)ptr1)[i];
        int v2 = ((int *)ptr2)[i];
        if (v1 != v2)
        {
            if (v1 < v2)
                return -1;
            return 1;
        }
    }
    return 0;
}

void *memset(void *ptr, int value, size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        ((int *)ptr)[i] = value;
    }

    return ptr;
}

size_t strlen(const char *str)
{
    size_t length = 0;
    while(str[length] != '\0')
    {
        ++length;
    }
    return length;
}

/////////////////////////////
//  Non standard fucntion  //
/////////////////////////////

char *strrev(char *str)
{
    if(str == NULL)
    {
        return NULL;
    }

    int length = strlen(str);

    for(int i = 0; i < length / 2; ++i)
    {
        char tmp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = tmp;
    }
}