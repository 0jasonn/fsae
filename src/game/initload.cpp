#include "engine/functions.h"
#include "global.h"
#include "game/bg_info.h"

extern "C" void initScrWithLoad(BGInfo *bg, u32 unused, s32 index);

// initScrWithLoad (0x020ac64c): copies a screen resource into a new 0x20-aligned buffer and reads its chunk
void initScrWithLoad(BGInfo *bg, u32 unused, s32 index) {
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
    bg->scrBuf = buf;
    data = getResourceData(id, kind);
    MIi_CpuCopyFast(data, buf, size);
    ResChunk_GetNRCS(bg->scrBuf, &bg->scrChunk);
}
