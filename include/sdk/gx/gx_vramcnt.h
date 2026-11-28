#ifndef SDK_GX_GX_VRAMCNT_H
#define SDK_GX_GX_VRAMCNT_H

// TwlSDK GX VRAM bank control (VRAMCNT registers 0x04000240..0x04000249). Bank masks: bit 0 = bank A ... bit 8 = bank I.
#include "types.h"

// VRAM bank state (data_02129864, 13 halfwords, TwlSDK sVramState): the banks of each use, indexed by GxVramUse. dsd
// names some records on their own (data_0212986c = tex, data_0212986e = texPltt, data_02129872 = bgExtPltt,
// data_02129874 = objExtPltt, data_0212987a = subBgExtPltt, data_0212987c = subObjExtPltt).
enum GxVramUse {
    GX_VRAM_LCDC,            // 0x00: banks mapped to the LCDC
    GX_VRAM_BG,              // 0x02
    GX_VRAM_OBJ,             // 0x04
    GX_VRAM_ARM7,            // 0x06
    GX_VRAM_TEX,             // 0x08
    GX_VRAM_TEXPLTT,         // 0x0a
    GX_VRAM_CLRIMG,          // 0x0c
    GX_VRAM_BGEXTPLTT,       // 0x0e
    GX_VRAM_OBJEXTPLTT,      // 0x10
    GX_VRAM_SUB_BG,          // 0x12
    GX_VRAM_SUB_OBJ,         // 0x14
    GX_VRAM_SUB_BGEXTPLTT,   // 0x16
    GX_VRAM_SUB_OBJEXTPLTT,  // 0x18
    GX_VRAM_USE_COUNT
};

extern u16 data_02129864[GX_VRAM_USE_COUNT];
extern u16 data_02129826; // lock ID of the GX library for OSi_TryLockVram

extern "C" {
void GX_VRAMCNT_SetLCDC_(u32 mask);      // maps the banks in mask to the LCDC
u32 GX_TrySetBankForLCDC(u32 banks);     // 0 when the banks are locked by the other processor
u32 resetBankForX_(u16 *bank);           // clears one record, maps its banks to the LCDC and returns them
u32 GX_GetSizeOfX_(u32 mask);            // bytes of VRAM in the banks of mask
u32 GX_GetSizeOfARM7(void);
void GX_InitGXState(void);
void Vram_SetLcdcBits(u32 mask);        // adds banks to the LCDC (src/sdk/gx/vram_lcdc.cpp)
void Vram_DisableBankTail(void);        // disables the LCDC banks (src/sdk/gx/vram_disable.cpp)
u32 MATH_CountPopulation(u32 x);         // number of set bits (sits with the GX code in the ROM)
void func_02014c24(s32 mode);            // sets the main BG extended palette banks (src/sdk/gx/vram_lcdc_mode.cpp)
// Not decompiled yet: set the banks of a use back after a Begin/End load (see sdk/gx/gx_load.h).
void func_02014d1c(u32 banks);           // main OBJ extended palette
void func_02014db8(u32 banks);           // texture
void func_02014f30(u32 banks);           // texture palette
}

#endif
