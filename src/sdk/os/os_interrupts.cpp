#include "global.h"
#include "types.h"
#include "sdk/os/os_interrupts.h"

// CPSR I-bit (0x80) and I+F-bit (0xc0) helpers. Each returns the previous masked bits, and each Restore takes such a value.

asm u32 OS_EnableInterrupts(void) {
    mrs r0, cpsr
    bic r1, r0, #0x80
    msr cpsr_c, r1
    and r0, r0, #0x80
    bx lr
}

asm u32 OS_DisableInterrupts(void) {
    mrs r0, cpsr
    orr r1, r0, #0x80
    msr cpsr_c, r1
    and r0, r0, #0x80
    bx lr
}

asm u32 OS_RestoreInterrupts(u32 state) {
    mrs r1, cpsr
    bic r2, r1, #0x80
    orr r2, r2, r0
    msr cpsr_c, r2
    and r0, r1, #0x80
    bx lr
}

asm u32 OS_DisableInterrupts_IrqAndFiq(void) {
    mrs r0, cpsr
    orr r1, r0, #0xc0
    msr cpsr_c, r1
    and r0, r0, #0xc0
    bx lr
}

asm u32 OS_RestoreInterrupts_IrqAndFiq(u32 state) {
    mrs r1, cpsr
    bic r2, r1, #0xc0
    orr r2, r2, r0
    msr cpsr_c, r2
    and r0, r1, #0xc0
    bx lr
}

asm u32 OS_GetCpsrIrq(void) {
    mrs r0, cpsr
    and r0, r0, #0x80
    bx lr
}

asm u32 OS_GetProcMode(void) {
    mrs r0, cpsr
    and r0, r0, #0x1f
    bx lr
}

// Busy loop: 4 cycles per iteration.
asm void OS_SpinWaitCpuCycles(u32 cycles) {
@loop:
    subs r0, r0, #4
    bhs @loop
    bx lr
}
