global main_rtc_linkage
extern main_rtc_handler

section .text
bits 64

main_rtc_linkage:
    cli
    call main_rtc_handler
    sti
    iretq

