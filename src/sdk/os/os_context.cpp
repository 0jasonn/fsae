#include "sdk/os/os_thread.h"
#include "sdk/os/cp_context.h"

// Context save/restore: hand-written ARM in the SDK.
asm u32 OS_SaveContext(register OsThread *context) {
    nofralloc
    stmdb sp!, {r0, lr}
    add r0, r0, #0x48
    ldr r1, =CP_SaveContext
    blx r1
    ldmia sp!, {r0, lr}
    add r1, r0, #0x0
    mrs r2, cpsr
    str r2, [r1], #0x4
    mov r0, #0xd3
    msr cpsr_c, r0
    str sp, [r1, #0x40]
    msr cpsr_c, r2
    mov r0, #0x1
    stmia r1, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, ip, sp, lr}
    add r0, pc, #0x8
    str r0, [r1, #0x3c]
    mov r0, #0x0
    bx lr
}

asm void OS_LoadContext(register OsThread *context) {
    nofralloc
    stmdb sp!, {r0, lr}
    add r0, r0, #0x48
    ldr r1, =CPi_RestoreContext
    blx r1
    ldmia sp!, {r0, lr}
    mrs r1, cpsr
    bic r1, r1, #0x1f
    orr r1, r1, #0xd3
    msr cpsr_c, r1
    ldr r1, [r0], #0x4
    msr spsr_fsxc, r1
    ldr sp, [r0, #0x40]
    ldr lr, [r0, #0x3c]
    ldmia r0, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, ip, sp, lr}^
    mov r0, r0
    stmdb sp!, {r0, r1}
    ldr r0, =0x4000280
L_02017f48:
    ldr r1, [r0, #0x0]
    ands r1, r1, #0x8000
    bne L_02017f48
    ldmia sp!, {r0, r1}
    subs pc, lr, #0x4
}

