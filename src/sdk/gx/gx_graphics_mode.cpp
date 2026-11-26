#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/gx.h"

void GXS_SetGraphicsMode(u32 mode) {
    volatile u32 *reg = (volatile u32 *)0x4001000;
    *reg = (*reg & ~7) | mode;
}

void GXx_SetMasterBrightness_(void *reg, u32 value) {
    u16 *half = (u16 *)reg;
    s32 brightness = (s32)value;
    if (brightness == 0) {
        *half = 0;
    } else if (brightness > 0) {
        *half = brightness | 0x4000;
    } else {
        *half = (-brightness) | 0x8000;
    }
}
