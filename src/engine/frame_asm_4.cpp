#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/frame_asm_api.h"

// Four short ARM sequences that are only instructions (no C body). Each one matches the ROM byte for byte.

// 0x02019980: count leading zero bits.
asm u32 Bits_CountLeadingZeros(u32 value) {
    clz r0, r0
    bx lr
}
