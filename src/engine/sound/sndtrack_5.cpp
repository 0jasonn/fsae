#include "engine/functions.h"
#include "engine/sndtrack_e.h"

// SndTrack_UpdateAll (0x020c1a7c): per-frame update of the four sound tracks. An active track with a sequence starts
// it once its start data is ready; a started track advances its list, recalculates its volume from the level table
// and, when the list is full, finishes
void SndTrack_UpdateAll(void) {
    SndTrackPlay *track;
    s32 i;
    s32 volume;
    s32 levelA;

    for (i = 0; i < 4; i++) {
        track = (SndTrackPlay *)&data_02184920[i];
        if (((s32)(track->flags << 31) >> 31) == 0) {
            continue;
        }
        if (track->seq == 0) {
            ((void (*)(SndTrackPlay *))SndTrack_Finish)(track);
            continue;
        }
        if (((s32)(track->flags << 29) >> 31) != 0 && track->startData != 0) {
            SndEntry_Start((SndEntry *)track);
            track->flags |= 2;
            track->flags &= ~4;
        }
        if (((s32)(track->flags << 30) >> 31) == 0) {
            continue;
        }
        SndList_Advance(&track->list);
        levelA = data_020cd280[track->levelIndexA];
        volume = data_020cd280[track->levelIndexB] + (data_020cd280[(s32)SndList_GetCurrent(&track->list) >> 8] - -levelA);
        if (volume != track->lastVolume) {
            SndEntry_ApplyVolumes((SndEntry *)track, volume);
            track->lastVolume = volume;
        }
        if (((s32)(track->flags << 28) >> 31) == 0) {
            continue;
        }
        if (SndList_IsFull(&track->list) == 0) {
            continue;
        }
        ((void (*)(SndTrackPlay *))SndTrack_Finish)(track);
    }
}
