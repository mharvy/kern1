#pragma once

#include <stdint.h>

template <typename T1, typename T2>
uint32_t kstrcpy(T1 to, T2 from) {
    char * f = (char *)from;
    char * t = (char *)to;
    uint32_t i = 0;

    while (f[i] != '\0' && i < (uint32_t)0xFFFFFFFF) {
        t[i] = f[i];
        i++;
    }

    return i;
}

