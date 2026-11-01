#include "engine/functions.h"
#include "global.h"
#include "game/e_decls.h"

extern "C" void initBgWithLoadVram(BGInfo *bg, u32 layer, s32 charIndex, s32 palIndex, s32 scrIndex, u32 flags);

// initBgWithLoadVram (0x020ac428): loads the character (through initBgCharWithLoadVram), palette and screen data of
// a BG layer. flags bit 1 frees the palette buffer, bit 2 the screen buffer (bit 1 of the character load frees the character).
ARM void initBgWithLoadVram(BGInfo *bg, u32 layer, s32 charIndex, s32 palIndex, s32 scrIndex, u32 flags) {
    if (charIndex != -1) {
        initBgCharWithLoadVram(bg, layer, charIndex, 0, flags);
    }
    if (palIndex != -1) {
        u8 kind;
        u32 id;
        u32 size;

        kind = (u8)((u32)palIndex >> 31);
        id = (u32)palIndex & 0x7fffffff;
        size = getResourceSize(id, kind);
        bg->palBuf = EL_GetGlobalAdr(size, 0x20);
        MI_CpuCopy8(getResourceData(id, kind), bg->palBuf, size);
        ResChunk_OpenTTLP(bg->palBuf, &bg->palChunk);
        DC_FlushRange(((ResChunkTTLP *)bg->palChunk)->data, ((ResChunkTTLP *)bg->palChunk)->size);
        subTaskSendBgPlt(((ResChunkTTLP *)bg->palChunk)->data, 0, ((ResChunkTTLP *)bg->palChunk)->size);
        if ((flags & 2) != 0) {
            func_0208e188(bg->palBuf);
            bg->palBuf = 0;
            bg->palChunk = 0;
        }
    }
    if (scrIndex != -1) {
        u32 id;
        u8 kind;
        u32 size;
        void *buf;

        kind = (u8)((u32)scrIndex >> 31);
        id = (u32)scrIndex & 0x7fffffff;
        size = getResourceSize(id, kind);
        buf = EL_GetGlobalAdr(size, 0x20);
        bg->scrBuf = buf;
        MIi_CpuCopyFast(getResourceData(id, kind), buf, size);
        ResChunk_GetNRCS(bg->scrBuf, &bg->scrChunk);
        DC_FlushRange((u8 *)bg->scrChunk + 0xc, ((ResChunkTTLP *)bg->scrChunk)->size);
        subTaskSendBgChar((s16)layer, (u8 *)bg->scrChunk + 0xc, 0, ((ResChunkTTLP *)bg->scrChunk)->size);
        if ((flags & 4) != 0) {
            func_0208e188(bg->scrBuf);
            bg->scrBuf = 0;
            bg->scrChunk = 0;
        }
    }
}
