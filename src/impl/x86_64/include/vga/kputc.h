#pragma once

#include "vga/vga.h"

#include <stdint.h>

inline void newline() {
    col = 0;
    if (++row >= NUM_ROWS)
        row--;
}

inline void shift_cursor() {
    if (++col >= NUM_COLS) {
        col = 0;
        if (++row >= NUM_ROWS)
            row--;
    }
}

// Put character on VGA screen
inline void kputc(char c) {
    switch (c) {
        case '\n':
            newline();
            break;
        default:
            *(char *)(VIDEO_MEM + ((NUM_COLS * row + col) << 1)) = c;
            break;
    }
}

