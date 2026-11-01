#ifndef ENGINE_GX_MISC_API_H
#define ENGINE_GX_MISC_API_H

// Functions defined in src/engine/gx_misc*.cpp.

#include "engine/entity.h"

extern "C" {
void Gx_loadPalette(u16 value);
void Gx_setBlendAlpha(void);
}

#endif
