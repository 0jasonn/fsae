#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/frame_asm_api.h"

// Four short ARM sequences that are only instructions (no C body). Each one matches the ROM byte for byte.

// 0x0200bf40: epilogue for a frame of 0xa4 bytes, restores r4-r11 and returns.
asm void Frame_AddSp0xa4PopR4R11(void) {
    add sp, sp, #0xa4
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}

