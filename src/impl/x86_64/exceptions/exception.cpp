#include "x86_64/exceptions/exception.h"
#include "kernel/printk.h"
#include "strings.h"

void * exceptions[NUM_EXCEPTIONS] = {
    (void *)&divide_by_zero,
    (void *)&debug,
    (void *)&non_maskable_interrupt,
    (void *)&breakpoint,
    (void *)&overflow,
    (void *)&bound_range_exceeded,
    (void *)&invalid_opcode,
    (void *)&device_not_available,
    (void *)&double_fault,
    (void *)&coprocessor_segment_overrun,
    (void *)&invalid_tss,
    (void *)&segment_not_present,
    (void *)&stack_segment_fault,
    (void *)&general_protection_fault,
    (void *)&page_fault,
    (void *)nullptr,
    (void *)&floating_point_exception,
    (void *)&alignment_check,
    (void *)&machine_check,
    (void *)&simd_floating_point_exception,
    (void *)&virtualization_exception,
    (void *)nullptr,
    (void *)nullptr,
    (void *)nullptr,
    (void *)nullptr,
    (void *)nullptr,
    (void *)nullptr,
    (void *)nullptr,
    (void *)nullptr,
    (void *)nullptr,
    (void *)&security_exception,
    (void *)nullptr,
};

const char * exception_messages[NUM_EXCEPTIONS] = {
    "Divide by Zero", "Debug", "NMI", "Breakpoint", "Overflow", 
    "Bound Range Exceeded", "Invalid Opcode", "Device Not Available",
    "Double Fault", "Coprocessor Segment Overrun", "Invalid TSS", 
    "Segment Not Present", "Stack Fault", "General Protection", 
    "Page-Fault", nullptr, "x87 FPU Floating-Point Error", "Aligment Check", 
    "Machine Check", "SIMD Floating Point Error", "Virtualization", 
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
    nullptr, nullptr, "Security"
};

// Handlers
EXCEPTION(divide_by_zero, 0, false);
EXCEPTION(debug, 1, false);
EXCEPTION(non_maskable_interrupt, 2, false);
EXCEPTION(breakpoint, 3, false);
EXCEPTION(overflow, 4, false);
EXCEPTION(bound_range_exceeded, 5, false);
EXCEPTION(invalid_opcode, 6, false);
EXCEPTION(device_not_available, 7, false);
EXCEPTION(double_fault, 8, true);
EXCEPTION(coprocessor_segment_overrun, 9, false);
EXCEPTION(invalid_tss, 10, true);
EXCEPTION(segment_not_present, 11, true);
EXCEPTION(stack_segment_fault, 12, true);
EXCEPTION(general_protection_fault, 13, true);
EXCEPTION(page_fault, 14, true);
EXCEPTION(floating_point_exception, 16, false);
EXCEPTION(alignment_check, 17, true);
EXCEPTION(machine_check, 18, false);
EXCEPTION(simd_floating_point_exception, 19, false);
EXCEPTION(virtualization_exception, 20, false);
EXCEPTION(security_exception, 30, true);

