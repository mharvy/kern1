#pragma once

static inline __printf(1, 2) __cold
int printk(const char *s, ...) {
    return 0;
}

