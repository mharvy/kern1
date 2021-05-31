#include "drivers/input/ps2keyboard.h"
#include "drivers/input/scancode.h"
#include "drivers/pic.h"
#include "vga/kputc.h"
#include "util/io.h"

PS2Keyboard main_ps2keyboard;

extern "C" void main_ps2keyboard_handler() {
    main_ps2keyboard.interrupt_handler();
}

PS2Keyboard::PS2Keyboard() {
    active = false;
}

void PS2Keyboard::init() {
    pic.enable_irq(PS2_KEYBOARD_IRQ);
    active = true;
}

void PS2Keyboard::interrupt_handler() {
    pic.send_EOI(PS2_KEYBOARD_IRQ);
    uint8_t scancode = inb(PS2_KEYBOARD_PORT);
    kputc('D');
}

void PS2Keyboard::stop() {
}

void PS2Keyboard::enable() {
}

