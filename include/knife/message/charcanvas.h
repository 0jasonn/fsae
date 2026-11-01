#ifndef WIP_E_CHARCANVAS_H
#define WIP_E_CHARCANVAS_H

// Char canvas helpers (src/wip/E/charcanvas.cpp): 4bpp 8x8 tile merges and fills.

#include "engine/functions.h"

extern "C" {
void CopyNotZero(s32 leftCol, s32 unused1, u8 *srcTile, u8 *dstTile, u16 unused2);
}

#endif
