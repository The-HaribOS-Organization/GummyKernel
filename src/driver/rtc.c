#include "driver/rtc.h"

void rtc_setup()
{
    puts("[+]: Configuration du RTC.\n");
    
    DISABLE_INTERRUPT();
    outb(RTC_REGISTER_NUMBER, 0x8B);
    outb(RTC_IO_PORT, 0x20);
    ENABLE_INTERRUPT();
    
    // terminal_setcolor(VGA_GREEN);
    puts("[+]: RTC configure.\n");
    // terminal_setcolor(VGA_WHITE);
}

uint8_t rtc_getRegisterInfos(uint8_t reg)
{
    outb(RTC_REGISTER_NUMBER, reg);
    return inb(RTC_IO_PORT);
}