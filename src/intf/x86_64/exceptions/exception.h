#pragma once

#include <stdint.h>

#define NUM_EXCEPTIONS 32

#define EXCEPTION_DECLARE(exception)                \
void exception();                                   \

#define EXCEPTION(exception, number, error_code)    \
void exception() {                                  \
    print_str("EXCEPTION: ");                       \
    print_str(exception_messages[number]);\
    while (1) {};                                   \
}                                                   \

extern void * exceptions[];
extern char * exception_messages[];

EXCEPTION_DECLARE(divide_by_zero);
EXCEPTION_DECLARE(debug);
EXCEPTION_DECLARE(non_maskable_interrupt);
EXCEPTION_DECLARE(breakpoint);
EXCEPTION_DECLARE(overflow);
EXCEPTION_DECLARE(bound_range_exceeded);
EXCEPTION_DECLARE(invalid_opcode);
EXCEPTION_DECLARE(device_not_available);
EXCEPTION_DECLARE(double_fault);
EXCEPTION_DECLARE(coprocessor_segment_overrun);
EXCEPTION_DECLARE(invalid_tss);
EXCEPTION_DECLARE(segment_not_present);
EXCEPTION_DECLARE(stack_segment_fault);
EXCEPTION_DECLARE(general_protection_fault);
EXCEPTION_DECLARE(page_fault);
EXCEPTION_DECLARE(floating_point_exception);
EXCEPTION_DECLARE(alignment_check);
EXCEPTION_DECLARE(machine_check);
EXCEPTION_DECLARE(simd_floating_point_exception);
EXCEPTION_DECLARE(virtualization_exception);
EXCEPTION_DECLARE(security_exception);
EXCEPTION_DECLARE(triple_fault);
EXCEPTION_DECLARE(fpu_error_interrupt);

