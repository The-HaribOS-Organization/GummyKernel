#include <io/lapic.h>
#include <stdint.h>
#include <cpuid.h>
#include <cpu_infos.h>
#include <io/msr.h>
#include <libs/stdio.h>
#include <video/vga_text.h>


uintptr_t get_apic_base() {

    uint32_t eax, edx;
    getMSR(IA32_APIC_BASE_MSR, &eax, &edx);

#ifdef __PHYSICAL_MEMORY_EXTENSION__
    return (eax & 0xFFFFF000) | ((edx & 0x0F) << 32);
#else
    return eax & 0xFFFFF000;
#endif
}

void lapic_write_register(uint32_t lapic_base, uint32_t lregister, uint32_t value) {

    *(volatile uint32_t *)(lapic_base + lregister) = value;
}

uint32_t lapic_read_register(uint32_t lapic_base, uint32_t lregister) {

    return *(volatile uint32_t *)(lapic_base + lregister);
}

void set_apic_base(uintptr_t apic) {

    uint32_t edx = 0;
    uint32_t eax = (apic & 0xFFFFF000) | IA32_APIC_BASE_MSR_ENABLE;

#ifdef __PHYSICAL_MEMORY_EXTENSION__
    edx = (apic << 32) & 0x0F;
#endif

    setMSR(IA32_APIC_BASE_MSR, eax, edx);
}

void enable_apic() {

    printf("[+]: Activation du APIC.\n");

    uintptr_t base = get_apic_base();
    set_apic_base(base);

    lapic_write_register(LAPIC_BASE_ADDRESS, LAPIC_SPURIOUS_IV_REGISTER, (lapic_read_register(LAPIC_BASE_ADDRESS, LAPIC_SPURIOUS_IV_REGISTER) | 0x100));

    terminal_setcolor(VGA_GREEN);
    printf("[+]: APIC active.\n");
    terminal_setcolor(VGA_WHITE);
}

void lapic_eoi() {

    lapic_write_register(LAPIC_BASE_ADDRESS, LAPIC_EOI_REGISTER, 0x0);
}
