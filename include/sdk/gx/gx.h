#ifndef SDK_GX_GX_H
#define SDK_GX_GX_H

// TwlSDK GX display control: DISPSTAT interrupts, display on/off, graphics mode and master brightness.
#include "types.h"

typedef struct GxDisplayState {
    u16 isDispOn; // display on flag, cleared by GX_DispOff
    s32 defaultDma; // DMA channel of the GX loads (GX_SetDefaultDMA), -1 = CPU copy; also OamRing_dmaNo
} GxDisplayState;
extern GxDisplayState data_020dfb7c;
extern u16 data_02129824;               // DISPCNT display mode saved by GX_DispOff

extern "C" {
void GX_Init(void); // 0x02012c40
void GX_SetVCountEqVal(u32 line);
BOOL GX_HBlankIntr(BOOL enable);
BOOL GX_VBlankIntr(BOOL enable);
void GX_DispOff(void);
s32 GX_SetDefaultDMA(s32 dmaNo); // sets the DMA channel of the GX loads, returns the previous one (-1: CPU copy)
void GX_SetGraphicsMode(u32 dispMode, u32 bgMode, u32 bg0As3d);
// VRAM bank mapping (TwlSDK GX_SetBankForBG / OBJ / SubOBJ): the banks in mask (bit 0 = bank A) are mapped to the use.
void GX_SetBankForBG(s32 mask);  // BG (not decompiled yet)
void GX_SetBankForOBJ(s32 mask);  // OBJ
void GX_SetBankForSubOBJ(s32 mask);  // sub OBJ
void GXS_SetGraphicsMode(u32 mode);
void GXx_SetMasterBrightness_(void *reg, u32 value);
}

#endif
