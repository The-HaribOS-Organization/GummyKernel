#include <io/pic.h>
#include <io/cursor.h>
#include <video/vga_text.h>
#include <libs/stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <idt/irq/irq.h>

void PICremap(uint8_t offset_master, uint8_t offset_slave) {

    printf("[+]: Remapping du PIC.\n");

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC1_DATA, PIC1_START_INTERRUPT);
    io_wait();
    outb(PIC2_DATA, PIC2_START_INTERRUPT);
    io_wait();
    outb(PIC1_DATA, 0x04);
    io_wait();
    outb(PIC2_DATA, 0x02);
    io_wait();
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, offset_master);
    outb(PIC2_DATA, offset_slave);

    terminal_setcolor(VGA_GREEN);
    printf("[+]: PIC remappe.\n");
    terminal_setcolor(VGA_WHITE);
}

bool disable_PIC() {

    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
    return true;
}

bool enable_PIC() {

    outb(PIC1_DATA, 0x00);
    outb(PIC2_DATA, 0x00);
    return true;
}

bool mask_IRQ(uint8_t irq) {

    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = inb(port) | (1 << irq);
    outb(port, value);

    return true;
}

bool unmask_IRQ(uint8_t irq) {

    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = inb(port) & ~(1 << irq);
    outb(port, value);
    
    return true;
}

void PIC_endOfInterrupt(uint8_t interrupt) {

    if (interrupt >= 40) {
        outb(PIC1_COMMAND, PIC_EOI);
    } else {
        outb(PIC2_COMMAND, PIC_EOI);
    }
}