#include <stdint.h>
#include "rtc.h"
#include "io.h"
#include "libc/stdio.h"
#include "interrupt/8259PIC.h"



/* Les différents tableaux de chaînes de
caractère permettant de mapper les jours
de la semaine ainsi que les mois */


void initRTC(void) {

    __asm__ volatile("cli");
    
    outb(REGISTER_NUMBER, REGISTER_A_SELECTION);
    outb(RW_RTC, 0x20);
    __asm__ volatile("sti");

    //set_IRQ_RTC();
    //pic_clear_mask(8);
}


void set_IRQ_RTC(void) {

    __asm__ volatile("cli");
    outb(REGISTER_NUMBER, REGISTER_A_SELECTION);

    uint8_t value = inb(RW_RTC);
    outb(REGISTER_NUMBER, value | 0x40);
    __asm__ volatile("sti");
}

void change_hour_format(void) {

    __asm__ volatile("cli");

    uint8_t value_register = inb(REGISTER_B_SELECTION);
    if ((value_register & 0x02)) {
        
        outb(REGISTER_NUMBER, REGISTER_B_SELECTION);
        outb(REGISTER_NUMBER, value_register ^ 0x02);
    } else {
        
        outb(REGISTER_NUMBER, REGISTER_B_SELECTION);
        outb(REGISTER_NUMBER, value_register & 0x02);
    }

    __asm__ volatile("sti");
}

void enable_binary_mode(void) {

    __asm__ volatile("cli");

    uint8_t value_register = inb(REGISTER_B_SELECTION);
    outb(REGISTER_NUMBER, REGISTER_B_SELECTION);
    outb(REGISTER_NUMBER, value_register & 0x04);

    (inb(REGISTER_B_SELECTION) & 0x04) 
        ? printf("[RTC]: Mode binaire active.\n", (Vec3){107, 255, 225, 0})
        : printf("[RTC]: Mode binaire non active.\n", (Vec3){255, 50, 50, 0});

    __asm__ volatile("sti");
}

void enable_bcd_mode(void) {

    uint8_t value_register = inb(REGISTER_B_SELECTION);
    outb(REGISTER_NUMBER, REGISTER_B_SELECTION);
    outb(REGISTER_NUMBER, value_register ^ 0x04);

    ((inb(REGISTER_B_SELECTION) ^ 0x04) == 0) 
        ? printf("[RTC]: Mode BCD active.\n", (Vec3){107, 255, 225, 0})
        : printf("[RTC]: Mode BCD non active.\n", (Vec3){255, 50, 50, 0});
}

datetime_t get_time(void) {

    return (datetime_t){
        BCD2BIN(read_register(SECONDS_REGISTER)), BCD2BIN(read_register(MINUTES_REGISTER)),
        BCD2BIN2(read_register(HOURS_REGISTER)), BCD2BIN(read_register(WEEKDAY_REGISTER)),
        BCD2BIN(read_register(DAY_MONTHS_REGISTER)), BCD2BIN(read_register(MONTH_REGISTER)),
        BCD2BIN(read_register(YEAR_REGISTER))};
}
