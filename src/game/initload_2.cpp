#include "engine/functions.h"
#include "global.h"
#include "game/e_decls.h"

extern "C" void initBgCharWithLoadVram(BGInfo *bg, u32 layer, s32 index, u32 offset, u32 freeFlag);

// initBgCharWithLoadVram (0x020ac594): loads character data of a resource, sends it to VRAM, optionally frees it
void initBgCharWithLoadVram(BGInfo *bg, u32 layer, s32 index, u32 offset, u32 freeFlag) {
    u32 size;
    void *buf;
    void *data;
    u8 kind;
    u32 id;

    if (index == -1) {
        return;
    }
    kind = (u8)((u32)index >> 31);
    id = (u32)index & 0x7fffffff;
    size = getResourceSize(id, kind);
    buf = EL_GetGlobalAdr(size, 0x20);
    bg->charBuf = buf;
    data = getResourceData(id, kind);
    MIi_CpuCopyFast(data, buf, size);
    ResChunk_OpenRACH2(bg->charBuf, &bg->charChunk);
    DC_FlushRange(((ResChunkRACH *)bg->charChunk)->data, ((ResChunkRACH *)bg->charChunk)->size);
    subTaskSendBgChar((s16)layer, ((ResChunkRACH *)bg->charChunk)->data, offset, ((ResChunkRACH *)bg->charChunk)->size);
    if ((freeFlag & 1) == 0) {
        return;
    }
    func_0208e188(bg->charBuf);
    bg->charBuf = 0;
    bg->charChunk = 0;
}
