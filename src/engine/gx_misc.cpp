#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// gx_misc: functions Gx_setBrightnessPair (0x020bc3a8), Gx_setBlendAlpha (0x020bc3d4) and Gx_loadPalette (0x020bc3fc),
// provisional names.

// Gx_setBrightnessPair(value) (0x020bc3a8, provisional name): the master brightness of the two display registers at
// 0x0400006c and 0x0400106c
extern "C" void Gx_setBrightnessPair(s32 value);
ARM void Gx_setBrightnessPair(s32 value) {
    GXx_SetMasterBrightness_((void *)0x0400006c, value);
    GXx_SetMasterBrightness_((void *)0x0400106c, value);
}

// Gx_setBlendAlpha() (0x020bc3d4, provisional name): the blend alpha of the register at 0x04000050 with 1, 0x3e, 6 and 10
extern "C" void Gx_setBlendAlpha(void);
ARM void Gx_setBlendAlpha(void) {
    G2x_SetBlendAlpha_((void *)0x04000050, 1, 0x3e, 6, 10);
}

// Gx_loadPalette(value) (0x020bc3fc, provisional name): loads the palette word value from a local into both the main and
// the sub background palette (two palette colours from offset 0)
extern "C" void Gx_loadPalette(u16 value);
ARM void Gx_loadPalette(u16 value) {
    u16 colour;

    colour = value;
    GX_LoadBGPltt(&colour, 0, 2);
    GXS_LoadBGPltt(&colour, 0, 2);
}
