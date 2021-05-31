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

    printk("Initializing IDT...");
    idt = IDT();
    idt.init();
    printk("Done");

    printk("Initializing PIC...");
    pic = PIC();
    pic.init();
    printk("Done");

    printk("Initializing Key Board...");
    main_ps2keyboard.init();
    printk("Done");

    uint16_t irr = pic.get_irr();
    uint16_t isr = pic.get_isr();

    asm volatile (
            "sti"
            :
            :
            : "memory", "cc"
    );
    printk("Interrupts enabled");

    bool a = pic.is_enabled();

    irr = pic.get_irr();
    isr = pic.get_isr();


    while (1) {}

    return;
}

