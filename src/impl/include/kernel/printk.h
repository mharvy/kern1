#pragma once

#include "vga/kputc.h"

int printk(const char *s, ...) {
    const char * c = s;
    while (*c != '\0')
        kputc(*(c++));
    kputc('\n');
}

