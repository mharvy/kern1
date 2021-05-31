#pragma once

#include "vga/kputc.h"

inline int printk(const char *s, ...) {
    const char * c = s;
    while (*c != '\0')
        kputc(*(c++));
    return 0;
}

