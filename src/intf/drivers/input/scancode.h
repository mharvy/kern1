#pragma once

#include <stdint.h>

class Scancode {
public:
    uint8_t * map;
    uint8_t * map_shift;
    uint8_t * map_caps;
    uint8_t * map_shift_caps;

    Scancode();
    Scancode(uint8_t size);
    Scancode(uint8_t size, uint8_t * map, uint8_t * map_shift, uint8_t * map_caps, uint8_t map_shift_caps);
    void change_map(uint8_t position, uint8_t new_char);
};

