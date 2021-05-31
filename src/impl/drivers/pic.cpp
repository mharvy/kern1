#include "drivers/pic.h"
#include "util/io.h"

#include <stdint.h>

PIC::PIC() {
    offset1 = 0x20;
    offset2 = 0x28;
}

PIC::PIC(uint8_t offset1, uint8_t offset2) : offset1(offset1), offset2(offset2) {}

void PIC::init() {
    uint8_t a1, a2;  // Saved masks

    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC1_DATA, offset1);
    io_wait();
    outb(PIC2_DATA, offset2);
    io_wait();
    outb(PIC1_DATA, 4);
    io_wait();
    outb(PIC2_DATA, 2);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    //outb(PIC1_DATA, a1);
    //outb(PIC2_DATA, a2);
    outb(PIC1_DATA, 0xfb);
    outb(PIC2_DATA, 0xff);
}

// Unmask the specific IRQ
void PIC::enable_irq(uint8_t irq) {
    uint16_t port;
    uint8_t value;

    if (irq < 8)
        port = PIC1_DATA;
    else {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = inb(port) & ~(1 << irq);
    outb(port, value);
}

// Mask the specific IRQ
void PIC::disable_irq(uint8_t irq) {
    uint16_t port;
    uint8_t value;

    if (irq < 8)
        port = PIC1_DATA;
    else {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = inb(port) | (1 << irq);
    outb(port, value);
}

void PIC::send_EOI(uint8_t irq) {
    if (irq >= 8)
        outb(PIC2_COMMAND, PIC_EOI);

    outb(PIC1_COMMAND, PIC_EOI);
}

uint16_t PIC::get_irq_reg(uint8_t ocw3) {
    outb(PIC1_COMMAND, ocw3);
    outb(PIC2_COMMAND, ocw3);
    return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}

uint16_t PIC::get_irr() {
    return get_irq_reg(PIC_READ_IRR);
}

uint16_t PIC::get_isr() {
    return get_irq_reg(PIC_READ_ISR);
}

bool PIC::is_enabled() {
    uint64_t flags;
    asm volatile (
            "pushf\n\t"
            "pop %0"
            : "=g"(flags)
    );
    return flags & (1 << 9);
}

