#include "engine/functions.h"
#include "global.h"
#include "engine/sndtrack.h"

extern "C" {
extern u8 data_02185fd8[];
void OS_LockMutexFromWToR(void *mutex);
void OS_UnlockMutex(void *mutex);
void SndEntry_StopIfPending(void *entry);
}

// SndTrack_Finish: with the sound mutex and the second track mutex held, stops the track's pending entry (flag bit 1),
// calls its update callback (flag bit 0) and stops the track. The second argument is not used.
extern "C" void SndTrack_Finish(SndTrack *track, s32 unused);
ARM void SndTrack_Finish(SndTrack *track, s32 unused) {
    OS_LockMutexFromWToR(data_02185fd8);
    if (data_021848f0[1] != 0) {
        OS_LockMutexFromWToR((u8 *)data_021848f0[1] + 0x10c8);
    }
    if (((s32)(track->flags << 30) >> 31) != 0) {
        SndEntry_StopIfPending(track);
    }
    if (((s32)(track->flags << 31) >> 31) != 0) {
        ((void (*)(SndTrack *))track->updateCallback)(track);
    }
    SndTrack_Stop(track);
    OS_UnlockMutex(data_02185fd8);
    if (data_021848f0[1] != 0) {
        OS_UnlockMutex((u8 *)data_021848f0[1] + 0x10c8);
    }
}
