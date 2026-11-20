#ifndef ENGINE_VRAM_BANK_BITS_API_H
#define ENGINE_VRAM_BANK_BITS_API_H

// Functions defined in src/engine/vram_bank_bits*.cpp.

#include "engine/entity.h"

extern "C" {
void Vram_SetBankGroupC(u32 mask);
}

#endif
