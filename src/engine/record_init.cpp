#include "engine/functions.h"
#include "global.h"

// Record_Init (provisional name): stores the two words a and b at +0 and +4, c at +8, the byte d at +0xc, the word f at +0x10
// and the word e at +0x14.
extern "C" void Record_Init(u8 *self, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);
ARM void Record_Init(u8 *self, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f) {
    *(u32 *)(self + 8) = c;
    *(u8 *)(self + 0xc) = (u8)d;
    *(u32 *)self = a;
    *(u32 *)(self + 4) = b;
    *(u32 *)(self + 0x14) = e;
    *(u32 *)(self + 0x10) = f;
}
