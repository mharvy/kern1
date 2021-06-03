#include "drivers/pit.h"
#include "drivers/pic.h"
#include "util/io.h"
#include "kernel/printk.h"

#include <stdint.h>

PIT main_pit;

void main_pit_handler() {
    main_pit.interrupt_handler();
}

PIT::PIT() {
}

void PIT::init() {
    asm volatile("cli");
    outb(CMD_REG, CHAN0_MODE2);
    set_freq(100);
    pic.enable_IRQ(PIT_IRQ);
    asm volatile("sti");
}

void PIT::change_mode() {
}

void PIT::set_freq(uint32_t freq) {
    uint32_t div = MAX_FREQ / freq;
    outb(CHANNEL0_PORT, (uint8_t)div);
    outb(CHANNEL0_PORT, (uint8_t)(div >> 8));
}

void PIT::interrupt_handler() {
    pic.send_EOI(PIT_IRQ);

    // Testing
    printk("PIT");
}

