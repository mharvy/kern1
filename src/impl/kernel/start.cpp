#include "x86_64/interrupts/idt.h"
#include "kernel/printk.h"
#include "drivers/pic.h"
#include "drivers/input/ps2keyboard.h"
#include "drivers/timer/rtc.h"
#include "drivers/timer/pit.h"
#include "util/cpuinfo.h"
#include "vga/kputc.h"

#include <stdint.h>

IDT idt;
PIC pic;

extern "C" void kernel_start() {
    int testing;

    printk("Starting Kernel 1\n\n");

    // Get some cpu information
    printk("CPU:\n");
    uint32_t regs[4];

    // Vendor name
    printk("  Vendor: ");
    uint8_t vendor[13];
    cpuid_string(CPUID_GETVENDORSTRING, vendor);
    printk((char *)vendor);
    printk("\n");

    // Long mode?
    printk("  Long mode: ");
    if (cpuid(0x80000001U, regs)) {
        if (regs[3] & (1 << 29))
            printk("True");
        else
            printk("False");
    }
    else
        printk("False");
    printk("\n");

    // Address sizes
    printk("  Address size (phys/virt): ");
    if (cpuid(0x80000008U, regs)) {
        kputc(regs[0] & 0xFF);
        kputc('\\');
        kputc((regs[0] & 0xFF00) >> 8);
    }
    printk("\n");

    // Core count
    printk("  Core quantity: ");
    if (cpuid(0x80000008U, regs)) {
        kputc((regs[2] & 0xFF) + 1 + '0');
    }
    printk("\n");

    // Has an apic?
    printk("  Has APIC?: ");
    if (cpuid(0x80000001U, regs)) {
        if (regs[3] & (1 << 9))
            printk("yes");
        else
            printk("no");
    }
    printk("\n");

    printk("Initializing IDT... ");
    idt = IDT();
    idt.init();
    printk("Done\n");

    printk("Initializing PIC... ");
    pic = PIC();
    pic.init();
    printk("Done\n");

    printk("Initializing KeyBoard... ");
    PS2Keyboard::get_instance().init();
    printk("Done\n");

    printk("Initializing RTC... ");
    RTC::get_instance().init();
    printk("Done\n");

    printk("Initializing PIT... ");
    PIT::get_instance().init();
    printk("Done\n");

    asm volatile ("sti");
    printk("Interrupts enabled\n");

    while (1) {}

    return;
}

