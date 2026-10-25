#include "engine/functions.h"
#include "global.h"
#include "engine/snd_seq.h"

// SndVoice_UpdateList: updates every voice of the global list once per frame. A voice that has finished and whose
// track is not in the player status mask is released. Other voices advance their sub-list, get a new volume from three
// table entries and the current sub-list position, and apply it when it changed. A voice in state 2 with a full
// sub-list is stopped, and a pending start is applied.
extern "C" void SndVoice_UpdateList(void);
ARM void SndVoice_UpdateList(void) {
    u32 status;
    SndVoiceFull *voice;
    SndVoiceFull *next;
    s32 volume;
    s32 minVolume;
    s32 levelB;
    s32 levelC;
    s32 levelA;

    status = SND_GetPlayerStatus();
    voice = (SndVoiceFull *)func_020c2064(&data_02183eb8, 0);
    if (voice == 0) {
        return;
    }
    minVolume = -0x8000;
    do {
        next = (SndVoiceFull *)func_020c2064(&data_02183eb8, (u8 *)voice);
        if (voice->finished == 0) {
            if (SND_IsFinishedCommandTag(voice->commandTag) != 0) {
                voice->finished = 1;
            }
        }
        if (voice->finished != 0 && (status & (1 << voice->track)) == 0) {
            SndVoice_Release((SndVoice *)voice);
        } else {
            SndList_Advance(&voice->subList);
            levelB = data_020cd280[voice->unk_41];
            levelC = data_020cd280[voice->unk_40];
            levelA = data_020cd280[*((u8 *)voice->list + 0x20)];
            volume = data_020cd280[(s32)SndList_GetCurrent(&voice->subList) >> 8];
            volume += levelA + (levelC + levelB);
            if (volume < minVolume) {
                volume = minVolume;
            } else if (volume > 0x7fff) {
                volume = 0x7fff;
            }
            if (volume != voice->volume) {
                SND_SetPlayerVolume(voice->track, volume);
                voice->volume = volume;
            }
            if (voice->state == 2 && SndList_IsFull(&voice->subList) != 0) {
                SndVoice_Stop((SndVoice *)voice);
            }
            if (voice->startPending != 0) {
                SND_StartPreparedSeq(voice->track);
                voice->startPending = 0;
            }
        }
        voice = next;
    } while (next != 0);
}

// SndVoicePool_Start: starts a voice from a pool entry for a reference. The reference first releases the voice it
// holds. When the pool is full, its first voice is stopped if its priority is not above the new one. The new voice is
// queued in the pool and linked with the reference both ways.
extern "C" SndVoice *SndVoicePool_Start(SndVoiceRef *ref, s32 pool, s32 priority);
ARM SndVoice *SndVoicePool_Start(SndVoiceRef *ref, s32 pool, s32 priority) {
    u8 *entry;
    SndVoice *voice;

    entry = (u8 *)data_02184304 + pool * 0x24;
    if (ref->voice != 0) {
        Menu_ReleaseRef((void * volatile *)ref);
    }
    if (*(u16 *)(entry + 8) >= *(u32 *)(entry + 0x18)) {
        voice = (SndVoice *)func_020c2064((SndList *)entry, 0);
        if (voice == 0) {
            return 0;
        }
        if (priority < voice->priority) {
            return 0;
        }
        SndVoice_Stop(voice);
    }
    voice = SndVoice_Allocate(priority);
    if (voice == 0) {
        return 0;
    }
    SndVoice_InsertSorted((SndList *)entry, voice);
    ((SndVoiceFull *)voice)->link = (u32 *)ref;
    ref->voice = voice;
    return voice;
}
