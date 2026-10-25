#include "engine/functions.h"
#include "global.h"
#include "engine/sndentry.h"

// SndEntry_Start: starts the entry's timer and, the first time, hooks it into the post-exit callbacks.
extern "C" void SndEntry_Start(SndEntry *entry);
ARM void SndEntry_Start(SndEntry *entry) {
    SND_StartTimer(entry->timerValue, 0, 1 << entry->channelIndex, 0);
    if (((s32)(entry->flags << 30) >> 31) != 0) {
        return;
    }
    PM_PrependPostExitCallback(entry->exitHookA);
    PM_AppendPostExitCallback(entry->exitHookB);
    entry->flags |= 2;
}

// SndEntry_StopIfPending: stops the entry when its release is pending (bit 0).
extern "C" void SndEntry_StopIfPending(SndEntry *entry);
ARM void SndEntry_StopIfPending(SndEntry *entry) {
    if (((s32)(entry->flags << 31) >> 31) != 0) {
        SndEntry_Stop(entry);
    }
}
