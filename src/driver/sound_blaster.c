#include "driver/sound_blaster.h"

static void programDMA(uint8_t bit_transfert)
{
    if (bit_transfert == 8)
    {
        outb(0x0A, 0x05);
        outb(0x0C, 0x01);
        outb(0x0B, 0x49);
        outb(0x83, 0x10);
        outb(0x02, 0x50);
        outb(0x02, 0x04);
        outb(0x03, 0xFF);
        outb(0x03, 0x0F);
        outb(0x0A, 0x01);
    }
    else if (bit_transfert == 16)
    {
        outb(0xD4, 0x05);
        outb(0xD8, 0x01);
        outb(0xD6, 0x49);
        outb(0x8B, 0x10);
        outb(0xC4, 0x50);
        outb(0xC4, 0x04);
        outb(0xC6, 0xFF);
        outb(0xC6, 0x0F);
        outb(0xD4, 0x01);
    }
}

static bool resetDSP()
{
    outb(DSP_RESET_PORT, 0x1);
    io_wait();
    outb(DSP_RESET_PORT, 0x0);

    return (inb(DSP_READ_PORT) == 0xAA);
}

void init_sound_blaster()
{
    // terminal_setcolor(VGA_WHITE);
    puts("[+]: Configuration du sound blaster.\n");

    bool dsp_reset = resetDSP();
    if (dsp_reset)
    {
        // terminal_setcolor(VGA_GREEN);
        puts("[+]: Le DSP est reinitialise.\n");
        // terminal_setcolor(VGA_WHITE);
    }
    else
    {
        // terminal_setcolor(VGA_RED);
        puts("[+]: Le DSP n'a pas ete reinitialise.\n");
        // terminal_setcolor(VGA_WHITE);
    }

    soundBlaster_setVolume(0xC, 0xC);
    soundBlaster_turnOn();
    
    programDMA(0x08);

    outb(DSP_WRITE_PORT, 0x40);
    outb(DSP_WRITE_PORT, 165);
    outb(DSP_WRITE_PORT, 0xC0);
    outb(DSP_WRITE_PORT, 0x00);
    outb(DSP_WRITE_PORT, 0xFE);
    outb(DSP_WRITE_PORT, 0x0F);
}

void soundBlaster_turnOn()
{
    outb(DSP_WRITE_PORT, TURN_SPEAKER_ON);
}

void soundBlaster_turnOff()
{
    outb(DSP_WRITE_PORT, TURN_SPEAKER_OFF);
}

uint8_t soundBlaster_setVolume(uint8_t left, uint8_t right)
{
    outb(DSP_MIXER_PORT, MASTER_VOLUME);
    outb(MASTER_VOLUME, left | right);

    return left | right;
}

void soundBlaster_setIrq(uint8_t irq_number)
{
    outb(DSP_MIXER_PORT, 0x80);
    outb(DSP_MIXER_DATA_PORT, irq_number);
}