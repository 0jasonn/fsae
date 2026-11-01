#include "engine/functions.h"
#include "global.h"
#include "engine/bg_load.h"
#include "engine/bg_char.h"

extern "C" void DC_FlushRange(void *base, u32 size);
extern "C" void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern "C" void BgRect_ClipCopy(u8 *dstVram, BgLoadInfo *src, s32 srcX, s32 srcY, s32 dstX, s32 dstY, s32 dstWidth,
                                s32 dstHeight, s32 width, s32 height);
extern "C" u16 *data_020df1a4[];
extern "C" s32 data_020dfb80;

// BgChar_Load (provisional name): copies the character data to the character base of the BG of the screen (screen 0..3 main
// engine, 4..7 sub engine), starting after rect->widthTiles * rect->heightTiles tiles of 0x40 bytes (colour mode 4) or
// 0x20 bytes. The DMA channel data_020dfb80 is used when it holds 0..3, otherwise a CPU copy.
extern "C" void BgChar_Load(s32 screen, BgCharData *charData, BgCharRect *rect);
void BgChar_Load(s32 screen, BgCharData *charData, BgCharRect *rect) {
    u32 dstOffset;
    u32 vramBase;
    u32 charBlock;
    u16 bgCnt;
    s32 dmaNo;
    u8 *dst;
    u32 size;
    void *src;
    u32 tileCount;

    dstOffset = 0;
    if (rect != NULL) {
        tileCount = rect->widthTiles * rect->heightTiles;
        dstOffset = tileCount * (charData->colorMode == 4 ? 0x40 : 0x20);
    }
    DC_FlushRange(charData->data, charData->size);
    size = charData->size;
    bgCnt = *data_020df1a4[screen];
    src = charData->data;
    charBlock = (bgCnt & 0x3c) >> 2;
    if (screen > 3) {
        vramBase = 0x06200000;
    } else {
        vramBase = 0x06000000 + ((*(u32 *)0x04000000 & 0x7000000) >> 24) * 0x10000;
    }
    dst = (u8 *)vramBase + charBlock * 0x4000;
    dmaNo = data_020dfb80;
    if ((u32)dmaNo > 3) {
        dmaNo = -1;
    }
    if (dmaNo != -1) {
        MIi_DmaCopy16(dmaNo, src, dst + dstOffset, size, 1);
    } else {
        MIi_CpuCopy16(src, dst + dstOffset, size);
    }
}

// BgScreen_Load (provisional name): copies the BG map of info to the screen base of the BG of the screen, clipped to the
// size of the BG in tiles (func_020c7018) and to the size of the map. The data of info is flushed from the cache first.
extern "C" void BgScreen_Load(s32 screen, BgLoadInfo *info);
void BgScreen_Load(s32 screen, BgLoadInfo *info) {
    u32 screenBlock;
    u32 vramBase;
    u16 bgCnt;
    u8 *dst;
    s32 widthTiles;
    s32 heightTiles;
    s32 rawW;
    s32 rawH;
    s32 sizeW;
    s32 sizeH;

    bgCnt = *data_020df1a4[screen];
    screenBlock = (bgCnt & 0x1f00) >> 8;
    if (screen > 3) {
        vramBase = 0x06200000;
    } else {
        vramBase = 0x06000000 + ((*(u32 *)0x04000000 & 0x38000000) >> 0x1b) * 0x10000;
    }
    dst = (u8 *)vramBase + screenBlock * 0x800;
    widthTiles = (u32)info->widthPx >> 3;
    heightTiles = (u32)info->heightPx >> 3;
    func_020c7018((u32 *)&rawW, (u32 *)&rawH, screen);
    sizeW = widthTiles;
    if (rawW <= widthTiles) {
        sizeW = rawW;
    }
    sizeH = heightTiles;
    if (rawH <= heightTiles) {
        sizeH = rawH;
    }
    DC_FlushRange((u8 *)info + 0xc, info->dataSize);
    BgRect_ClipCopy(dst, info, 0, 0, 0, 0, rawW, rawH, sizeW, sizeH);
}
