#include "sdk/mi/mi_dma.h"
#include "sdk/mi/mi_memory.h"
#include "sdk/mi/dma_conflict_api.h"

// MI memory fill/copy helpers. The Cpu* routines are hand-written ARM in the SDK (asm blocks).

void MI_HBlankDmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size) {
    Dma_CheckConflict(dmaNo, 0x10000000);
    Region_CheckNotIoOrRom(dmaNo, (u32)src, size, 0);
    if (size == 0) {
        return;
    }
    MI_WaitDma(dmaNo);
    func_01ff8020(dmaNo, (u32)src, (u32)dest, (size >> 1) | 0x92600000, 0);
}

asm void MIi_CpuClear16(register u16 data, register void *dest, register u32 size) {
    mov r3, #0
L1:
    cmp r3, r2
    strlth r0, [r1, r3]
    addlt r3, r3, #2
    blt L1
    bx lr
}

asm void MIi_CpuCopy16(register const void *src, register void *dest, register u32 size) {
    mov ip, #0
L1:
    cmp ip, r2
    ldrlth r3, [r0, ip]
    strlth r3, [r1, ip]
    addlt ip, ip, #2
    blt L1
    bx lr
}

asm void OSi_CpuClear32(register u32 data, register void *dest, register u32 size) {
    add ip, r1, r2
L1:
    cmp r1, ip
    stmltia r1!, {r0}
    blt L1
    bx lr
}

asm void MIi_CpuCopy32(register const void *src, register void *dest, register u32 size) {
    add ip, r1, r2
L1:
    cmp r1, ip
    ldmltia r0!, {r2}
    stmltia r1!, {r2}
    blt L1
    bx lr
}

asm void MIi_CpuClearFast(register u32 data, register void *dest, register u32 size) {
    nofralloc
    stmdb sp!, {r4, r5, r6, r7, r8, r9}
    add r9, r1, r2
    mov ip, r2, lsr #5
    add ip, r1, ip, lsl #5
    mov r2, r0
    mov r3, r2
    mov r4, r2
    mov r5, r2
    mov r6, r2
    mov r7, r2
    mov r8, r2
L1:
    cmp r1, ip
    stmltia r1!, {r0, r2, r3, r4, r5, r6, r7, r8}
    blt L1
L2:
    cmp r1, r9
    stmltia r1!, {r0}
    blt L2
    ldmia sp!, {r4, r5, r6, r7, r8, r9}
    bx lr
}

asm void MIi_CpuCopyFast(register const void *src, register void *dest, register u32 size) {
    nofralloc
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10}
    add r10, r1, r2
    mov ip, r2, lsr #5
    add ip, r1, ip, lsl #5
L1:
    cmp r1, ip
    ldmltia r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
    stmltia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
    blt L1
L2:
    cmp r1, r10
    ldmltia r0!, {r2}
    stmltia r1!, {r2}
    blt L2
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10}
    bx lr
}

asm void MI_CpuFill8(register void *dest, register u8 data, register u32 size) {
    nofralloc
    cmp r2, #0x0
    bxeq lr
    tst r0, #0x1
    beq L_02015bc0
    ldrh ip, [r0, #-0x1]
    and ip, ip, #0xff
    orr r3, ip, r1, lsl #0x8
    strh r3, [r0, #-0x1]
    add r0, r0, #0x1
    subs r2, r2, #0x1
    bxeq lr
L_02015bc0:
    cmp r2, #0x2
    blo L_02015c08
    orr r1, r1, r1, lsl #0x8
    tst r0, #0x2
    beq L_02015be0
    strh r1, [r0], #0x2
    subs r2, r2, #0x2
    bxeq lr
L_02015be0:
    orr r1, r1, r1, lsl #0x10
    bics r3, r2, #0x3
    beq L_02015c00
    sub r2, r2, r3
    add ip, r3, r0
L_02015bf4:
    str r1, [r0], #0x4
    cmp r0, ip
    blo L_02015bf4
L_02015c00:
    tst r2, #0x2
    strneh r1, [r0], #0x2
L_02015c08:
    tst r2, #0x1
    bxeq lr
    ldrh r3, [r0, #0x0]
    and r3, r3, #0xff00
    and r1, r1, #0xff
    orr r1, r1, r3
    strh r1, [r0, #0x0]
    bx lr
}
asm void MI_CpuFill(register void *dest, register u32 data, register u32 size) {
    nofralloc
    cmp r2, #0x0
    bxeq lr
    cmp r2, #0x8
    bgt L_02015c68
    rsb r3, r2, #0x8
    add pc, pc, r3, lsl #0x2
    mov r0, r0
    strb r1, [r0], #0x1
    strb r1, [r0], #0x1
    strb r1, [r0], #0x1
    strb r1, [r0], #0x1
    strb r1, [r0], #0x1
    strb r1, [r0], #0x1
    strb r1, [r0], #0x1
    strb r1, [r0], #0x1
    bx lr
L_02015c68:
    orr r1, r1, r1, lsl #0x8
    orr r1, r1, r1, lsl #0x10
    tst r0, #0x1
    subne r2, r2, #0x1
    strneb r1, [r0], #0x1
    tst r0, #0x2
    subne r2, r2, #0x2
    strneh r1, [r0], #0x2
    tst r0, #0x4
    subne r2, r2, #0x4
    strne r1, [r0], #0x4
    cmp r2, #0x20
    blt L_02015cd4
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10}
    mov r4, r1
    mov r5, r1
    mov r6, r1
    mov r7, r1
    mov r8, r1
    mov r9, r1
    mov r10, r1
    subs r2, r2, #0x20
L_02015cc0:
    stmgeia r0!, {r1, r4, r5, r6, r7, r8, r9, r10}
    subges r2, r2, #0x20
    bge L_02015cc0
    add r2, r2, #0x20
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10}
L_02015cd4:
    cmp r2, #0x4
    blt L_02015cf0
    subs r2, r2, #0x4
L_02015ce0:
    strge r1, [r0], #0x4
    subs r2, r2, #0x4
    bge L_02015ce0
    add r2, r2, #0x4
L_02015cf0:
    subs r2, r2, #0x1
    strgeb r1, [r0], #0x1
    subges r2, r2, #0x1
    strgeb r1, [r0], #0x1
    subges r2, r2, #0x1
    strgeb r1, [r0], #0x1
    bx lr
}
asm void MI_CpuCopy8(register const void *src, register void *dest, register u32 size) {
    nofralloc
    cmp r2, #0x0
    bxeq lr
    tst r1, #0x1
    beq L_02015d4c
    ldrh ip, [r1, #-0x1]
    and ip, ip, #0xff
    tst r0, #0x1
    ldrneh r3, [r0, #-0x1]
    movne r3, r3, lsr #0x8
    ldreqh r3, [r0, #0x0]
    orr r3, ip, r3, lsl #0x8
    strh r3, [r1, #-0x1]
    add r0, r0, #0x1
    add r1, r1, #0x1
    subs r2, r2, #0x1
    bxeq lr
L_02015d4c:
    eor ip, r1, r0
    tst ip, #0x1
    beq L_02015da0
    bic r0, r0, #0x1
    ldrh ip, [r0], #0x2
    mov r3, ip, lsr #0x8
    subs r2, r2, #0x2
    blo L_02015d84
L_02015d6c:
    ldrh ip, [r0], #0x2
    orr ip, r3, ip, lsl #0x8
    strh ip, [r1], #0x2
    mov r3, ip, lsr #0x10
    subs r2, r2, #0x2
    bhs L_02015d6c
L_02015d84:
    tst r2, #0x1
    bxeq lr
    ldrh ip, [r1, #0x0]
    and ip, ip, #0xff00
    orr ip, ip, r3
    strh ip, [r1, #0x0]
    bx lr
L_02015da0:
    tst ip, #0x2
    beq L_02015dcc
    bics r3, r2, #0x1
    beq L_02015e18
    sub r2, r2, r3
    add ip, r3, r1
L_02015db8:
    ldrh r3, [r0], #0x2
    strh r3, [r1], #0x2
    cmp r1, ip
    blo L_02015db8
    b L_02015e18
L_02015dcc:
    cmp r2, #0x2
    blo L_02015e18
    tst r1, #0x2
    beq L_02015dec
    ldrh r3, [r0], #0x2
    strh r3, [r1], #0x2
    subs r2, r2, #0x2
    bxeq lr
L_02015dec:
    bics r3, r2, #0x3
    beq L_02015e0c
    sub r2, r2, r3
    add ip, r3, r1
L_02015dfc:
    ldr r3, [r0], #0x4
    str r3, [r1], #0x4
    cmp r1, ip
    blo L_02015dfc
L_02015e0c:
    tst r2, #0x2
    ldrneh r3, [r0], #0x2
    strneh r3, [r1], #0x2
L_02015e18:
    tst r2, #0x1
    bxeq lr
    ldrh r2, [r1, #0x0]
    ldrh r0, [r0, #0x0]
    and r2, r2, #0xff00
    and r0, r0, #0xff
    orr r0, r2, r0
    strh r0, [r1, #0x0]
    bx lr
}
