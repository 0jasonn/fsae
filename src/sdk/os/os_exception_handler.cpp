#include "sdk/os/os_exception.h"
#include "sdk/os/os_protection.h"

extern u8 data_02129bc4[];
extern u8 data_02129bcc[];

// Exception vector handler and the context capture helpers: hand-written ARM in the SDK.
asm void OSi_ExceptionHandler(void) {
    nofralloc
    ldr ip, =data_02129bc0
    ldr ip, [ip, #0x0]
    cmp ip, #0x0
    movne lr, pc
    bxne ip
    ldr ip, =0x2000000
    stmdb ip!, {r0, r1, r2, r3, sp, lr}
    and r0, sp, #0x1
    mov sp, ip
    mrs r1, cpsr
    and r1, r1, #0x1f
    teq r1, #0x17
    bne L_02018db4
    bl OSi_GetAndDisplayContext
    b L_02018dc0
L_02018db4:
    teq r1, #0x1b
    bne L_02018dc0
    bl OSi_GetAndDisplayContext
L_02018dc0:
    ldr ip, =data_02129bc0
    ldr ip, [ip, #0x0]
    cmp ip, #0x0
L_02018dcc:
    beq L_02018dcc
L_loop:
    mov r0, r0
    b L_loop
    ldmia sp!, {r0, r1, r2, r3, ip, lr}
    mov sp, ip
    bx lr
}

asm void OSi_GetAndDisplayContext(void) {
    nofralloc
    stmdb sp!, {r0, lr}
    bl OSi_SetExContext
    bl func_02018e80
    ldmia sp!, {r0, lr}
    bx lr
}

asm void OSi_SetExContext(void) {
    nofralloc
    ldr r1, =data_02129bf0
    str r0, [r1, #0x6c]
    ldr r0, [ip, #0x0]
    str r0, [r1, #0x4]
    ldr r0, [ip, #0x4]
    str r0, [r1, #0x8]
    ldr r0, [ip, #0x8]
    str r0, [r1, #0xc]
    ldr r0, [ip, #0xc]
    str r0, [r1, #0x10]
    ldr r2, [ip, #0x10]
    bic r2, r2, #0x1
    add r0, r1, #0x14
    stmia r0, {r4, r5, r6, r7, r8, r9, r10, r11}
    ldr r0, [r2, #0x0]
    str r0, [r1, #0x64]
    ldr r3, [r2, #0x4]
    str r3, [r1, #0x0]
    ldr r0, [r2, #0x8]
    str r0, [r1, #0x34]
    ldr r0, [r2, #0xc]
    str r0, [r1, #0x40]
    mrs r0, cpsr
    orr r3, r3, #0x80
    bic r3, r3, #0x20
    msr cpsr_fsxc, r3
    str sp, [r1, #0x38]
    str lr, [r1, #0x3c]
    mrs r2, spsr
    msr cpsr_fsxc, r0
    bx lr
}

asm void func_02018e80(void) {
    nofralloc
    stmdb sp!, {r3, lr}
    ldr r0, =data_02129bc0
    ldr r0, [r0, #0xc]
    cmp r0, #0x0
    ldmeqia sp!, {r3, pc}
    mrs r2, cpsr
    mov r0, sp
    ldr r1, =0x9f
    msr cpsr_fsxc, r1
    mov r1, sp
    mov sp, r0
    stmdb sp!, {r1, r2}
    bl OS_EnableProtectionUnit
    ldr r0, =data_02129bf0
    ldr r1, =data_02129bc4
    ldr r1, [r1, #0x0]
    ldr ip, =data_02129bcc
    ldr ip, [ip, #0x0]
    ldr lr, =L_return
    bx ip
L_return:
    bl OS_DisableProtectionUnit
    ldmia sp!, {r1, r2}
    mov sp, r1
    msr cpsr_fsxc, r2
    ldmia sp!, {r3, pc}
}
