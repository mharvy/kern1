#pragma once

#include <stdint.h>

#define RTC_PORT 0x70
#define CMOS_PORT 0x71
#define RTC_IRQ 8

#define NMI_A 0x8A
#define NMI_MASK 0x8B
#define REG_C 0x0C

extern "C" void main_rtc_handler();
extern "C" void main_rtc_linkage();

class RTC {
private:
    uint32_t freq = 1024;
    uint32_t seconds;
    RTC();

public:
    static RTC & get_instance();
    void init();
    void interrupt_handler();
    void set_freq(uint32_t freq);
    uint32_t open();
    uint32_t close();
    uint32_t read();
    uint32_t write();
};

