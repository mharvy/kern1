#pragma once

#include "vga/vga.h"

#include <stdint.h>

void newline() {
    col = 0;
    if (++row >= NUM_ROWS)
        row--;
}

void shift_cursor() {
    if (++col >= NUM_COLS) {
        col = 0;
        if (++row >= NUM_ROWS)
            row--;
    }
}

// Put character on VGA screen
void kputc(char c) {
    switch (c) {
        case '\n':
            newline();
            break;
        default:
            *(char *)(VIDEO_MEM + ((NUM_COLS * row + col) << 1)) = c;
            shift_cursor();
            break;
    }
}

