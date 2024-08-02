#ifndef _SSP_H
#define _SSP_H

#include <stdint.h>
#include "libc/stdio.h"


#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xe2dee396
#else
#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif

extern uintptr_t __stack_chk_guard;

__attribute__((noreturn))
extern void __stack_chk_fail(void);

#endif
