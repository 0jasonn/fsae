#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"
#include "engine/sndtrack.h"

// SndTrack_Reset: releases the track's handle word and clears flag bits 0 to 2.
extern "C" void SndTrack_Reset(SndTrack *track);
ARM void SndTrack_Reset(SndTrack *track) {
    if (track->handle != 0) {
        *track->handle = 0;
        track->handle = 0;
    }
    track->flags &= ~1;
    track->flags &= ~4;
    track->flags &= ~2;
}

// SndTrack_Update: when the track is running and count is not zero, sets up its list with count entries and sets flag
// bit 3. Otherwise it only calls SndTrack_Finish with the running flag (0 or -1).
extern "C" void SndTrack_Update(SndTrack *track, s32 count);
ARM void SndTrack_Update(SndTrack *track, s32 count) {
    s32 running;

    running = (s32)(track->flags << 30) >> 31;
    if (running == 0) {
        SndTrack_Finish(track, running);
        return;
    }
    if (count == 0) {
        SndTrack_Finish(track, running);
        return;
    }
    SndList_Setup(&track->list, 0, count);
    track->unk_158 = 0;
    track->flags |= 8;
}
