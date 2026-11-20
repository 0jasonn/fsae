#ifndef ENGINE_VRAMBANK_API_H
#define ENGINE_VRAMBANK_API_H

// Functions defined in src/engine/vrambank*.cpp.

#include "engine/entity.h"

extern "C" {
void Vram_ResetBankC(void);
void Vram_ResetBankD(void);
void Vram_ResetSubBankA(void);
void Vram_ResetSubBankB(void);
}

#endif
