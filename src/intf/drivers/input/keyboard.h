#pragma once

#include "drivers/input/scancode.h"

class Keyboard {
private:
    bool active = false;
    Scancode scancode;

public:
    Keyboard();
    void init();
    void interrupt_handler();
    void stop();
    void enable();
};

