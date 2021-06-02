#include "drivers/pic.h"
#include "util/io.h"

#include <stdint.h>

// This represents cascading PIC system
PIC::PIC() {
    offset1 = 0x20;
    offset2 = 0x28;
    mask1 = 0xFB;  // When we init, make sure pic2 can send pic1 interrupts
    mask2 = 0xFF;  // Pic2 has not enabled irq lines
}

PIC::PIC(uint8_t offset1, uint8_t offset2) : offset1(offset1), offset2(offset2) {}

void PIC::init() {
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
}

// Unmask the specific IRQ
void PIC::enable_IRQ(uint8_t irq) {
    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC1_DATA;
        mask1 = mask1 & ~(1 << irq);
        outb(port, mask1);
    }
    else {
        port = PIC2_DATA;
        irq -= 8;
        mask2 = mask2 & ~(1 << irq);
        outb(port, mask2);
    }
}

// Mask the specific IRQ
void PIC::disable_IRQ(uint8_t irq) {
    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC1_DATA;
        mask1 = mask1 | (1 << irq);
        outb(port, mask1);
    }
    else {
        port = PIC2_DATA;
        irq -= 8;
        mask2 = mask2 | (1 << irq);
        outb(port, mask2);
    }
}

void PIC::send_EOI(uint8_t irq) {
    if (irq >= 8)
        outb(PIC2_COMMAND, PIC_EOI);

    outb(PIC1_COMMAND, PIC_EOI);
}

uint16_t PIC::get_IRQ_reg(uint8_t ocw3) {
    outb(PIC1_COMMAND, ocw3);
    outb(PIC2_COMMAND, ocw3);
    return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}

uint16_t PIC::get_IRR() {
    return get_IRQ_reg(PIC_READ_IRR);
}

uint16_t PIC::get_ISR() {
    return get_IRQ_reg(PIC_READ_ISR);
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

