#ifndef WIP_G_SNDTRACK_H
#define WIP_G_SNDTRACK_H

#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"

// Sound track (provisional name). The table data_02184920 holds four 0x17c-byte tracks. flags at +0x118: bit 0 =
// active, bit 1 = running (its list is set up by SndTrack_Update), bit 3 = list set up.
typedef struct SndTrack {
    /* 00 */ u8 unk_00[0x4c];
    /* 4c */ u32 channelMask;
    /* 50 */ u8 unk_50[0xf0 - 0x50];
    /* f0 */ SndList list;
    /* 100 */ u8 unk_100[0x118 - 0x100];
    /* 118 */ u32 flags;
    /* 11c */ u8 unk_11c[0x128 - 0x11c];
    /* 128 */ s32 counter;
    /* 12c */ u8 unk_12c[0x154 - 0x12c];
    /* 154 */ u32 *handle;
    /* 158 */ void *unk_158;
    /* 15c */ u8 unk_15c[0x170 - 0x15c];
    /* 170 */ void *stopCallback;
    /* 174 */ u8 unk_174[0x178 - 0x174];
    /* 178 */ void *updateCallback;
} SndTrack;

extern "C" {
extern SndTrack data_02184920[4];
extern SndList data_02185ff0;
extern u32 data_021848f0[];
void SndTrack_Finish(SndTrack *track, s32 unused);
void SndList_MoveMatching(SndList *list, s32 key);
void SndTrack_ReleaseCounted(SndTrack *track);
void SndTrack_Reset(SndTrack *track);
}

extern "C" void func_020c1a38(s32 count);
extern "C" void SndTrack_Update(SndTrack *track, s32 count);
extern "C" void SndTrack_Reset(SndTrack *track);
extern "C" void SndTrack_Stop(SndTrack *track);
extern "C" void SndTrack_Finish(SndTrack *track, s32 unused);

#endif
