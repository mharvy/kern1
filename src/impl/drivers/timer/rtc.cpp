#include "drivers/timer/rtc.h"
#include "util/io.h"
#include "drivers/pic.h"
#include "kernel/printk.h"

#include <stdint.h>

extern "C" void main_rtc_handler() {
    RTC::get_instance().interrupt_handler();
}

RTC::RTC() {
}

RTC & RTC::get_instance() {
    static RTC instance = RTC();
    return instance;
}

void RTC::init() {
    asm volatile("cli");
    outb(RTC_PORT, NMI_MASK);
    uint8_t temp = inb(CMOS_PORT);
    outb(RTC_PORT, NMI_MASK);
    outb(CMOS_PORT, temp | 0x40);
    pic.enable_IRQ(RTC_IRQ);
    asm volatile("sti");
}

void RTC::interrupt_handler() {
    pic.send_EOI(RTC_IRQ);

    outb(RTC_PORT, 0x00);
    int time = inb(CMOS_PORT);
    time = (time & 0x0F) + ((time / 16) * 10);

    outb(RTC_PORT, REG_C);  // Register C must be read
    inb(CMOS_PORT);
}

void RTC::set_freq(uint32_t freq) {
}

uint32_t RTC::open() {
}

uint32_t RTC::close() {
}

uint32_t RTC::read() {
}

uint32_t RTC::write() {
}

