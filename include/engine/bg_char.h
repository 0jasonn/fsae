#ifndef WIP_G_BG_CHAR_H
#define WIP_G_BG_CHAR_H

#include "global.h"

// Character data passed to BgChar_Load (provisional layout from the code that reads it):
// +0x04 colour mode (4 selects 8bpp tiles of 0x40 bytes, anything else 4bpp tiles of 0x20 bytes),
// +0x10 size in bytes of the data, +0x14 the data itself.
typedef struct BgCharData {
    u32 unk00;
    u32 colorMode;
    u8 unk08[8];
    u32 size;
    void *data;
} BgCharData;

// Rectangle of tiles passed to BgChar_Load (provisional layout): the halfwords at +2 and +4 are the width and height in
// tiles; their product times the tile size is the offset of the data in the character base.
typedef struct BgCharRect {
    u16 unk00;
    u16 widthTiles;
    u16 heightTiles;
} BgCharRect;

#endif
