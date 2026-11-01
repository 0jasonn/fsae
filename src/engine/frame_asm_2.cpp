#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Four short ARM sequences that are only instructions (no C body). Each one matches the ROM byte for byte.

extern "C" void Frame_AddSp0xa4PopR4R11(void);
extern "C" u32 Swp_Exchange(u32 value, u32 *target);
extern "C" void Frame_PopR3ToR7Return(void);
extern "C" u32 Bits_CountLeadingZeros(u32 value);

// 0x02016440: atomic exchange of value with *target (swp).
asm u32 Swp_Exchange(u32 value, u32 *target) {
    swp r0, r0, [r1]
    bx lr
}

