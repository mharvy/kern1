#include "x86_64/print.h"
#include "x86_64/interrupts/idt.h"

IDT idt;

extern "C" void kernel_start() {
    int testing;

    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    char * str = "Welcome to our 64-bit kernel!";
    print_str(str);

    idt = IDT();
    idt.init();
    testing = 8 / 0;
    return;
}

