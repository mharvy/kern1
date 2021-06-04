#pragma once

#include "drivers/input/scancode.h"

#include <stdint.h>

#define PS2_KEYBOARD_IRQ 1
#define PS2_KEYBOARD_PORT 0x60

extern "C" void main_ps2keyboard_handler();
extern "C" void main_ps2keyboard_linkage();

class PS2Keyboard {
private:
    bool active = false;
    Scancode scancode;
    uint64_t keys;
    bool shift_pressed = false;
    bool caps_on = false;
    PS2Keyboard();

public:
    static PS2Keyboard & get_instance();
    void init();
    void interrupt_handler();
    void stop();
    void enable();
    uint64_t get_keys();
};

