#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"
#include "engine/sndstop.h"

extern "C" {
void SND_StopTimer(u32 timer, u32 unk1, u32 mask, u32 unk3);
u32 SND_GetCurrentCommandTag(void);
void SND_FlushCommand(u32 mode);
void SND_WaitForCommandProc(u32 tag);
void SND_SetChannelVolume(u32 mask, u32 volumeLow, s32 volumeHigh);
void SndChannel_ClearWord0(u32 mask);
void SndChannel_Unlock(u32 mask);
void SndChannel_ClearWord4(u32 index);
void func_020c0350(void);
}

// func_020c02d0: while the stop state is active in mode 0, advances the volume curve and, when the curve is
// full (if fullCheck is set), finishes the stop. Otherwise the timer channel gets the new volume when it changed.
extern "C" void func_020c02d0(void);
ARM void func_020c02d0(void) {
    SndStopState *state;
    s32 volume;

    state = &data_0218485c;
    if (state->active == 0) {
        return;
    }
    if (state->mode != 0) {
        return;
    }
    SndList_Advance(&state->curve);
    if (state->fullCheck != 0 && SndList_IsFull(&state->curve) != 0) {
        func_020c0350();
        return;
    }
    volume = (s32)SndList_GetCurrent(&state->curve) >> 8;
    if (volume == state->volume) {
        return;
    }
    SND_SetChannelVolume(state->timerA, volume, 0);
    state->volume = volume;
}

// func_020c0350: stops the stop state's timer (on its channel when the index is not negative), drains the message
// queue, releases the channel bits and clears the active flag. Mode 1 also resets the output selector.
extern "C" void func_020c0350(void);
ARM void func_020c0350(void) {
    SndStopState *state;
    u32 mask;
    u32 tag;
    s32 hasChannel;

    state = &data_0218485c;
    if (state->active == 0) {
        return;
    }
    hasChannel = state->channelIndex >= 0;
    mask = hasChannel ? (1 << state->channelIndex) : 0;
    SND_StopTimer(state->timerA, state->timerB, mask, 0);
    if (hasChannel) {
        tag = SND_GetCurrentCommandTag();
        SND_FlushCommand(1);
        SND_WaitForCommandProc(tag);
        while (OS_ReceiveMessage(data_0218481c, 0, 0) != 0) {
        }
    }
    if (state->timerB != 0) {
        SndChannel_ClearWord0(state->timerB);
    }
    if (state->channelMask != 0) {
        SndChannel_Unlock(state->channelMask);
    }
    if (hasChannel) {
        SndChannel_ClearWord4(state->channelIndex);
    }
    if (state->mode == 1) {
        SND_SetOutputSelector(0, 0, 0, 0);
    }
    state->active = 0;
}
