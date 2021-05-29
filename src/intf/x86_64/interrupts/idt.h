#pragma once

#include <stdint.h>

#define IDT_SIZE 256
#define KERNEL_CS 0x08

struct IDTEntry {
    uint16_t offset_1;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t offset_2;
    uint32_t offset_3;
    uint32_t zero;
}__attribute__((packed));

struct IDTDesc {
    uint16_t size;
    uintptr_t location;
}__attribute__((packed));

class IDT {
private:
    IDTEntry table[IDT_SIZE];
    IDTDesc idt_desc;

public:
    IDT();
    void init();
};

extern IDT idt;

