/* 
   Cet en-tête contient tous les prototypes de fonctions
   nécessaires au fonctionnement du RTC (Real-Time Clock).
*/

#ifndef KERNEL_RTC_H_INCLUDED
#define KERNEL_RTC_H_INCLUDED

// #include <stdio.h>
#include <stdint.h>

/////////////////////////
//  Constants & types  //
/////////////////////////

#define RTC_REGISTER_NUMBER 0x70
#define RTC_IO_PORT 0x71

#define DISABLE_INTERRUPT() __asm__ volatile("cli")
#define ENABLE_INTERRUPT() __asm__ volatile("sti")

typedef enum {
    SECONDS = 0x00,
    MINUTES = 0x02,
    HOURS = 0x04,
    WEEKDAY = 0x06,
    DAY_OF_MONTH = 0x07,
    MONTHS = 0x08,
    YEAR = 0x09,
} RTCTimeRegisters;

/////////////////
//  Functions  //
/////////////////

void rtc_setup();
uint8_t rtc_getRegisterInfos(uint8_t reg);

#endif // KERNEL_RTC_H_INCLUDED
