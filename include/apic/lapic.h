/*Ce fichier contient toutes les macros ainsi que
les prototypes de fonctions nécessaires à l'utilisation
du APIC locale.*/

#ifndef _LAPIC_
#define _LAPIC_

#include <stdint.h>
#include <stdbool.h>

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


uintptr_t get_apic_base();
uint32_t lapic_read_register(uint32_t lapic_base, uint32_t lregister);
void lapic_write_register(uint32_t lapic_base, uint32_t lregister, uint32_t value);
void set_apic_base(uintptr_t apic);
void enable_apic();

#endif
