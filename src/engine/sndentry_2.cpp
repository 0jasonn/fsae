#include "engine/functions.h"
#include "global.h"
#include "engine/sndentry.h"

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
extern "C" void SndEntry_Stop(SndEntry *entry);
ARM void SndEntry_Stop(SndEntry *entry) {
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
extern "C" void SndEntry_Release(SndEntry *entry);
ARM void SndEntry_Release(SndEntry *entry) {
    SndChannel_ClearWord4(entry->channelIndex);
    func_020c2004(data_02184788, entry);
    entry->flags &= ~1;
}

// SndSys_ClearWords: clears two state words.
extern "C" void SndSys_ClearWords(void);
ARM void SndSys_ClearWords(void) {
    data_02184814 = 0;
    data_0218485c = 0;
}
