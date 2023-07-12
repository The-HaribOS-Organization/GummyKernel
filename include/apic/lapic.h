/*Ce fichier contient toutes les macros ainsi que
les prototypes de fonctions nécessaires à l'utilisation
du APIC locale.*/

#ifndef KERNEL_LAPIC_H_INCLUDED
#define KERNEL_LAPIC_H_INCLUDED

// #include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <cpuid.h>

/////////////////////////
//  Constants & types  //
/////////////////////////

#define LAPIC_BASE_ADDRESS 0xFEE00000
#define LAPIC_ID_REGISTER 0x20
#define LAPIC_VERSION_REGISTER 0x30
#define LAPIC_TASK_PROIRITY_REGISTER 0x80
#define LAPIC_EOI_REGISTER 0xB0
#define LAPIC_SPURIOUS_IV_REGISTER 0xF0
#define LAPIC_ERROR_STATUS_REGISTER 0x280
#define LAPIC_INTERRUPT_COMMAND_REGISTER_32F (0x300 << 32)
#define LAPIC_INTERRUPT_COMMAND_REGISTER_32L (0x310 >> 32)
#define LAPIC_TIMER_REGISTER 0x320
#define LAPIC_LINT1_REGISTER 0x360
#define LAPIC_ERROR_REGISTER 0x370
#define LAPIC_TIMER_INITIAL_COUNT_REGISTER 0x380
#define LAPIC_TIMER_DIVIDE_CONFIGURATION_REGISTER 0x3E0

#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100
#define IA32_APIC_BASE_MSR_ENABLE 0x800

/////////////////
//  Functions  //
/////////////////

void apic_enable();

uintptr_t apic_getBase();
void apic_setBase(uintptr_t apic);

uint32_t lapic_readRegister(uint32_t lapic_base, uint32_t lregister);
void lapic_writeRegister(uint32_t lapic_base, uint32_t lregister, uint32_t value);

#endif // KERNEL_LAPIC_H_INCLUDED
