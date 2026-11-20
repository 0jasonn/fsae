#include "global.h"
#include "types.h"
#include "sdk/os/dc_cache.h"

// ARM946E-S cache maintenance (CP15 c7). Line size is 0x20 bytes.

// Clean and invalidate every data cache line (4 segments x 32 sets), draining the write buffer before each line.
asm void DC_FlushAll(void) {
    mov ip, #0
    mov r1, #0
@segment:
    mov r0, #0
@line:
    orr r2, r1, r0
    mcr p15, 0, ip, c7, c10, 4
    mcr p15, 0, r2, c7, c14, 2
    add r0, r0, #0x20
    cmp r0, #0x400
    blt @line
    add r1, r1, #0x40000000
    cmp r1, #0
    bne @segment
    bx lr
}

asm void DC_InvalidateRange(void *start, u32 size) {
    add r1, r1, r0
    bic r0, r0, #0x1f
@loop:
    mcr p15, 0, r0, c7, c6, 1
    add r0, r0, #0x20
    cmp r0, r1
    blt @loop
    bx lr
}

asm void DC_StoreRange(void *start, u32 size) {
    add r1, r1, r0
    bic r0, r0, #0x1f
@loop:
    mcr p15, 0, r0, c7, c10, 1
    add r0, r0, #0x20
    cmp r0, r1
    blt @loop
    bx lr
}

asm void DC_FlushRange(const void *start, u32 size) {
    mov ip, #0
    add r1, r1, r0
    bic r0, r0, #0x1f
@loop:
    mcr p15, 0, ip, c7, c10, 4
    mcr p15, 0, r0, c7, c14, 1
    add r0, r0, #0x20
    cmp r0, r1
    blt @loop
    bx lr
}

asm void DC_WaitWriteBufferEmpty(void) {
    mov r0, #0
    mcr p15, 0, r0, c7, c10, 4
    bx lr
}

asm void IC_InvalidateAll(void) {
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0
    bx lr
}

asm void IC_InvalidateRange(void *start, u32 size) {
    add r1, r1, r0
    bic r0, r0, #0x1f
@loop:
    mcr p15, 0, r0, c7, c5, 1
    add r0, r0, #0x20
    cmp r0, r1
    blt @loop
    bx lr
}

// Waits for scanline 0 (REG_VCOUNT == 0) with the master interrupt enable register (+0x208) overwritten by the register
// base address, then restores it.
asm void OSi_WaitVCount0(void) {
    mov ip, #0x4000000
    ldr r1, [ip, #0x208]
    str ip, [ip, #0x208]
@wait:
    ldrh r0, [ip, #6]
    cmp r0, #0
    bne @wait
    str r1, [ip, #0x208]
    bx lr
}
