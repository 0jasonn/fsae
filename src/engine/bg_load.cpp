#include "engine/functions.h"
#include "global.h"
#include "engine/bg_load.h"

extern "C" void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern "C" void BgChar_Load(s32 screen, void *charData, void *rect);
extern "C" void BgScreen_Load(s32 screen, BgLoadInfo *info);

// BgRect_Copy16 (provisional name): copies rowCount rows of copyCount halfwords from the BG load block into dstBase. Source
// rows are widthPx >> 3 halfwords apart and destination rows are dstPitch halfwords apart; the copy starts at (dstX, dstY)
// in the destination and at row srcRow of the source.
extern "C" void BgRect_Copy16(u16 *dstBase, BgLoadInfo *src, u32 srcOffset, s32 srcRow, u32 dstX, u32 dstY, u32 dstPitch,
                              u32 copyCount, s32 rowCount);
void BgRect_Copy16(u16 *dstBase, BgLoadInfo *src, u32 srcOffset, s32 srcRow, u32 dstX, u32 dstY, u32 dstPitch,
                       u32 copyCount, s32 rowCount) {
    u32 stride;
    s32 row;
    s32 endRow;
    u32 dstOffset;
    u32 copyBytes;
    u16 *srcPtr;
    u16 *dstPtr;

    stride = (src++)->widthPx;
    dstOffset = dstY * dstPitch + dstX;
    row = srcRow;
    stride >>= 3;
    srcOffset += row * stride;
    copyBytes = copyCount << 1;
    endRow = row + rowCount;
    srcPtr = (u16 *)src + srcOffset;
    dstPtr = dstBase + dstOffset;
    for (; row < endRow; row++) {
        MIi_CpuCopy16(srcPtr, dstPtr, copyBytes);
        srcPtr += stride;
        dstPtr += dstPitch;
    }
}

// BgLoad_Resources (provisional name): loads the palette when both the palette and the load block are given, the character
// data when charData is given, and the BG screen when the load block is given.
extern "C" void BgLoad_Resources(s32 screen, BgLoadInfo *info, void *charData, u8 *palette, void *rect, u8 *loadTable);
void BgLoad_Resources(s32 screen, BgLoadInfo *info, void *charData, u8 *palette, void *rect, u8 *loadTable) {
    if (palette != NULL && info != NULL) {
        BgPalette_LoadAuto(screen, palette, (u8 *)info, loadTable);
    }
    if (charData != NULL) {
        BgChar_Load(screen, charData, rect);
    }
    if (info != NULL) {
        BgScreen_Load(screen, info);
    }
}
