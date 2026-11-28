#ifndef SDK_SND_SND_WORK_H
#define SDK_SND_SND_WORK_H

// TwlSDK SND shared work (snd_work.c): the status block the ARM7 sound driver fills in.
#include "types.h"

// Per-player part of the shared work (0x24 bytes).
typedef struct SndSharedPlayer {
    s16 trackStatus[16]; // 0x00
    u32 unk_20;          // 0x20
} SndSharedPlayer;

// Status block shared with the ARM7 sound driver (data_02129e00, 0x280 bytes; data_0212b8e0 points at it). Read after
// DC_InvalidateRange.
typedef struct SndSharedWork {
    u32 finishedTag;             // 0x00: number of command lists the ARM7 has finished
    u32 playerStatus;            // 0x04: bit mask of the running sequence players
    u16 channelStatus;           // 0x08: bit mask of the busy hardware channels
    u16 unk_0a;                  // 0x0a
    u8 unk_0c[0x14];             // 0x0c
    SndSharedPlayer players[16]; // 0x20
    s16 unk_260[16];             // 0x260
} SndSharedWork;

extern SndSharedWork data_02129e00;
extern SndSharedWork *data_0212b8e0;

extern "C" {
u32 SND_GetPlayerStatus(void);
u16 SND_GetChannelStatus(void);
u32 SNDi_GetFinishedCommandTag(void);
void SNDi_InitSharedWork(SndSharedWork *work);
}

#endif
