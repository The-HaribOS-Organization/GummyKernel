/*
    File          : string.h
    Creation date : 11/07/2023
 */

#include "klibc/string.h"

void *memcpy(void *dest, const void *src, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        ((uint8_t *)dest)[i] = ((uint8_t *)src)[i];
    }
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
            return (str + i);
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