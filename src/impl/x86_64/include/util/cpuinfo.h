#pragma once

#include "kernel/kmemcpy.h"

#include <stdint.h>
#include <cpuid.h>

enum cpuid_requests {
    CPUID_GETVENDORSTRING,
    CPUID_GETFEATURES,
    CPUID_GETTLB,
    CPUID_GETSERIAL,

    CPUID_GETHIGHESTFUNC = 0x80000000,
    CPUID_GETADDRSIZE = 0x80000008,
};

static inline bool cpuid(uint32_t cmd, uint32_t regs[]) {
    return __get_cpuid(cmd, &regs[0], &regs[1], &regs[2], &regs[3]);
}

static inline void cpuid_string(uint32_t cmd, uint8_t out[]) {
    uint32_t eax = 0;
    __get_cpuid(cmd, &eax, (uint32_t *)&out[0], (uint32_t *)&out[8], (uint32_t *)&out[4]);
    out[12] = '\0';
}

static inline bool cpu_has_msr() {
    uint32_t regs[4];
    cpuid(0x00000001U, regs);
    return regs[3] & (1 << 5);
}

static inline void cpu_get_msr(uint32_t msr, uint32_t *lo, uint32_t *hi) {
    asm volatile(
            "rdmsr"
            : "=a"(*lo), "=d"(*hi)
            : "c"(msr)
    );
}

static inline void cpu_set_msr(uint32_t msr, uint32_t lo, uint32_t hi) {
    asm volatile(
            "wrmsr"
            :
            : "a"(lo), "d"(hi), "c"(msr)
    );
}

