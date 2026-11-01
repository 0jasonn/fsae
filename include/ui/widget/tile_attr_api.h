#ifndef ENGINE_TILE_ATTR_API_H
#define ENGINE_TILE_ATTR_API_H

// Functions defined in src/engine/tile_attr*.cpp.

#include "engine/entity.h"

extern "C" {
u16 TileMap_getCellAttr(void *self, const s16 *pos);
}

#endif
