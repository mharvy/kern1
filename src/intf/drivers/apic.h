#pragma once

#include <stdint.h>

#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100
#define IA32_APIC_BASE_MSR_ENABLE 0x800

class APIC {
private:
    bool check_apic();
    void cpu_set_apic_base(uintptr_t);
    uintptr_t cpu_get_apic_base();
public:
    APIC();
    void init();
    void enable();
};

extern APIC apic;

