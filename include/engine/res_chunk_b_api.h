#ifndef ENGINE_RES_CHUNK_B_API_H
#define ENGINE_RES_CHUNK_B_API_H

// Functions defined in src/engine/res_chunk_b*.cpp.

#include "engine/entity.h"

extern "C" {
u8 *ResTable_GetEnd(u8 *table);
u8 *ResTable_GetEntry(u8 *table, u32 index);
void *ResTable_LookupFrom8(u8 *table);
}

#endif
