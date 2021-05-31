#pragma once

#include "drivers/input/scancode.h"

extern "C" void main_ps2keyboard_handler();
extern "C" void ps2keyboard_linkage();

class PS2Keyboard {
private:
    bool active = false;
    Scancode scancode;

public:
    PS2Keyboard();
    void init();
    void interrupt_handler();
    void stop();
    void enable();
};

extern PS2Keyboard main_ps2keyboard;

