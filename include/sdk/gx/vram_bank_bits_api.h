#ifndef SDK_GX_VRAM_BANK_BITS_API_H
#define SDK_GX_VRAM_BANK_BITS_API_H

// Functions defined in src/sdk/gx/vram_bank_bits*.cpp: set the sub BG (B) / sub OBJ (C) extended palette banks.

#include "engine/entity.h"

extern "C" {
void Vram_SetBankGroupB(u32 mask);
void Vram_SetBankGroupC(u32 mask);
}

#endif
