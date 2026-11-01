#ifndef WIP_F_TILEBUF_H
#define WIP_F_TILEBUF_H

// Tile buffer helpers near 0x020b73b8 (provisional names).

#include "engine/functions.h"

extern "C" {
void TileBuffer_fillRect(void *self, s16 *pos, s16 *size, u16 value);
void func_020b7488(s16 *clip, s16 *pos, s16 *size, void *bounds);
}

#endif
