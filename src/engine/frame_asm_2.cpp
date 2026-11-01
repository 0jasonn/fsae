#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/frame_asm_api.h"

// Four short ARM sequences that are only instructions (no C body). Each one matches the ROM byte for byte.

// 0x02016440: atomic exchange of value with *target (swp).
asm u32 Swp_Exchange(u32 value, u32 *target) {
    swp r0, r0, [r1]
    bx lr
}

