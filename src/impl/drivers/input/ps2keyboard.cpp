#include "drivers/input/ps2keyboard.h"
#include "drivers/input/scancode.h"
#include "drivers/pic.h"
#include "vga/kputc.h"
#include "util/io.h"

extern "C" void main_ps2keyboard_handler() {
    PS2Keyboard::get_instance().interrupt_handler();
}

PS2Keyboard::PS2Keyboard() {
    scancode = Scancode();
    active = false;
}

PS2Keyboard & PS2Keyboard::get_instance() {
    static PS2Keyboard instance = PS2Keyboard();
    return instance;
}

void PS2Keyboard::init() {
    pic.enable_IRQ(PS2_KEYBOARD_IRQ);
    active = true;
}

void PS2Keyboard::interrupt_handler() {
    pic.send_EOI(PS2_KEYBOARD_IRQ);

    // Update the keys bitmask
    uint8_t index = inb(PS2_KEYBOARD_PORT);
    if (index < NUM_SCANCODES)
        keys |= ((uint64_t)1 << index);
    else if (index > 0x80)
        keys &= ~((uint64_t)1 << (index - 0x80));

    // Update keyboard states
    uint8_t lshift = scancode.get_lshift();
    uint8_t rshift = scancode.get_rshift();
    uint8_t caps = scancode.get_caps();
    // Shift
    shift_pressed = keys & ((uint64_t)1 << lshift) || keys & ((uint64_t)1 << rshift);
    // Caps
    if (keys & ((uint64_t)1 << caps))
        caps_on = !caps_on;

    // For debugging right now
    char c = (char)scancode.get_char(index, shift_pressed, caps_on);
    if (c != '\0')
        kputc(c);
}

void PS2Keyboard::stop() {
}

void PS2Keyboard::enable() {
}

uint64_t PS2Keyboard::get_keys() {
    return keys;
}

