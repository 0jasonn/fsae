#ifndef WIP_E_SNDTRACK_E_H
#define WIP_E_SNDTRACK_E_H

#include "engine/functions.h"
#include "engine/sound/sndtrack.h"
#include "engine/sound/sndentry.h"
#include "engine/sound/snd_seq.h"

// Fields of a sound track (SndTrack, 0x17c bytes) that the per-frame update reads; flags bits: 0 active, 1 started,
// 2 start pending, 3 list set up
typedef struct SndTrackPlay {
    /* 000 */ u8 unk_000[0xf0];
    /* 0f0 */ SndList list;
    /* 100 */ u8 unk_100[0x118 - 0x100];
    /* 118 */ u32 flags;
    /* 11c */ s32 seq;          // zero: nothing to play
    /* 120 */ s32 startData;    // nonzero: ready to start
    /* 124 */ u8 unk_124[0x15c - 0x124];
    /* 15c */ s32 levelIndexA;  // index into the level table data_020cd280
    /* 160 */ s32 levelIndexB;
    /* 164 */ s32 lastVolume;
    /* 168 */ u8 unk_168[0x17c - 0x168];
} SndTrackPlay;

extern "C" {
void SndTrack_UpdateAll(void);
}

#endif
