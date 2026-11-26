#ifndef SDK_GX_GX_H
#define SDK_GX_GX_H

// TwlSDK GX display control: DISPSTAT interrupts, display on/off, graphics mode and master brightness.
#include "types.h"

extern u16 data_020dfb7c;               // display on flag, cleared by GX_DispOff
extern u16 data_02129824;               // DISPCNT display mode saved by GX_DispOff

extern "C" {
void GX_SetVCountEqVal(u32 line);
BOOL GX_HBlankIntr(BOOL enable);
BOOL GX_VBlankIntr(BOOL enable);
void GX_DispOff(void);
void GXS_SetGraphicsMode(u32 mode);
void GXx_SetMasterBrightness_(void *reg, u32 value);
}

#endif
