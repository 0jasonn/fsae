#ifndef WIP_F_TILE_RECORD_H
#define WIP_F_TILE_RECORD_H

// Tile map record of tile_map.cpp (base, cell table, width, height, stride) and the source record that
// TileMap_initWithOffset reads (width and height halfwords, a kind byte at +4, a flag byte at +5, a halfword offset at +6
// and the cells at +0x10).

#include "types.h"

typedef struct TileMap {
    void *vtable;       // 0x00
    u8 *base;           // 0x04
    u32 unk_08;         // 0x08
    u16 width;          // 0x0c
    u16 height;         // 0x0e
    u32 stride;         // 0x10
    u8 unk_14;          // 0x14
} TileMap;

typedef struct TileRecord {
    u16 width;          // 0x00
    u16 height;         // 0x02
    u8 kind;            // 0x04
    u8 flag;            // 0x05
    u16 offset;         // 0x06: in halfwords from the cells
    u8 cells[1];        // 0x10
} TileRecord;

#endif
