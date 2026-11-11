#ifndef WIP_E_TILEBUF_E_H
#define WIP_E_TILEBUF_E_H

#include "engine/functions.h"
#include "ui/widget/tile_row_api.h"
#include "ui/widget/tilebuf.h"

// Virtual table of a tile map source: slot 0 returns the tile at a position (bit 15 set when the tile is present)
typedef struct TileMapVtbl {
    u16 (*getCell)(void *self, s16 *pos);
} TileMapVtbl;

// Tile map object built on the stack by the blit functions (the base class ctor is inlined)
typedef struct TileMapWork {
    const TileMapVtbl *vtbl; // 0x00
    u32 unk_04;
    u32 unk_08;
    u16 unk_0c;
    u16 unk_0e;
    u32 unk_10;
    u8 unk_14;
} TileMapWork;

// Width and height of a tile map source (the first two halfwords of its record)
typedef struct TileSize {
    u16 w;
    u16 h;
} TileSize;

extern const TileMapVtbl data_02126c18;

// Virtual interface of a tile map object (slot 0 = getCell, defined elsewhere)
class TileMapObj {
public:
    virtual u16 getCell(s16 *pos);
};

extern "C" {
void TileBuffer_blitMap(void *self, s16 *pos, void **src);
}

#endif
