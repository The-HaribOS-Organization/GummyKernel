#include "apic/lapic.h"

void apic_enable()
{
    //printf("[+]: Activation du APIC.\n");

    uintptr_t base = apic_getBase();
    apic_setBase(base);

    lapic_writeRegister(LAPIC_BASE_ADDRESS, LAPIC_SPURIOUS_IV_REGISTER, (lapic_readRegister(LAPIC_BASE_ADDRESS, LAPIC_SPURIOUS_IV_REGISTER) | 0x100));

    //terminal_setcolor(VGA_GREEN);
    //printf("[+]: APIC active.\n");
    //terminal_setcolor(VGA_WHITE);
}

uintptr_t apic_getBase()
{
    uint32_t eax;
    uint32_t edx;

    getMSR(IA32_APIC_BASE_MSR, &eax, &edx);

#ifdef __PHYSICAL_MEMORY_EXTENSION__
    return (eax & 0xFFFFF000) | ((edx & 0x0F) << 32);
#else
    return eax & 0xFFFFF000;
#endif
}

void apic_setBase(uintptr_t apic)
{
    uint32_t edx = 0;
    uint32_t eax = (apic & 0xFFFFF000) | IA32_APIC_BASE_MSR_ENABLE;

#ifdef __PHYSICAL_MEMORY_EXTENSION__
    edx = (apic << 32) & 0x0F;
#endif

    setMSR(IA32_APIC_BASE_MSR, eax, edx);
}

uint32_t lapic_readRegister(uint32_t lapic_base, uint32_t lregister)
{
    return *(volatile uint32_t*)((uintptr_t)lapic_base + lregister);
}

void lapic_writeRegister(uint32_t lapic_base, uint32_t lregister, uint32_t value)
{
    *(volatile uint32_t*)((uintptr_t)lapic_base + lregister) = value;
}