#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/g2.h"

void G2x_SetBlendAlpha_(void *reg, s32 plane1, s32 plane2, s32 ev1, s32 ev2) {
    *(u32 *)reg = ((plane1 | 0x40) | (plane2 << 8)) | ((ev1 | (ev2 << 8)) << 16);
}
