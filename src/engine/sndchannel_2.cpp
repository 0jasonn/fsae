#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names; the channel reference holds the channel index at +0 and the state words):
//   SndChannelRef_Stop (SndChannelRef_Stop), SndChannelRef_SetVolume (SndChannelRef_SetVolume), SndChannelRef_SetPan (SndChannelRef_SetPan),
//   SndChannelRef_Update (SndChannelRef_Update), SndChannelRef_Wait (SndChannelRef_Wait)

extern "C" {
void SND_StopTimer(u32 mask, u32 a, u32 b, u32 c);
void SND_SetChannelVolume(u32 mask, s32 volume, s32 fade);
void SND_SetChannelPan(u32 mask, s32 pan);
s32 SND_IsFinishedCommandTag(u32 tag);
u32 SND_GetChannelStatus(void);
u32 SND_GetCurrentCommandTag(void);
void SND_FlushCommand(u32 mode);
void SND_WaitForCommandProc(u32 tag);
}

// A channel reference: the channel index, a flag, the active flag, a finished flag and the command tag.
typedef struct SndChannelRef {
    u32 index;
    u32 unk_04;
    u32 active;
    u32 finished;
    u32 tag;
} SndChannelRef;

// SndChannelRef_Stop (0x020bf66c): stops the channel timer of an active reference and clears the active flag.
extern "C" void SndChannelRef_Stop(SndChannelRef *ref);
ARM void SndChannelRef_Stop(SndChannelRef *ref) {
    if (ref->active == 0) {
        return;
    }
    SND_StopTimer(1 << ref->index, 0, 0, 0);
    ref->active = 0;
}

// SndChannelRef_SetVolume (0x020bf6a8): sets the volume of the channel of an active reference.
extern "C" void SndChannelRef_SetVolume(SndChannelRef *ref, s32 volume);
ARM void SndChannelRef_SetVolume(SndChannelRef *ref, s32 volume) {
    if (ref->active == 0) {
        return;
    }
    SND_SetChannelVolume(1 << ref->index, volume, 0);
}

// SndChannelRef_SetPan (0x020bf6d0): sets the pan of the channel of an active reference.
extern "C" void SndChannelRef_SetPan(SndChannelRef *ref, s32 pan);
ARM void SndChannelRef_SetPan(SndChannelRef *ref, s32 pan) {
    if (ref->active == 0) {
        return;
    }
    SND_SetChannelPan(1 << ref->index, pan);
}

// SndChannelRef_Update (0x020bf6f4): returns 1 while the command of the reference is pending, otherwise checks whether
// the channel still plays and clears the active flag when it stopped.
extern "C" s32 SndChannelRef_Update(SndChannelRef *ref);
ARM s32 SndChannelRef_Update(SndChannelRef *ref) {
    if (ref->active == 0) {
        return 0;
    }
    if (ref->finished == 0) {
        if (SND_IsFinishedCommandTag(ref->tag) == 0) {
            return 1;
        }
        ref->finished = 1;
    }
    if (SND_GetChannelStatus() & (1 << ref->index)) {
        return 1;
    }
    ref->active = 0;
    return 0;
}

// SndChannelRef_Wait (0x020bf750): waits for the command of an idle reference (flushing its channel), or for the
// command and then for the channel to stop when the reference is active.
extern "C" void SndChannelRef_Wait(SndChannelRef *ref);
ARM void SndChannelRef_Wait(SndChannelRef *ref) {
    u32 tag;

    if (ref->active == 0) {
        if ((SND_GetChannelStatus() & (1 << ref->index)) == 0) {
            return;
        }
        tag = SND_GetCurrentCommandTag();
        SND_FlushCommand(1);
        SND_WaitForCommandProc(tag);
        return;
    }
    if (ref->finished == 0) {
        SND_WaitForCommandProc(ref->tag);
        ref->finished = 1;
    }
    while (SND_GetChannelStatus() & (1 << ref->index)) {
    }
}
