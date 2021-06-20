#include "drivers/apic.h"
#include "util/cpuinfo.h"
#include "util/io.h"

#include <stdint.h>

bool APIC::check_apic() {
    uint32_t regs[4];
    cpuid(0x80000001U, regs);
    return regs[3] & (1 << 9);
}

void APIC::cpu_set_apic_base(uintptr_t apic) {
    uint32_t edx = 0;
    uint32_t eax = (apic & 0xFFFFF000) | IA32_APIC_BASE_MSR_ENABLE;

    edx = (apic >> 32) & 0x0F;

    cpu_set_msr(IA32_APIC_BASE_MSR, eax, edx);
}

uintptr_t APIC::cpu_get_apic_base() {
    uint32_t eax, edx;
    cpu_get_msr(IA32_APIC_BASE_MSR, &eax, &edx);

    return (eax & 0xFFFFF000) | ((edx & 0x0F) << 32);
}

APIC::APIC() {

}

void APIC::init() {

}

void APIC::enable() {
    // Enable the local APIC if not already enabled
    cpu_set_apic_base(cpu_get_apic_base());

    // Start receiving interrupts
    outw(0xF0, inw(0xF0) | 0x100);
}

