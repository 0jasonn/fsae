#include "engine/functions.h"
#include "global.h"

extern "C" {
void SND_StopTimer(u32 timer, u32 unk1, u32 mask, u32 unk3);
void SND_StartTimer(u32 timer, u32 unk1, u32 mask, u32 unk3);
u32 SND_GetCurrentCommandTag(void);
void SND_FlushCommand(u32 mode);
void SND_WaitForCommandProc(u32 tag);
void OSi_CpuClear32(u32 value, void *dst, u32 size);
void DC_FlushRange(void *start, u32 size);
}

// Global stop state at data_0218485c (provisional): active flag at +0, two buffers with their size, two timer values
// and a channel index.
typedef struct SndStopState {
    /* 00 */ s32 active;
    /* 04 */ u8 unk_04[0x0c - 0x04];
    /* 0c */ void *bufferA;
    /* 10 */ void *bufferB;
    /* 14 */ u32 bufferSize;
    /* 18 */ u8 unk_18[0x1c - 0x18];
    /* 1c */ s32 unk_1c;
    /* 20 */ u8 unk_20[0x24 - 0x20];
    /* 24 */ u32 timerA;
    /* 28 */ u32 timerB;
    /* 2c */ s32 channelIndex;
} SndStopState;

extern "C" SndStopState data_0218485c;

// SndSys_StopActiveTimer: when the stop state is active, stops its timer (the channel's bit, or none when the index is
// negative), then flushes the command queue and waits for the last command.
extern "C" void SndSys_StopActiveTimer(void);
ARM void SndSys_StopActiveTimer(void) {
    SndStopState *state;
    s32 index;
    u32 mask;
    u32 tag;

    state = &data_0218485c;
    if (state->active == 0) {
        return;
    }
    index = state->channelIndex;
    mask = (index >= 0) ? (1 << index) : 0;
    SND_StopTimer(state->timerA, state->timerB, mask, 0);
    tag = SND_GetCurrentCommandTag();
    SND_FlushCommand(1);
    SND_WaitForCommandProc(tag);
}

// SndSys_StartActiveTimer: when the stop state is active, clears and flushes its two buffers, then starts its timer on the
// channel's bit (or none when the index is negative).
extern "C" void SndSys_StartActiveTimer(void);
ARM void SndSys_StartActiveTimer(void) {
    SndStopState *state;
    u32 mask;

    state = &data_0218485c;
    if (state->active == 0) {
        return;
    }
    mask = 0;
    state->unk_1c = 0;
    OSi_CpuClear32(0, state->bufferA, state->bufferSize);
    OSi_CpuClear32(0, state->bufferB, state->bufferSize);
    DC_FlushRange(state->bufferA, state->bufferSize);
    DC_FlushRange(state->bufferB, state->bufferSize);
    if (state->channelIndex >= 0) {
        mask = 1 << state->channelIndex;
    }
    SND_StartTimer(state->timerA, state->timerB, mask, 0);
}
