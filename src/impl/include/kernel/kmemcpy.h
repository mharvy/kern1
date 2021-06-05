#pragma once

#include <stdint.h>

inline int kmemcpy(void * to, void * from, unsigned int num) {
    uint8_t * to_c = (uint8_t *)to;
    uint8_t * from_c = (uint8_t *)from;
    while (num--) {
        *to_c = *from_c;
        to_c++;
        from_c++;
    }
    return 0;
}

