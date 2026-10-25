#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// tile_map: functions Rec_returnZero (0x020b7570), TileMap_init (0x020b7578) and TileMap_getCell (0x020b75d0).
// data_02126c3c is the vtable of TileMap.

extern u8 data_02126c3c[];

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

// TileMap_getCell(self, pos) (0x020b75d0, provisional name): the halfword at column pos[0] of row pos[1]
extern "C" u16 TileMap_getCell(TileMap *self, const s16 *pos);
ARM u16 TileMap_getCell(TileMap *self, const s16 *pos) {
    return *(u16 *)(self->base + pos[1] * self->stride + pos[0] * 2);
}
