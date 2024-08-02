#include <stdint.h>
#include "interrupt/isr.h"
#include "libc/stdio.h"


static char *isr_name[] = {
    "Division Error", "Debug", "Non-maskable Interrupt", "Breakpoint",
    "Overflow", "Bound Range Exceeded", "Invalid Opcode", "Device Not Available",
    "Double Fault", "Coprocessor Segment Overrun", "Invalid TSS", "Segment Not Present",
    "Stack-Segment Fault", "General Protection Fault", "Page Fault", "Reserved",
    "x87 Floating-Point Exception", "Alignment Check", "Machine Check", "SIMD Floating-Point Exception",
    "Virtualization Exception", "Control Protection Exception", "Reserved", "Hypervisor Injection Exception",
    "VMM Communication Exception", "Security Exception", "Reserved"};

void isr_handler(isr_frame *frame) {

    if (frame->interrupt < 32) {
        printf("Interruption: ", (Vec3){255, 107, 107, 0});
        printf(isr_name[frame->interrupt], (Vec3){255, 107, 107, 0});
        __asm__ volatile("cli; hlt");
    }
}