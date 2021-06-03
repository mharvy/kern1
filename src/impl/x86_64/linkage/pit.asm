global main_pit_linkage
extern main_pit_handler

section .text
bits 64

main_pit_linkage:
    cli
    call main_pit_handler
    sti
    iretq

