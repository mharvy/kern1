#include "x86_64/print.h"

extern "C" void kernel_start() {
    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    char * str = "Welcome to our 64-bit kernel!";
    print_str(str);
}
