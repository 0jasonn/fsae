#include "sdk/mi/mi_uncompress.h"

// Checks the footer of a backward-compressed (BLZ) image, then decompresses it in place.
s32 MI_SecureUncompressBLZ(u8 *data, u32 size, u32 limit) {
    u8 *end = data + size;
    if ((*(u32 *)(end - 8) & 0xffffff) > size) {
        return -1;
    }
    u32 kind = *(end - 5);
    if (kind < 8) {
        if (kind > 11) {
            return -1;
        }
    }
    size += *(u32 *)(end - 4);
    if (size > limit) {
        return -4;
    }
    MI_UncompressBackward(end);
    return 0;
}

// Hand-written ARM in the SDK: expands the BLZ data that ends at bottom, then flushes the data cache.
asm void MI_UncompressBackward(register void *bottom) {
    nofralloc
    cmp r0, #0x0
    beq L_02016bfc
    stmdb sp!, {r4, r5, r6, r7, r8}
    ldmdb r0, {r1, r2}
    add r2, r0, r2
    sub r3, r0, r1, lsr #0x18
    bic r1, r1, #0xff000000
    sub r1, r0, r1
    mov r4, r2
L_02016b70:
    cmp r3, r1
    ble L_02016bd8
    ldrb r5, [r3, #-0x1]!
    mov r6, #0x8
L_02016b80:
    subs r6, r6, #0x1
    blt L_02016b70
    tst r5, #0x80
    bne L_02016ba0
    ldrb r0, [r3, #-0x1]!
    ldrb r8, [r2, #-0x1]
    strb r0, [r2, #-0x1]!
    b L_02016bcc
L_02016ba0:
    ldrb ip, [r3, #-0x1]!
    ldrb r7, [r3, #-0x1]!
    orr r7, r7, ip, lsl #0x8
    bic r7, r7, #0xf000
    add r7, r7, #0x2
    add ip, ip, #0x20
L_02016bb8:
    ldrb r0, [r2, r7]
    ldrb r8, [r2, #-0x1]
    strb r0, [r2, #-0x1]!
    subs ip, ip, #0x10
    bge L_02016bb8
L_02016bcc:
    cmp r3, r1
    mov r5, r5, lsl #0x1
    bgt L_02016b80
L_02016bd8:
    mov r0, #0x0
    bic r3, r1, #0x1f
L_02016be0:
    mcr p15, 0x0, r0, c7, c10, 0x4
    mcr p15, 0x0, r3, c7, c5, 0x1
    mcr p15, 0x0, r3, c7, c14, 0x1
    add r3, r3, #0x20
    cmp r3, r4
    blt L_02016be0
    ldmia sp!, {r4, r5, r6, r7, r8}
L_02016bfc:
    bx lr
}
