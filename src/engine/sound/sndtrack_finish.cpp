#include "engine/functions.h"
#include "global.h"
#include "engine/sound/sndtrack.h"
#include "sdk/os/os_mutex.h"

extern "C" {
extern OsMutex data_02185fd8; // the sound mutex
void SndEntry_StopIfPending(void *entry);
}

// SndTrack_Finish: with the sound mutex and the second track mutex held, stops the track's pending entry (flag bit 1),
// calls its update callback (flag bit 0) and stops the track. The second argument is not used.
extern "C" void SndTrack_Finish(SndTrack *track, s32 unused);
void SndTrack_Finish(SndTrack *track, s32 unused) {
    OS_LockMutexFromWToR(&data_02185fd8);
    if (data_021848f0[1] != 0) {
        OS_LockMutexFromWToR((OsMutex *)((u8 *)data_021848f0[1] + 0x10c8));
    }
    if (((s32)(track->flags << 30) >> 31) != 0) {
        SndEntry_StopIfPending(track);
    }
    if (((s32)(track->flags << 31) >> 31) != 0) {
        ((void (*)(SndTrack *))track->updateCallback)(track);
    }
    SndTrack_Stop(track);
    OS_UnlockMutex(&data_02185fd8);
    if (data_021848f0[1] != 0) {
        OS_UnlockMutex((OsMutex *)((u8 *)data_021848f0[1] + 0x10c8));
    }
}
