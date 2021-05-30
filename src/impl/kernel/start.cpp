#include "print.h"
#include "x86_64/interrupts/idt.h"
#include "kernel/printk.h"

IDT idt;

extern "C" void kernel_start() {
    int testing;

    printk("Starting Kernel 1");
    printk("This should be on a new line");
    printk("SO SHOULD THIS!");
    printk("dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");

    idt = IDT();
    idt.init();
    return;
}

