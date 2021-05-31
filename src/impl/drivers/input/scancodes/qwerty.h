#pragma once

#include <stdint.h>

uint8_t _num = 62;
uint8_t * _map = (uint8_t *)"\0\0001234567890-=\0\0qwertyuiop[]\0\0asdfghjkl;\'`\0\\zxcvbnm,./\0\0\0 \0\0\0\0";
uint8_t * _map_shift = (uint8_t *)"\0\0!@#$%^&*()_+\0\0QWERTYUIOP{}\0\0ASDFGHJKL:\"`\0\\ZXCVBNM<>?\0\0\0 \0\0\0\0";
uint8_t * _map_caps = (uint8_t *)"\0\0001234567890-=\0\0QWERTYUIOP{}\0\0ASDFGHJKL;\'`\0\\ZXCVBNM,./\0\0\0 \0\0\0\0";
uint8_t * _map_shift_caps = (uint8_t *)"\0\0!@#$%^&*()_+\0\0qwertyuiop{}\0\0asdfghjkl:\'`\0\\zxcvbnm<>?\0\0\0 \0\0\0\0";
uint8_t _lshift = 42;
uint8_t _rshift = 54;
uint8_t _caps = 58;

