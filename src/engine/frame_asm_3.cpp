#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/frame_asm_api.h"

// Four short ARM sequences that are only instructions (no C body). Each one matches the ROM byte for byte.

// 0x02016af4: epilogue, restores r3-r7 and returns.
asm void Frame_PopR3ToR7Return(void) {
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}

