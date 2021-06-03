#include "print.h"
#include "x86_64/interrupts/idt.h"
#include "kernel/printk.h"
#include "drivers/pic.h"
#include "drivers/input/ps2keyboard.h"
#include "drivers/rtc.h"
#include "drivers/pit.h"

IDT idt;
PIC pic;

extern "C" void kernel_start() {
    int testing;

    printk("Starting Kernel 1\n\n");

    printk("Initializing IDT... ");
    idt = IDT();
    idt.init();
    printk("Done\n");

    printk("Initializing PIC... ");
    pic = PIC();
    pic.init();
    printk("Done\n");

    printk("Initializing KeyBoard... ");
    main_ps2keyboard = PS2Keyboard();
    main_ps2keyboard.init();
    printk("Done\n");

    printk("Initializing RTC... ");
    main_rtc = RTC();
    main_rtc.init();
    printk("Done\n");

    printk("Initializing PIT... ");
    main_pit = PIT();
    main_pit.init();
    printk("Done\n");

    asm volatile ("sti");
    printk("Interrupts enabled\n");

    while (1) {}

    return;
}

