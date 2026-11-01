#ifndef ENGINE_BG_PALETTE_API_H
#define ENGINE_BG_PALETTE_API_H

// Functions defined in src/engine/bg_palette*.cpp.

#include "engine/entity.h"

extern "C" {
u32 BgExtPalette_ResolveSlot(u32 index);
void BgPalette_LoadSelect(s32 screen, u32 useExt, u8 *palette, u8 *table);
}

#endif
