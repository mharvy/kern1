#include "x86_64/interrupts/idt.h"
#include "x86_64/exceptions/exception.h"
#include "x86_64/print.h"

#include <stdint.h>

#define SET_IDT_ENTRY(str, handler)                                             \
do {                                                                            \
    str->offset_1 = (uint16_t)((uint64_t)handler & 0xFFFF);                     \
    str->offset_2 = (uint16_t)(((uint64_t)handler & 0xFFFF0000) >> 16);         \
    str->offset_3 = (uint32_t)(((uint64_t)handler & 0xFFFFFFFF00000000) >> 32); \
} while (0);

void set_trap_gate(IDTEntry * entry, void * func) {
    SET_IDT_ENTRY(entry, func);
    entry->selector = KERNEL_CS;
    entry->ist = 0x00;
    entry->type_attr = 0x8f;  // Present, DPL=0, ss=0, gate type = 15 (trap gate)
    entry->zero = 0x00000000;
}

IDT::IDT() {
    // Set up IDT Descriptor
    this->idt_desc.size = sizeof(IDTEntry) * IDT_SIZE;
    this->idt_desc.location = (uintptr_t)(this->table);

    // Exceptions
    for (int i = 0x00; i < 0x20; i++)
        set_trap_gate(&this->table[i], exceptions[i]);

    // Interrupts
    //for (int i = 0x20; i < 0xFF; i++)
    //    set_interrupt_gate(this->table[i] , interrupts[i]);

    // System calls
    //set_trap_gate(this->table[0x80], syscall_linkage);
}

void IDT::init() {
    asm volatile (
            "lidt (%0);"
                :
                : "r" (&this->idt_desc)
    );
    return;
}

