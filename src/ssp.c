#include <stdint.h>
#include "ssp.h"
#include "libc/stdio.h"


uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

__attribute__((noreturn))
void __stack_chk_fail(void) {

#if __STDC_HOSTED__
    printf("\x1b[255;50;50mStack Smashing detecte.");
#else
    printf("\x1b[255;50;50mStack Smashing detecte.");
#endif
}