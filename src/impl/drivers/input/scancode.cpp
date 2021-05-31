#include "drivers/input/scancode.h"
#include "scancodes/qwerty.h"
#include "kernel/kmemcpy.h"

#include <stdint.h>

Scancode::Scancode(uint8_t num, uint8_t * map, uint8_t * map_shift, uint8_t * map_caps, uint8_t * map_shift_caps, uint8_t lshift, uint8_t rshift, uint8_t caps) {
    if (num > NUM_SCANCODES)
        return;

    this->num = num;
    kmemcpy(this->map, map, num);
    kmemcpy(this->map_shift, map_shift, num);
    kmemcpy(this->map_caps, map_caps, num);
    kmemcpy(this->map_shift_caps, map_shift_caps, num);
    this->lshift = lshift;
    this->rshift = rshift;
    this->caps = caps;
}

Scancode::Scancode() {
    if (_num > NUM_SCANCODES)
        return;

    this->num = _num;
    kmemcpy(this->map, _map, _num);
    kmemcpy(this->map_shift, _map_shift, _num);
    kmemcpy(this->map_caps, _map_caps, _num);
    kmemcpy(this->map_shift_caps, _map_shift_caps, _num);
    this->lshift = _lshift;
    this->rshift = _rshift;
    this->caps = _caps;
}


uint8_t Scancode::get_char(uint8_t index, bool shift_pressed, bool caps_on) {
    if (index >= num)
        return (uint8_t)'\0';

    if (shift_pressed && caps_on)
        return map_shift_caps[index];
    else if (shift_pressed)
        return map_shift[index];
    else if (caps_on)
        return map_caps[index];
    else
        return map[index];
}

uint8_t Scancode::get_lshift() {
    return lshift;
}

uint8_t Scancode::get_rshift() {
    return rshift;
}

uint8_t Scancode::get_caps() {
    return caps;
}

