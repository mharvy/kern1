#pragma once

#include <stdint.h>

#define NUM_SCANCODES 62

class Scancode {
private:
    uint8_t num;
    uint8_t map[NUM_SCANCODES];
    uint8_t map_shift[NUM_SCANCODES];
    uint8_t map_caps[NUM_SCANCODES];
    uint8_t map_shift_caps[NUM_SCANCODES];
    uint8_t lshift, rshift, caps;

public:
    Scancode();
    Scancode(
            uint8_t size, 
            uint8_t * map, 
            uint8_t * map_shift, 
            uint8_t * map_caps, 
            uint8_t * map_shift_caps, 
            uint8_t lshift, 
            uint8_t rshift, 
            uint8_t caps
    );
    uint8_t get_char(uint8_t index, bool shift_pressed, bool caps_on);
    uint8_t get_lshift();
    uint8_t get_rshift();
    uint8_t get_caps();
};

