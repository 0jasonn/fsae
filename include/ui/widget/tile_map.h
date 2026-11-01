#ifndef ENGINE_TILE_MAP_H
#define ENGINE_TILE_MAP_H

#include "engine/entity.h"

// TileMap record. The base pointer is at +4, the width and height halfwords at +0xc and +0xe, and the row stride in bytes at +0x10.
typedef struct TileMap {
    void *vtable;       // 0x00
    u8 *base;           // 0x04
    u32 unk_08;         // 0x08
    u16 width;          // 0x0c
    u16 height;         // 0x0e
    u32 stride;         // 0x10
    u8 unk_14;          // 0x14
} TileMap;

#endif
