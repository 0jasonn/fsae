#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"
#include "engine/sndtrack.h"

// SndTrack_Stop: for an active track, releases its counter, calls its stop callback, removes its pending nodes from the
// two track lists (the second one at the list of data_021848f0 + 0x10e0 when that is set) and resets it.
extern "C" void SndTrack_Stop(SndTrack *track);
ARM void SndTrack_Stop(SndTrack *track) {
    if (((s32)(track->flags << 31) >> 31) == 0) {
        return;
    }
    SndTrack_ReleaseCounted(track);
    ((void (*)(SndTrack *))track->stopCallback)(track);
    SndList_MoveMatching(&data_02185ff0, (s32)track);
    if (data_021848f0[1] != 0) {
        SndList_MoveMatching((SndList *)(data_021848f0[1] + 0x10e0), (s32)track);
    }
    SndTrack_Reset(track);
}
