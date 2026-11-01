#ifndef WIP_G_BG_LOAD_H
#define WIP_G_BG_LOAD_H

#include "global.h"

// Header of the BG load block passed to the BG loaders (provisional layout from the code that reads it):
// +0x00 width in pixels (the row stride of a copied rectangle is width >> 3 elements),
// +0x02 height in pixels, +0x04 and +0x06 flags read by the palette selection,
// +0x08 size in bytes of the data, +0x0c the data itself.
typedef struct BgLoadInfo {
    u16 widthPx;
    u16 heightPx;
    u16 flag04;
    u16 flag06;
    u32 dataSize;
} BgLoadInfo;

#endif
