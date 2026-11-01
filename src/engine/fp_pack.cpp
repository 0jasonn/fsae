#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/fp_pack_api.h"

// Packs an unsigned 32-bit integer into a soft-float bit pattern: the value is normalised (clz), the exponent is
// 0x9e minus the shift, and the low byte is rounded to nearest-even. Zero returns zero. The clz instruction has no
// C form here, so the whole sequence is written in ARM assembly.

// 0x0200d6f8
asm u32 Fp_PackU32ToFloat(u32 value) {
    cmp r0, #0x0
    bxeq lr
    mov r3, #0x9e
    bmi fp_skip_norm
    clz ip, r0
    movs r0, r0, lsl ip
    sub r3, r3, ip
fp_skip_norm:
    ands r2, r0, #0xff
    add r0, r0, r0
    mov r0, r0, lsr #0x9
    orr r0, r0, r3, lsl #0x17
    bxeq lr
    tst r2, #0x80
    bxeq lr
    ands r1, r2, #0x7f
    andeqs r1, r0, #0x1
    addne r0, r0, #0x1
    bx lr
}
