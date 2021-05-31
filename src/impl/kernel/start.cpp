#include "print.h"
#include "x86_64/interrupts/idt.h"
#include "kernel/printk.h"
#include "drivers/pic.h"
#include "drivers/input/ps2keyboard.h"

IDT idt;
PIC pic;

extern "C" void kernel_start() {
    int testing;

    printk("Starting Kernel 1");

    printk("Initializing IDT... ");
    idt = IDT();
    idt.init();
    printk("Done\n");

    printk("Initializing PIC... ");
    pic = PIC();
    pic.init();
    printk("Done\n");

    printk("Initializing Key Board... ");
    main_ps2keyboard = PS2Keyboard();
    main_ps2keyboard.init();
    printk("Done\n");

    uint16_t irr = pic.get_IRR();
    uint16_t isr = pic.get_ISR();

    asm volatile (
            "sti"
            :
            :
            : "memory", "cc"
    );
    printk("Interrupts enabled\n");

    bool a = pic.is_enabled();

    irr = pic.get_IRR();
    isr = pic.get_ISR();

    while (1) {}

    return;
}

