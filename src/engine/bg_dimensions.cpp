#include "engine/functions.h"

extern "C" u16 *data_020df1a4[];

// Provisional name. Read tile dimensions from the background control bits and display mode.
void BgScreen_GetTileDimensions(u32 *widthTiles, u32 *heightTiles, s32 screen) {
    u32 size;
    u32 layer;
    s32 mode;

    size = (*data_020df1a4[screen] & 0xc000) >> 14;
    layer = screen & 3;
    if (screen <= 3) {
        mode = *(volatile u32 *)0x04000000 & 7;
    } else {
        mode = *(volatile u32 *)0x04001000 & 7;
    }
    if ((layer == 2 && (mode == 2 || mode >= 4)) || (layer == 3 && mode >= 1)) {
        *widthTiles = 0x10 << size;
        *heightTiles = 0x10 << size;
    } else {
        *widthTiles = (size & 1) ? 0x40 : 0x20;
        *heightTiles = (size & 2) ? 0x40 : 0x20;
    }
}
