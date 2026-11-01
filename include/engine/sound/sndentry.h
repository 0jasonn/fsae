#ifndef WIP_G_SNDENTRY_H
#define WIP_G_SNDENTRY_H

#include "engine/functions.h"
#include "global.h"

// Sound entry (provisional layout from the sound code at 0x020c0130..0x020c02c0). The two hook fields are passed to
// PM_PrependPostExitCallback and PM_AppendPostExitCallback. flags: bit 0 = release pending, bit 1 = started.
typedef struct SndEntry {
    /* 00 */ u8 unk_00[0x8];
    /* 08 */ u8 exitHookA[0x10];
    /* 18 */ u8 exitHookB[0x14];
    /* 2c */ u32 flags;
    /* 30 */ u8 unk_30[0x44 - 0x30];
    /* 44 */ s32 volumeBase;
    /* 48 */ s32 channelIndex; // the timer bit is 1 << channelIndex
    /* 4c */ u32 timerValue;
    /* 50 */ s32 channelCount;
    /* 54 */ u8 channels[0x20]; // channel numbers (one byte each), channelCount of them
} SndEntry;

extern "C" {
extern "C" void SND_StartTimer(u32 timer, u32 unk1, u32 mask, u32 unk3);
extern "C" void SND_StopTimer(u32 timer, u32 unk1, u32 mask, u32 unk3);
extern "C" void PM_PrependPostExitCallback(void *callback);
extern "C" void PM_AppendPostExitCallback(void *callback);
extern "C" void SndChannel_ClearWord4(u32 index);
extern "C" void func_020c2004(void *list, void *entry);
extern "C" s32 SND_CalcChannelVolume(s32 value);
extern "C" void SND_SetChannelVolume(u32 mask, u32 volumeLow, s32 volumeHigh);
}

extern "C" void SndEntry_Start(SndEntry *entry);
extern "C" void SndEntry_StopIfPending(SndEntry *entry);
extern "C" void SndEntry_Stop(SndEntry *entry);
extern "C" void SndEntry_Release(SndEntry *entry);
extern "C" void SndEntry_ApplyVolumes(SndEntry *entry, s32 volumeBase);

#endif
