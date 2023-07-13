#include "klibc/assert.h"

void _Assert(char *msg)
{
    puts(msg);
    puts(" -- assertion failed");
    kpanic_execute();
}