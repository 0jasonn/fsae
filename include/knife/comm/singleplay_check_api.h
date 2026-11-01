#ifndef ENGINE_SINGLEPLAY_CHECK_API_H
#define ENGINE_SINGLEPLAY_CHECK_API_H

// Functions defined in src/engine/singleplay_check*.cpp.

#include "engine/entity.h"

extern "C" {
BOOL Knife_Single_SinglePlay_CheckBane_094b64(void *self, Entity *e, s16 x, s16 y);
Entity *Knife_Single_SinglePlay_CheckShell(void *self, Entity *e, u8 kind);
BOOL Knife_Single_SinglePlay_CheckTsubuAtari_094bc4(void *self, u8 kind, u32 mask, Entity *e, s16 x, s16 y);
BOOL Knife_Single_SinglePlay_CheckTsubuAtari_094c0c(void *self, u8 kind, u32 mask, s16 x, s16 y, u16 layer);
}

#endif
