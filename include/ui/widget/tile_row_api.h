#ifndef ENGINE_TILE_ROW_API_H
#define ENGINE_TILE_ROW_API_H

// Functions defined in src/engine/tile_row*.cpp.

#include "engine/entity.h"

extern "C" {
u16 *TileBuffer_getRow(void *self, u32 index);
void *TileMap_setupFromSrc(void *self, void **src);
}

#endif
