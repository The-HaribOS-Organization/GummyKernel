#ifndef _RTC_
#define _RTC_


#include <stdint.h>
#include "io.h"


#define REGISTER_NUMBER 0x70
#define RW_RTC 0x71

#define REGISTER_A_SELECTION 0x8A
#define REGISTER_B_SELECTION 0x8B
#define REGISTER_C_SELECTION 0x8C

// Registres du RTC.
#define SECONDS_REGISTER 0x00
#define MINUTES_REGISTER 0x02
#define HOURS_REGISTER 0x04
#define WEEKDAY_REGISTER 0x06
#define DAY_MONTHS_REGISTER 0x07
#define MONTH_REGISTER 0x08
#define YEAR_REGISTER 0x09
#define CENTURY_REGISTER 0x32


#define BCD2BIN(x) ((x & 0x0F) + ((x / 16) * 10))
#define BCD2BIN2(x) (((x & 0x0F) + (((x & 0x70) / 16) * 10)) | (x & 0x80))
// ((x & 0x0F) + ((x >> 4) * 10))


static char months[12][11] = {
    "Janvier", "Fevrier", "Mars", "Avril",
    "Mai", "Juin", "Juillet", "Aout",
    "Septembre", "Octobre", "Novembre", "Decembre"};

static char weekdays[7][9] = {
    "Dimanche", "Lundi", "Mardi", "Mercredi",
    "Jeudi", "Vendredi", "Samedi"};

// Définition d'une structure contenant la date et l'heure.
typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t weekday;
    uint8_t day_month;
    uint8_t month;
    uint8_t year;
} datetime_t;


static inline char *map_month(uint8_t month) {

    return months[month - 1];
}

static inline char *map_week(uint8_t weekday) {

    return weekdays[weekday - 1];
}

void initRTC(void);
void set_IRQ_RTC(void);
void change_hour_format(void);
void enable_binary_mode(void);

datetime_t get_time(void);


inline uint8_t read_register(uint8_t regs) {

    outb(REGISTER_NUMBER, regs);
    return inb(RW_RTC);
}

#endif