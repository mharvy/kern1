#pragma once

#include "drivers/input/scancode.h"

#include <stdint.h>

extern "C" void main_ps2keyboard_handler();
extern "C" void ps2keyboard_linkage();

class PS2Keyboard {
private:
    bool active = false;
    Scancode scancode;
    uint64_t keys;
    bool shift_pressed = false;
    bool caps_on = false;

public:
    PS2Keyboard();
    void init();
    void interrupt_handler();
    void stop();
    void enable();
    uint64_t get_keys();
};

extern PS2Keyboard main_ps2keyboard;

