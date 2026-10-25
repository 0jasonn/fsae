#ifndef WIP_G_SNDSTOP_H
#define WIP_G_SNDSTOP_H

#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"

// Global stop state at data_0218485c (fuller layout than the one in src/engine/sndsys_6.cpp). mode is 0 or 1; the
// list at +0x3c holds the volume curve, its current value is the volume (value >> 8) applied to the timer channel.
typedef struct SndStopState {
    /* 00 */ s32 active;
    /* 04 */ s32 mode;
    /* 08 */ u8 unk_08[0x0c - 0x08];
    /* 0c */ void *bufferA;
    /* 10 */ void *bufferB;
    /* 14 */ u32 bufferSize;
    /* 18 */ u8 unk_18[0x1c - 0x18];
    /* 1c */ s32 unk_1c;
    /* 20 */ u32 channelMask;
    /* 24 */ u32 timerA;
    /* 28 */ u32 timerB;
    /* 2c */ s32 channelIndex;
    /* 30 */ u8 unk_30[0x3c - 0x30];
    /* 3c */ SndList curve;
    /* 4c */ u32 fullCheck;
    /* 50 */ s32 volume;
} SndStopState;

extern "C" {
extern SndStopState data_0218485c;
extern u8 data_0218481c[];
s32 OS_ReceiveMessage(void *queue, void *message, s32 flags);
void SND_SetOutputSelector(u32 a, u32 b, u32 c, u32 d);
}

extern "C" void func_020c02d0(void);
extern "C" void func_020c0350(void);

#endif
