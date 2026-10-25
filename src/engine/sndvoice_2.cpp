#include "engine/functions.h"
#include "global.h"
#include "engine/snd_seq.h"

// SndVoice_Setup: an active voice (state nonzero) with a flag gets its sub-list set up with that capacity, its
// priority cleared and its state set to 2. A zero flag stops the voice instead.
extern "C" void SndVoice_Setup(SndVoice *voice, s32 flag);
ARM void SndVoice_Setup(SndVoice *voice, s32 flag) {
    SndVoiceFull *v = (SndVoiceFull *)voice;

    if (v == 0 || v->state == 0) {
        return;
    }
    if (flag == 0) {
        SndVoice_Stop(voice);
        return;
    }
    SndList_Setup(&v->subList, 0, flag);
    SndVoice_SetPriority(voice, 0);
    v->state = 2;
}

// SndVoice_SetPaused: pauses or resumes the voice's sequence when the flag differs from the stored one.
extern "C" void SndVoice_SetPaused(SndVoice *voice, s32 paused);
ARM void SndVoice_SetPaused(SndVoice *voice, s32 paused) {
    SndVoiceFull *v = (SndVoiceFull *)voice;

    if (v == 0 || paused == v->paused) {
        return;
    }
    SND_PauseSeq(v->track);
    v->paused = paused;
}

// SndVoicePool_Acquire: takes a voice from the free list of a pool group, links it to the owner and returns its
// record (cleared). Returns 0 when the free list is empty.
extern "C" SndRecord *SndVoicePool_Acquire(s32 group, SndVoiceOwner *owner);
ARM SndRecord *SndVoicePool_Acquire(s32 group, SndVoiceOwner *owner) {
    u8 *pool;
    SndVoiceFull *node;

    pool = (u8 *)data_02184304 + group * 0x24;
    node = (SndVoiceFull *)func_020c2064((SndList *)(pool + 0xc), 0);
    if (node == 0) {
        return 0;
    }
    func_020c2004((SndList *)(pool + 0xc), node);
    node->owner = owner;
    owner->unk_08 = (u32)node;
    SndRecord_Clear(node->record);
    return node->record;
}

// SndVoice_Reset: clears the voice's flags and tag, then sets up its sub-list.
extern "C" void SndVoice_Reset(SndVoice *voice);
ARM void SndVoice_Reset(SndVoice *voice) {
    SndVoiceFull *v = (SndVoiceFull *)voice;

    v->paused = 0;
    v->finished = 0;
    v->startPending = 0;
    v->unk_34 = 0;
    v->volume = 0;
    v->unk_40 = 0x7f;
    v->unk_41 = 0x7f;
    SndList_Clear(&v->subList);
    SndList_Setup(&v->subList, (u8 *)0x7f00, 1);
}

// SndVoice_InsertSorted: queues a voice into a list before the first node of a lower priority (the node's priority
// is compared with the voice's), then links the voice to the list.
extern "C" void SndVoice_InsertSorted(SndList *list, SndVoice *voice);
ARM void SndVoice_InsertSorted(SndList *list, SndVoice *voice) {
    u8 *node;

    node = func_020c2064(list, 0);
    while (node != 0) {
        if (voice->priority < ((SndVoice *)node)->priority) {
            break;
        }
        node = func_020c2064(list, node);
    }
    func_020c1fa0(list, node, voice);
    voice->list = list;
}

// SndVoice_InsertGlobal: the same sorted insert into the global voice list.
extern "C" void SndVoice_InsertGlobal(SndVoice *voice);
ARM void SndVoice_InsertGlobal(SndVoice *voice) {
    u8 *node;

    node = func_020c2064(&data_02183eb8, 0);
    while (node != 0) {
        if (voice->priority < ((SndVoice *)node)->priority) {
            break;
        }
        node = func_020c2064(&data_02183eb8, node);
    }
    func_020c1fa0(&data_02183eb8, node, voice);
}

// SndVoice_Stop: lowers the volume of a voice in state 2, stops its sequence and releases it.
extern "C" void SndVoice_Stop(SndVoice *voice);
ARM void SndVoice_Stop(SndVoice *voice) {
    SndVoiceFull *v = (SndVoiceFull *)voice;

    if (v->state == 2) {
        SND_SetPlayerVolume(v->track, -723);
    }
    SND_StopSeq(v->track);
    SndVoice_Release(voice);
}

// SndVoice_Allocate: takes a voice for the given priority. It comes from the free list, or else the first voice of
// the global list is stopped when its priority is not above the new one. The voice then goes into the global list.
extern "C" SndVoice *SndVoice_Allocate(s32 priority);
ARM SndVoice *SndVoice_Allocate(s32 priority) {
    SndVoiceFull *node;

    node = (SndVoiceFull *)func_020c2064(&data_02183eac, 0);
    if (node == 0) {
        node = (SndVoiceFull *)func_020c2064(&data_02183eb8, 0);
        if (priority < node->priority) {
            return 0;
        }
        SndVoice_Stop((SndVoice *)node);
    }
    func_020c2004(&data_02183eac, node);
    node->priority = priority;
    SndVoice_InsertGlobal((SndVoice *)node);
    return (SndVoice *)node;
}

// SndVoice_Release: unlinks the voice from its list and the global list, clears its record's link and returns it to
// the free list. The voice's record goes back to its group's list.
extern "C" void SndVoice_Release(SndVoice *voice);
ARM void SndVoice_Release(SndVoice *voice) {
    SndVoiceFull *v = (SndVoiceFull *)voice;
    SndList *list;
    SndRecord *record;

    if (v->link != 0) {
        *v->link = 0;
        v->link = 0;
    }
    list = v->list;
    func_020c2004(list, v);
    record = v->record;
    v->list = 0;
    if (record != 0) {
        SndList_Append((SndList *)((u8 *)list + 0xc), (u8 *)record);
        *(u32 *)((u8 *)v->record + 0xc) = 0;
        v->record = 0;
    }
    func_020c2004(&data_02183eb8, v);
    SndList_Append(&data_02183eac, (u8 *)v);
    v->state = 0;
}
