/* Cet en-tête contient tous les prototypes de fonctions
nécessaires au fonctionnement du RTC (Real-Time Clock).*/
#ifndef _RTC_
#define _RTC_

#include <stdint.h>

#define RTC_REGISTER_NUMBER 0x70
#define RTC_IO_PORT 0x71

#define DISABLE_INTERRUPT() asm volatile("cli")
#define ENABLE_INTERRUPT() asm volatile("sti")


enum rtc_time_registers {
    SECONDS = 0x00,
    MINUTES = 0x02,
    HOURS = 0x04,
    WEEKDAY = 0x06,
    DAY_OF_MONTH = 0x07,
    MONTHS = 0x08,
    YEAR = 0x09,
};

void setup_rtc();
uint8_t get_register_infos(uint8_t reg);

#endif
