#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/dc_cache.h"
#include "sdk/snd/snd_work.h"

// SNDi_GetFinishedCommandTag() (0x0201b968): number of command lists the ARM7 has finished, read from the shared block.
u32 SNDi_GetFinishedCommandTag(void) {
    DC_InvalidateRange(data_0212b8e0, 4);
    return data_0212b8e0->finishedTag;
}

// SNDi_InitSharedWork(work) (0x0201b98c): resets the status block: no finished lists, no players or channels busy and
// all per-player track words and the trailing word table set to 0xffff, then flushes it to memory.
void SNDi_InitSharedWork(SndSharedWork *work) {
    s32 i;
    s32 j;

    work->playerStatus = 0;
    work->channelStatus = 0;
    work->unk_0a = 0;
    work->finishedTag = 0;
    for (i = 0; i < 16; i++) {
        work->players[i].unk_20 = 0;
        for (j = 0; j < 16; j++) {
            work->players[i].trackStatus[j] = -1;
        }
    }
    for (i = 0; i < 16; i++) {
        work->unk_260[i] = -1;
    }
    DC_FlushRange(work, 0x280);
}
