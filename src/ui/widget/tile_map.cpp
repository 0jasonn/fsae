#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/pane.h"
#include "ui/widget/tile_map_api.h"
#include "ui/widget/tile_map.h"

// tile_map: functions Rec_returnZero (0x020b7570), TileMap_init (0x020b7578) and TileMap_getCell (0x020b75d0).
// data_02126c3c is the vtable of TileMap.

extern u8 data_02126c3c[];

// Rec_returnZero(self) (0x020b7570, provisional name): returns 0
s32 Rec_returnZero(void *self) {
    return 0;
}
