#pragma once

#include <stdint.h>

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

#define ICW1_ICW4 0x01          /* ICW4 (not) needed */
#define ICW1_SINGLE 0x02        /* Single (cascade) mode */
#define ICW1_INTERVAL4 0x04     /* Call address interval 4 (8) */
#define ICW1_LEVEL 0x08         /* Level triggered (edge) mode */
#define ICW1_INIT 0x10          /* Initialization - required! */
 
#define ICW4_8086 0x01          /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO 0x02          /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE 0x08     /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C    /* Buffered mode/master */
#define ICW4_SFNM 0x10          /* Special fully nested (not) */

#define PIC_EOI 0x20
#define PIC_READ_IRR 0x0a
#define PIC_READ_ISR 0x0b

class PIC {
private:
    uint8_t offset1;
    uint8_t offset2;
    uint16_t get_IRQ_reg(uint8_t ocw3);
    uint8_t mask1;
    uint8_t mask2;
public:
    PIC();
    PIC(uint8_t offset1, uint8_t offset2);
    void init();
    void enable_IRQ(uint8_t irq);
    void disable_IRQ(uint8_t irq);
    void send_EOI(uint8_t irq);
    uint16_t get_IRR();
    uint16_t get_ISR();
    bool is_enabled();
};

extern PIC pic;

