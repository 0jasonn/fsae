#ifndef ENGINE_RES_CHUNK_D_API_H
#define ENGINE_RES_CHUNK_D_API_H

// Functions defined in src/engine/res_chunk_d*.cpp.

#include "engine/entity.h"

extern "C" {
void *ResChunk_Find(u8 *base, u32 magic);
void ResChunk_RelocOff0c(u8 *self);
void ResChunk_RelocOff14(u8 *self);
void ResChunk_RelocOff14b(u8 *self);
}

#endif
