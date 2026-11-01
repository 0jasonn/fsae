#ifndef ENGINE_RES_CHUNK_C_API_H
#define ENGINE_RES_CHUNK_C_API_H

// Functions defined in src/engine/res_chunk_c*.cpp.

#include "engine/entity.h"

extern "C" {
u8 *ResTable_GetEntryAt(u8 *table, u32 index);
}

#endif
