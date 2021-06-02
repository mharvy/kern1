global main_ps2keyboard_linkage
extern main_ps2keyboard_handler

section .text
bits 64

main_ps2keyboard_linkage:
    cli
    call main_ps2keyboard_handler
    sti
    iretq

