#include "print.h"
#include "x86_64/interrupts/idt.h"

IDT idt;

extern "C" void kernel_start() {
    int testing;

    print_clear();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLUE);
    char * str = "Starting Kernel 1";
    print_str(str);
    //printk(str);

    idt = IDT();
    idt.init();
    testing = 8 / 0;
    return;
}

