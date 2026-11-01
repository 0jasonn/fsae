#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/fp_compare_api.h"

// Double-precision compares of the soft-float runtime. They read the flags (mrs / msr cpsr) to set or clear the
// overflow bit for unordered operands, which C cannot express, so the bodies are instructions. Arguments: a in r0/r1,
// b in r2/r3 (low word first).

// 0x0200d544: a < b (unordered sets the overflow flag and returns 0).
asm s32 Fp_DoubleLess(u64 a, u64 b) {
    mov ip, #0x200000
    cmn ip, r1, lsl #0x1
    bhs fpl_nan_a
    cmn ip, r3, lsl #0x1
    bhs fpl_nan_b
fpl_ordered:
    orrs ip, r3, r1
    bmi fpl_zero_case
    cmp r1, r3
    cmpeq r0, r2
    movlo r0, #0x1
    movhs r0, #0x0
    bx lr
fpl_unordered:
    mov r0, #0x0
    mrs ip, cpsr
    orr ip, ip, #0x20000000
    msr cpsr_f, ip
    bx lr
fpl_zero_case:
    orr ip, r0, ip, lsl #0x1
    orrs ip, ip, r2
    moveq r0, #0x0
    bne fpl_ordered_2
    mrs ip, cpsr
    orr ip, ip, #0x20000000
    msr cpsr_f, ip
    bxeq lr
fpl_ordered_2:
    cmp r3, r1
    cmpeq r2, r0
    movlo r0, #0x1
    movhs r0, #0x0
    bx lr
fpl_nan_a:
    bne fpl_unordered
    cmp r0, #0x0
    bhi fpl_unordered
    cmn ip, r3, lsl #0x1
    blo fpl_ordered
fpl_nan_b:
    bne fpl_unordered
    cmp r2, #0x0
    bhi fpl_unordered
    b fpl_ordered
}

// 0x0200d5e0: a == b (unordered clears the overflow bit and returns 0).
asm s32 Fp_DoubleEqual(u64 a, u64 b) {
    mov ip, #0x200000
    cmn ip, r1, lsl #0x1
    bhs fpe_nan_a
    cmn ip, r3, lsl #0x1
    bhs fpe_nan_b
fpe_ordered:
    orrs ip, r3, r1
    bmi fpe_zero_case
    cmp r1, r3
    cmpeq r0, r2
    moveq r0, #0x1
    movne r0, #0x0
    bx lr
fpe_unordered:
    mov r0, #0x0
    mrs ip, cpsr
    bic ip, ip, #0x40000000
    msr cpsr_f, ip
    bx lr
fpe_zero_case:
    orr ip, r0, ip, lsl #0x1
    orrs ip, ip, r2
    moveq r0, #0x1
    bxeq lr
    cmp r3, r1
    cmpeq r2, r0
    moveq r0, #0x1
    movne r0, #0x0
    bx lr
fpe_nan_a:
    bne fpe_unordered
    cmp r0, #0x0
    bhi fpe_unordered
    cmn ip, r3, lsl #0x1
    blo fpe_ordered
fpe_nan_b:
    bne fpe_unordered
    cmp r2, #0x0
    bhi fpe_unordered
    b fpe_ordered
}

// 0x0200d66c: a != b (unordered clears the overflow flag and returns 1).
asm s32 Fp_DoubleNotEqual(u64 a, u64 b) {
    mov ip, #0x200000
    cmn ip, r1, lsl #0x1
    bhs fpn_nan_a
    cmn ip, r3, lsl #0x1
    bhs fpn_nan_b
fpn_ordered:
    orrs ip, r3, r1
    bmi fpn_zero_case
    cmp r1, r3
    cmpeq r0, r2
    movne r0, #0x1
    moveq r0, #0x0
    bx lr
fpn_unordered:
    mov r0, #0x1
    mrs ip, cpsr
    bic ip, ip, #0x40000000
    msr cpsr_f, ip
    bx lr
fpn_zero_case:
    orr ip, r0, ip, lsl #0x1
    orrs ip, ip, r2
    moveq r0, #0x0
    bxeq lr
    cmp r3, r1
    cmpeq r2, r0
    movne r0, #0x1
    moveq r0, #0x0
    bx lr
fpn_nan_a:
    bne fpn_unordered
    cmp r0, #0x0
    bhi fpn_unordered
    cmn ip, r3, lsl #0x1
    blo fpn_ordered
fpn_nan_b:
    bne fpn_unordered
    cmp r2, #0x0
    bhi fpn_unordered
    b fpn_ordered
}
