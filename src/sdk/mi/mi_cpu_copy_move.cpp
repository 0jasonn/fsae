#include "sdk/mi/mi_memory.h"

// MI_CpuCopy and MI_CpuMove are hand-written assembly. Their real extent is larger than the symbols.txt sizes (0xa4 and
// 0xbc): MI_CpuCopy is 0x2f0 bytes (0x02015e3c-0x0201612c), MI_CpuMove 0x314 bytes (0x0201612c-0x02016440); the four
// 32-byte-block loops for each source/destination misalignment are part of them.
asm void MI_CpuCopy(register const void *src, register void *dest, register u32 size) {
    nofralloc
    cmp r2, #0x8
    bgt L_02015e94
    rsb r3, r2, #0x8
    add pc, pc, r3, lsl #0x3
    mov r0, r0
    ldrb r3, [r0], #0x1
    strb r3, [r1], #0x1
    ldrb r3, [r0], #0x1
    strb r3, [r1], #0x1
    ldrb r3, [r0], #0x1
    strb r3, [r1], #0x1
    ldrb r3, [r0], #0x1
    strb r3, [r1], #0x1
    ldrb r3, [r0], #0x1
    strb r3, [r1], #0x1
    ldrb r3, [r0], #0x1
    strb r3, [r1], #0x1
    ldrb r3, [r0], #0x1
    strb r3, [r1], #0x1
    ldrb r3, [r0], #0x1
    strb r3, [r1], #0x1
    bx lr
L_02015e94:
    tst r0, #0x1
    subne r2, r2, #0x1
    ldrneb r3, [r0], #0x1
    strneb r3, [r1], #0x1
    tst r0, #0x2
    subne r2, r2, #0x2
    ldrneb r3, [r0], #0x1
    strneb r3, [r1], #0x1
    ldrneb r3, [r0], #0x1
    strneb r3, [r1], #0x1
    and r3, r1, #0x3
    bic r1, r1, #0x3
    cmp r3, #0x0
    beq L_02015ee0
    cmp r3, #0x1
    beq L_02015f1c
    cmp r3, #0x2
    beq L_02015fb4
    b L_0201604c
L_02015ee0:
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x20
L_02015ee8:
    ldmgeia r0!, {r4, r5, r6, r7, r8, r9, r10, lr}
    stmgeia r1!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subges r2, r2, #0x20
    bge L_02015ee8
    add r2, r2, #0x20
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x4
L_02015f04:
    ldrge r3, [r0], #0x4
    strge r3, [r1], #0x4
    subges r2, r2, #0x4
    bge L_02015f04
    add r2, r2, #0x4
    b L_020160e4
L_02015f1c:
    ldr ip, [r1]
    mov ip, ip, lsl #0x18
    mov ip, ip, lsr #0x18
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x20
L_02015f30:
    ldmgeia r0!, {r4, r5, r6, r7, r8, r9, r10, lr}
    movge r3, r4, lsr #0x18
    orrge r4, ip, r4, lsl #0x8
    movge ip, r5, lsr #0x18
    orrge r5, r3, r5, lsl #0x8
    movge r3, r6, lsr #0x18
    orrge r6, ip, r6, lsl #0x8
    movge ip, r7, lsr #0x18
    orrge r7, r3, r7, lsl #0x8
    movge r3, r8, lsr #0x18
    orrge r8, ip, r8, lsl #0x8
    movge ip, r9, lsr #0x18
    orrge r9, r3, r9, lsl #0x8
    movge r3, r10, lsr #0x18
    orrge r10, ip, r10, lsl #0x8
    movge ip, lr, lsr #0x18
    orrge lr, r3, lr, lsl #0x8
    stmgeia r1!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subges r2, r2, #0x20
    bge L_02015f30
    add r2, r2, #0x20
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x4
L_02015f8c:
    ldrge r3, [r0], #0x4
    orrge ip, ip, r3, lsl #0x8
    strge ip, [r1], #0x4
    movge ip, r3, lsr #0x18
    subges r2, r2, #0x4
    bge L_02015f8c
    add r2, r2, #0x4
    sub r0, r0, #0x1
    add r2, r2, #0x1
    b L_020160e4
L_02015fb4:
    ldr ip, [r1]
    mov ip, ip, lsl #0x10
    mov ip, ip, lsr #0x10
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x20
L_02015fc8:
    ldmgeia r0!, {r4, r5, r6, r7, r8, r9, r10, lr}
    movge r3, r4, lsr #0x10
    orrge r4, ip, r4, lsl #0x10
    movge ip, r5, lsr #0x10
    orrge r5, r3, r5, lsl #0x10
    movge r3, r6, lsr #0x10
    orrge r6, ip, r6, lsl #0x10
    movge ip, r7, lsr #0x10
    orrge r7, r3, r7, lsl #0x10
    movge r3, r8, lsr #0x10
    orrge r8, ip, r8, lsl #0x10
    movge ip, r9, lsr #0x10
    orrge r9, r3, r9, lsl #0x10
    movge r3, r10, lsr #0x10
    orrge r10, ip, r10, lsl #0x10
    movge ip, lr, lsr #0x10
    orrge lr, r3, lr, lsl #0x10
    stmgeia r1!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subges r2, r2, #0x20
    bge L_02015fc8
    add r2, r2, #0x20
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x4
L_02016024:
    ldrge r3, [r0], #0x4
    orrge ip, ip, r3, lsl #0x10
    strge ip, [r1], #0x4
    movge ip, r3, lsr #0x10
    subges r2, r2, #0x4
    bge L_02016024
    add r2, r2, #0x4
    sub r0, r0, #0x2
    add r2, r2, #0x2
    b L_020160e4
L_0201604c:
    ldr ip, [r1]
    mov ip, ip, lsl #0x8
    mov ip, ip, lsr #0x8
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x20
L_02016060:
    ldmgeia r0!, {r4, r5, r6, r7, r8, r9, r10, lr}
    movge r3, r4, lsr #0x8
    orrge r4, ip, r4, lsl #0x18
    movge ip, r5, lsr #0x8
    orrge r5, r3, r5, lsl #0x18
    movge r3, r6, lsr #0x8
    orrge r6, ip, r6, lsl #0x18
    movge ip, r7, lsr #0x8
    orrge r7, r3, r7, lsl #0x18
    movge r3, r8, lsr #0x8
    orrge r8, ip, r8, lsl #0x18
    movge ip, r9, lsr #0x8
    orrge r9, r3, r9, lsl #0x18
    movge r3, r10, lsr #0x8
    orrge r10, ip, r10, lsl #0x18
    movge ip, lr, lsr #0x8
    orrge lr, r3, lr, lsl #0x18
    stmgeia r1!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subges r2, r2, #0x20
    bge L_02016060
    add r2, r2, #0x20
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x4
L_020160bc:
    ldrge r3, [r0], #0x4
    orrge ip, ip, r3, lsl #0x18
    strge ip, [r1], #0x4
    movge ip, r3, lsr #0x8
    subges r2, r2, #0x4
    bge L_020160bc
    add r2, r2, #0x4
    sub r0, r0, #0x3
    add r2, r2, #0x3
    b L_020160e4
L_020160e4:
    tst r2, #0x4
    ldrneb r3, [r0], #0x1
    strneb r3, [r1], #0x1
    ldrneb r3, [r0], #0x1
    strneb r3, [r1], #0x1
    ldrneb r3, [r0], #0x1
    strneb r3, [r1], #0x1
    ldrneb r3, [r0], #0x1
    strneb r3, [r1], #0x1
    tst r2, #0x2
    ldrneb r3, [r0], #0x1
    strneb r3, [r1], #0x1
    ldrneb r3, [r0], #0x1
    strneb r3, [r1], #0x1
    tst r2, #0x1
    ldrneb r3, [r0], #0x1
    strneb r3, [r1], #0x1
    bx lr
}

asm void MI_CpuMove(register const void *src, register void *dest, register u32 size) {
    nofralloc
    cmp r2, #0x0
    subnes r3, r0, r1
    bxeq lr
    bgt MI_CpuCopy
    add r1, r1, r2
    add r0, r0, r2
    cmp r2, #0x8
    bgt L_0201619c
    rsb r3, r2, #0x8
    add pc, pc, r3, lsl #0x3
    mov r0, r0
    ldrb r3, [r0, #-0x1]!
    strb r3, [r1, #-0x1]!
    ldrb r3, [r0, #-0x1]!
    strb r3, [r1, #-0x1]!
    ldrb r3, [r0, #-0x1]!
    strb r3, [r1, #-0x1]!
    ldrb r3, [r0, #-0x1]!
    strb r3, [r1, #-0x1]!
    ldrb r3, [r0, #-0x1]!
    strb r3, [r1, #-0x1]!
    ldrb r3, [r0, #-0x1]!
    strb r3, [r1, #-0x1]!
    ldrb r3, [r0, #-0x1]!
    strb r3, [r1, #-0x1]!
    ldrb r3, [r0, #-0x1]!
    strb r3, [r1, #-0x1]!
    bx lr
L_0201619c:
    tst r0, #0x2
    subne r2, r2, #0x2
    ldrneb r3, [r0, #-0x1]!
    strneb r3, [r1, #-0x1]!
    ldrneb r3, [r0, #-0x1]!
    strneb r3, [r1, #-0x1]!
    tst r0, #0x1
    subne r2, r2, #0x1
    ldrneb r3, [r0, #-0x1]!
    strneb r3, [r1, #-0x1]!
    and r3, r1, #0x3
    bic r1, r1, #0x3
    cmp r3, #0x0
    beq L_020161e8
    cmp r3, #0x1
    beq L_02016224
    cmp r3, #0x2
    beq L_020162c0
    b L_0201635c
L_020161e8:
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x20
L_020161f0:
    ldmgedb r0!, {r4, r5, r6, r7, r8, r9, r10, lr}
    stmgedb r1!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subges r2, r2, #0x20
    bge L_020161f0
    add r2, r2, #0x20
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x4
L_0201620c:
    ldrge r3, [r0, #-0x4]!
    strge r3, [r1, #-0x4]!
    subges r2, r2, #0x4
    bge L_0201620c
    add r2, r2, #0x4
    b L_020163f8
L_02016224:
    ldr ip, [r1]
    mov ip, ip, lsr #0x8
    mov ip, ip, lsl #0x8
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x20
L_02016238:
    ldmgedb r0!, {r4, r5, r6, r7, r8, r9, r10, lr}
    movge r3, lr, lsl #0x8
    orrge lr, ip, lr, lsr #0x18
    movge ip, r10, lsl #0x8
    orrge r10, r3, r10, lsr #0x18
    movge r3, r9, lsl #0x8
    orrge r9, ip, r9, lsr #0x18
    movge ip, r8, lsl #0x8
    orrge r8, r3, r8, lsr #0x18
    movge r3, r7, lsl #0x8
    orrge r7, ip, r7, lsr #0x18
    movge ip, r6, lsl #0x8
    orrge r6, r3, r6, lsr #0x18
    movge r3, r5, lsl #0x8
    orrge r5, ip, r5, lsr #0x18
    movge ip, r4, lsl #0x8
    orrge r4, r3, r4, lsr #0x18
    stmgeda r1!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subges r2, r2, #0x20
    bge L_02016238
    add r2, r2, #0x20
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x4
L_02016294:
    ldrge r3, [r0, #-0x4]!
    orrge ip, ip, r3, lsr #0x18
    strge ip, [r1], #-0x4
    movge ip, r3, lsl #0x8
    subges r2, r2, #0x4
    bge L_02016294
    add r2, r2, #0x4
    add r1, r1, #0x4
    add r0, r0, #0x3
    add r2, r2, #0x3
    b L_020163f8
L_020162c0:
    ldr ip, [r1]
    mov ip, ip, lsr #0x10
    mov ip, ip, lsl #0x10
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x20
L_020162d4:
    ldmgedb r0!, {r4, r5, r6, r7, r8, r9, r10, lr}
    movge r3, lr, lsl #0x10
    orrge lr, ip, lr, lsr #0x10
    movge ip, r10, lsl #0x10
    orrge r10, r3, r10, lsr #0x10
    movge r3, r9, lsl #0x10
    orrge r9, ip, r9, lsr #0x10
    movge ip, r8, lsl #0x10
    orrge r8, r3, r8, lsr #0x10
    movge r3, r7, lsl #0x10
    orrge r7, ip, r7, lsr #0x10
    movge ip, r6, lsl #0x10
    orrge r6, r3, r6, lsr #0x10
    movge r3, r5, lsl #0x10
    orrge r5, ip, r5, lsr #0x10
    movge ip, r4, lsl #0x10
    orrge r4, r3, r4, lsr #0x10
    stmgeda r1!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subges r2, r2, #0x20
    bge L_020162d4
    add r2, r2, #0x20
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x4
L_02016330:
    ldrge r3, [r0, #-0x4]!
    orrge ip, ip, r3, lsr #0x10
    strge ip, [r1], #-0x4
    movge ip, r3, lsl #0x10
    subges r2, r2, #0x4
    bge L_02016330
    add r2, r2, #0x4
    add r1, r1, #0x4
    add r0, r0, #0x2
    add r2, r2, #0x2
    b L_020163f8
L_0201635c:
    ldr ip, [r1]
    mov ip, ip, lsr #0x18
    mov ip, ip, lsl #0x18
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x20
L_02016370:
    ldmgedb r0!, {r4, r5, r6, r7, r8, r9, r10, lr}
    movge r3, lr, lsl #0x18
    orrge lr, ip, lr, lsr #0x8
    movge ip, r10, lsl #0x18
    orrge r10, r3, r10, lsr #0x8
    movge r3, r9, lsl #0x18
    orrge r9, ip, r9, lsr #0x8
    movge ip, r8, lsl #0x18
    orrge r8, r3, r8, lsr #0x8
    movge r3, r7, lsl #0x18
    orrge r7, ip, r7, lsr #0x8
    movge ip, r6, lsl #0x18
    orrge r6, r3, r6, lsr #0x8
    movge r3, r5, lsl #0x18
    orrge r5, ip, r5, lsr #0x8
    movge ip, r4, lsl #0x18
    orrge r4, r3, r4, lsr #0x8
    stmgeda r1!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subges r2, r2, #0x20
    bge L_02016370
    add r2, r2, #0x20
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs r2, r2, #0x4
L_020163cc:
    ldrge r3, [r0, #-0x4]!
    orrge ip, ip, r3, lsr #0x8
    strge ip, [r1], #-0x4
    movge ip, r3, lsl #0x18
    subges r2, r2, #0x4
    bge L_020163cc
    add r2, r2, #0x4
    add r1, r1, #0x4
    add r0, r0, #0x1
    add r2, r2, #0x1
    b L_020163f8
L_020163f8:
    tst r2, #0x4
    ldrneb r3, [r0, #-0x1]!
    strneb r3, [r1, #-0x1]!
    ldrneb r3, [r0, #-0x1]!
    strneb r3, [r1, #-0x1]!
    ldrneb r3, [r0, #-0x1]!
    strneb r3, [r1, #-0x1]!
    ldrneb r3, [r0, #-0x1]!
    strneb r3, [r1, #-0x1]!
    tst r2, #0x2
    ldrneb r3, [r0, #-0x1]!
    strneb r3, [r1, #-0x1]!
    ldrneb r3, [r0, #-0x1]!
    strneb r3, [r1, #-0x1]!
    tst r2, #0x1
    ldrneb r3, [r0, #-0x1]!
    strneb r3, [r1, #-0x1]!
    bx lr
}
