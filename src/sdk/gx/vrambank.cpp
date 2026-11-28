#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/vrambank_api.h"
#include "sdk/gx/gx_vramcnt.h"

// Records of data_02129864 that dsd names on their own (see sdk/gx/gx_vramcnt.h).
extern u16 data_02129872; // GX_VRAM_BGEXTPLTT
extern u16 data_02129874; // GX_VRAM_OBJEXTPLTT
extern u16 data_0212986c; // GX_VRAM_TEX
extern u16 data_0212986e; // GX_VRAM_TEXPLTT
extern u16 data_0212987a; // GX_VRAM_SUB_BGEXTPLTT
extern u16 data_0212987c; // GX_VRAM_SUB_OBJEXTPLTT

// VRAM bank reset helpers. Each clears one display control bit (main DISPCNT at 0x04000000, sub DISPCNT at
// 0x04001000) and then resets one bank record in the 0x02129864 table through resetBankForX_, returning its banks.

u32 Vram_ResetMainBankA(void) {
    *(volatile u32 *)0x4000000 &= ~0x40000000;
    return resetBankForX_(&data_02129872);
}

u32 Vram_ResetMainBankB(void) {
    *(volatile u32 *)0x4000000 &= ~0x80000000;
    return resetBankForX_(&data_02129874);
}

u32 Vram_ResetBankC(void) {
    return resetBankForX_(&data_0212986c);
}

u32 Vram_ResetBankD(void) {
    return resetBankForX_(&data_0212986e);
}

u32 Vram_ResetSubBankA(void) {
    *(volatile u32 *)0x4001000 &= ~0x40000000;
    return resetBankForX_(&data_0212987a);
}

u32 Vram_ResetSubBankB(void) {
    *(volatile u32 *)0x4001000 &= ~0x80000000;
    return resetBankForX_(&data_0212987c);
}
