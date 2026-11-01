#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/pane.h"
#include "ui/widget/tile_map.h"

// tile_map: functions Rec_returnZero (0x020b7570), TileMap_init (0x020b7578) and TileMap_getCell (0x020b75d0).
// data_02126c3c is the vtable of TileMap.

extern u8 data_02126c3c[];

// TileMap_getCell(self, pos) (0x020b75d0, provisional name): the halfword at column pos[0] of row pos[1]
extern "C" u16 TileMap_getCell(TileMap *self, const s16 *pos);
u16 TileMap_getCell(TileMap *self, const s16 *pos) {
    return *(u16 *)(self->base + pos[1] * self->stride + pos[0] * 2);
}
