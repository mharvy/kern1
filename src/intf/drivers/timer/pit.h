#pragma once

#include <stdint.h>

#define PIT_IRQ 0x00

#define CHANNEL0_PORT 0x40
#define CHANNEL1_PORT 0x41
#define CHANNEL2_PORT 0x42
#define CMD_REG 0x43

#define CHAN0_MODE2 0x34  // 0b 00 11 010 0

#define MAX_FREQ 1193180

extern "C" void main_pit_handler();
extern "C" void main_pit_linkage();

// Will only support channel 0 for now
class PIT {
private:
    PIT();
public:
    static PIT & get_instance();
    void init();
    void set_freq(uint32_t freq);
    void change_mode();
    void interrupt_handler();
};

