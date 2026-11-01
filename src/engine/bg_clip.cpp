#include "engine/functions.h"
#include "global.h"
#include "engine/bg_load.h"

extern "C" void func_020c491c(u8 *dstVram, BgLoadInfo *src, s32 srcX, s32 srcY, s32 dstX, s32 dstY, s32 dstWidth,
                              s32 dstHeight, s32 width, s32 height);
extern "C" void func_020c4b44(u8 *dstVram, BgLoadInfo *src, s32 srcX, s32 srcY, s32 dstX, s32 dstY, s32 dstWidth,
                              s32 width, s32 height);
extern "C" void BgRect_Copy16(u16 *dstBase, BgLoadInfo *src, u32 srcOffset, s32 srcRow, u32 dstX, u32 dstY, u32 dstPitch,
                              u32 copyCount, s32 rowCount);

// BgRect_ClipCopy (provisional name): copies the rectangle of width x height tiles at (srcX, srcY) of the BG load block to
// (dstX, dstY) of the destination (dstWidth x dstHeight tiles). The rectangle is clipped on both sides to the destination
// and to the block (widthPx / heightPx in pixels, 8 pixels a tile). flag06 of the block selects the copy routine:
// 0 func_020c491c, 1 func_020c4b44, 2 BgRect_Copy16; other values copy nothing.
extern "C" void BgRect_ClipCopy(u8 *dstVram, BgLoadInfo *src, s32 srcX, s32 srcY, s32 dstX, s32 dstY, s32 dstWidth,
                                s32 dstHeight, s32 width, s32 height);
ARM void BgRect_ClipCopy(u8 *dstVram, BgLoadInfo *src, s32 srcX, s32 srcY, s32 dstX, s32 dstY, s32 dstWidth,
                         s32 dstHeight, s32 width, s32 height) {
    if (dstX < 0) {
        dstX = -dstX;
        srcX += dstX;
        width -= dstX;
        dstX = 0;
    }
    if (dstY < 0) {
        dstY = -dstY;
        srcY += dstY;
        height -= dstY;
        dstY = 0;
    }
    if (dstX + width > dstWidth) {
        width -= dstX + width - dstWidth;
    }
    if (dstY + height > dstHeight) {
        height -= dstY + height - dstHeight;
    }
    if (srcX < 0) {
        srcX = -srcX;
        dstX += srcX;
        width -= srcX;
        srcX = 0;
    }
    if (srcY < 0) {
        srcY = -srcY;
        dstY += srcY;
        height -= srcY;
        srcY = 0;
    }
    if (srcX + width > (s32)((u32)src->widthPx >> 3)) {
        width -= srcX + width - (s32)((u32)src->widthPx >> 3);
    }
    if (srcY + height > (s32)((u32)src->heightPx >> 3)) {
        height -= srcY + height - (s32)((u32)src->heightPx >> 3);
    }
    if (width <= 0 || height <= 0) {
        return;
    }
    switch (src->flag06) {
    case 0:
        func_020c491c(dstVram, src, srcX, srcY, dstX, dstY, dstWidth, dstHeight, width, height);
        break;
    case 1:
        func_020c4b44(dstVram, src, srcX, srcY, dstX, dstY, dstWidth, width, height);
        break;
    case 2:
        BgRect_Copy16((u16 *)dstVram, src, srcX, srcY, dstX, dstY, dstWidth, width, height);
        break;
    }
}
