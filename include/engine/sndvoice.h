#ifndef WIP_G_SNDVOICE_H
#define WIP_G_SNDVOICE_H

#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"
#include "engine/sndrecord.h"

// Sound voice (provisional name): one playing sound with a record heap, a priority and a channel mask. The voice
// table at data_02184304 has 0x24-byte entries, each with a list at +0xc; a voice selects its entry by index at +0x10.
typedef struct SndVoiceOwner {
    u8 unk_00[0x8];
    u32 unk_08;
} SndVoiceOwner;

typedef struct SndVoice {
    /* 00 */ u8 unk_00[0x4];
    /* 04 */ SndList *list;
    /* 08 */ SndRecord *record;
    /* 0c */ SndVoiceOwner *owner;
    /* 10 */ s32 index;
    /* 14 */ u8 unk_14[0x3d - 0x14];
    /* 3d */ u8 priority;
    /* 3e */ u8 unk_3e[0x4c - 0x3e];
    /* 4c */ u32 channelMask;
    /* 50 */ u32 unk_50;
} SndVoice;

extern "C" {
extern u8 data_02184304[];
extern SndList data_02183eb8;
void SndRecord_Free(SndRecord *record);
void SndChannel_Unlock(u32 mask);
void func_020c2004(void *list, void *node);
void SndVoice_InsertSorted(SndList *list, SndVoice *voice);
void SndVoice_InsertGlobal(SndVoice *voice);
}

extern "C" void func_020c0058(SndVoice *voice);
extern "C" void SndVoice_SetPriority(SndVoice *voice, u8 priority);
extern "C" void SndVoice_ReleaseChannel(SndVoice *voice);

#endif
