#include "engine/functions.h"
#include "global.h"
#include "engine/sound/sndentry.h"

// SndEntry_Start: starts the entry's timer and, the first time, hooks it into the post-exit callbacks.
extern "C" void SndEntry_Start(SndEntry *entry);
void SndEntry_Start(SndEntry *entry) {
    SND_StartTimer(entry->timerValue, 0, 1 << entry->channelIndex, 0);
    if (((s32)(entry->flags << 30) >> 31) != 0) {
        return;
    }
    PM_PrependPostExitCallback(entry->exitHookA);
    PM_AppendPostExitCallback(entry->exitHookB);
    entry->flags |= 2;
}

// SndEntry_StopIfPending: stops the entry when its release is pending (bit 0).
void SndEntry_StopIfPending(SndEntry *entry) {
    if (((s32)(entry->flags << 31) >> 31) != 0) {
        SndEntry_Stop(entry);
    }
}

// Per-channel volume entry: the offset at +4 is added to the entry's volume base.
typedef struct SndVolumeDesc {
    /* 00 */ u32 unk_00;
    /* 04 */ s32 offset;
} SndVolumeDesc;

extern "C" SndVolumeDesc data_02184794[];

// SndEntry_ApplyVolumes: stores the volume base and sets the volume of each of the entry's channels from the base plus the
// channel's offset.
void SndEntry_ApplyVolumes(SndEntry *entry, s32 volumeBase) {
    u8 channel;
    s32 i;
    s32 volume;

    entry->volumeBase = volumeBase;
    for (i = 0; i < entry->channelCount; i++) {
        channel = entry->channels[i];
        volume = SND_CalcChannelVolume(entry->volumeBase + data_02184794[channel].offset);
        SND_SetChannelVolume(1 << channel, volume & 0xff, volume >> 8);
    }
}

extern "C" {
void PmList_DeleteFirst(void *hook);
void PmList_DeleteSecond(void *hook);
u32 SND_GetCurrentCommandTag(void);
void SND_FlushCommand(u32 mode);
void SND_WaitForCommandProc(u32 tag);
extern u8 data_02184788[]; // list that released entries are removed from
extern u32 data_02184814;
extern u32 data_0218485c;
}

// SndEntry_Stop: stops a started entry (timer off, hooks removed, flags cleared, command queue flushed) and then
// releases it.
void SndEntry_Stop(SndEntry *entry) {
    u32 tag;

    if (((s32)(entry->flags << 30) >> 31) != 0) {
        SND_StopTimer(entry->timerValue, 0, 1 << entry->channelIndex, 0);
        PmList_DeleteFirst(entry->exitHookA);
        PmList_DeleteSecond(entry->exitHookB);
        entry->flags &= ~2;
        tag = SND_GetCurrentCommandTag();
        SND_FlushCommand(1);
        SND_WaitForCommandProc(tag);
    }
    SndEntry_Release(entry);
}

// SndEntry_Release: clears the channel's bit in word 4, removes the entry from the list and clears the release-pending
// flag.
void SndEntry_Release(SndEntry *entry) {
    SndChannel_ClearWord4(entry->channelIndex);
    func_020c2004(data_02184788, entry);
    entry->flags &= ~1;
}

// SndSys_ClearWords: clears two state words.
extern "C" void SndSys_ClearWords(void);
void SndSys_ClearWords(void) {
    data_02184814 = 0;
    data_0218485c = 0;
}
