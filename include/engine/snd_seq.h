#ifndef WIP_G_SND_SEQ_H
#define WIP_G_SND_SEQ_H

#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"
#include "engine/sndrecord.h"
#include "engine/sndvoice.h"
#include "engine/sndlink.h"

// Sound voice with every field the sequence code uses (engine/sndvoice.h names only some of them). The SndList at
// +1c is the voice's own sub-list; +2c is its state.
typedef struct SndVoiceFull {
    /* 00 */ u32 *link; // a word the release clears through this pointer
    /* 04 */ SndList *list; // the list the voice is queued in; its word at +1c is a flag
    /* 08 */ SndRecord *record;
    /* 0c */ SndVoiceOwner *owner;
    /* 10 */ s32 index;
    /* 14 */ u8 unk_14[0x1c - 0x14];
    /* 1c */ SndList subList;
    /* 2c */ u8 state; // 0 = idle, 1 = started, 2 = set up with a sub-list
    /* 2d */ u8 finished; // set when the sequence reports its command tag as finished
    /* 2e */ u8 paused;
    /* 2f */ u8 startPending; // nonzero: SND_StartPreparedSeq is called on the next update
    /* 30 */ u32 commandTag;
    /* 34 */ u16 unk_34;
    /* 36 */ u8 unk_36[0x3c - 0x36];
    /* 3c */ u8 track;
    /* 3d */ u8 priority;
    /* 3e */ s16 volume; // last volume set on the track
    /* 40 */ u8 unk_40; // index of a level table entry
    /* 41 */ u8 unk_41; // index of a level table entry
} SndVoiceFull;

// Reference to a sound voice: its first word is the voice (the voice's link word points back here).
typedef struct SndVoiceRef {
    SndVoice * volatile voice;
} SndVoiceRef;

extern "C" {
void SND_PrepareSeq(u32 track);
void SND_SetTrackPan(u32 track, s32 pan);
void SND_SetPlayerTempoRatio(u32 track, s32 ratio);
void SND_StartPreparedSeq(u32 track);
s32 SND_IsFinishedCommandTag(u32 tag);
u32 SND_GetPlayerStatus(void);
void SndVoice_Release(SndVoice *voice);
void SND_SetTrackAllocatableChannel(u32 track, u32 channels);
u32 SND_GetCurrentCommandTag(void);
void SND_PauseSeq(u32 track);
void SND_StopSeq(u32 track);
void SND_SetPlayerVolume(u32 track, s32 volume);
void SndVoice_Release(SndVoice *voice);
void SndVoice_Reset(SndVoice *voice);
void SndVoice_InsertGlobal(SndVoice *voice);
void SndVoice_InsertSorted(SndList *list, SndVoice *voice);
void Menu_ReleaseRef(void * volatile *ref);
void SndVoice_Stop(SndVoice *voice);
SndVoice *SndVoice_Allocate(s32 priority);
extern SndList data_02183eac;
extern s16 data_020cd280[];
void func_020c1fa0(SndList *list, u8 *before, void *node);
void SndVoice_SetPriority(SndVoice *voice, u8 priority);
}

#endif
