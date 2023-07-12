/* Contient tous le prototypes de fonctions
ainsi que les macros nécéssaires à l'utilisation du PIC.*/

#ifndef KERNEL_PIC_H_INCLUDED
#define KERNEL_PIC_H_INCLUDED

// #include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/////////////////////////
//  Constants & types  //
/////////////////////////

#define PIC1_COMMAND 0x20
#define PIC2_COMMAND 0xA0
#define PIC1_DATA 0x21
#define PIC2_DATA 0xA1
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28

#define PIC_EOI 0x20
#define ICW1_ICW4 0x01
#define ICW1_SINGLE 0x02
#define ICW1_INTERVAL4 0x04
#define ICW1_LEVEL 0x08
#define ICW1_INIT 0x10

#define ICW4_8086 0x01
#define ICW4_AUTO 0x02
#define ICW4_BUF_SLAVE 0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM 0x10

/////////////////
//  Functions  //
/////////////////

bool PIC_enable();
bool PIC_disable();

void PIC_remap(uint8_t offset_master, uint8_t offset_slave);
void PIC_endOfInterrupt(uint8_t interrupt);

bool IRQ_mask(uint8_t irq);
bool IRQ_unmask(uint8_t irq);

#endif // KERNEL_PIC_H_INCLUDED