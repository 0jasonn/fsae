#include "engine/functions.h"
#include "global.h"
#include "engine/sndvoice.h"

// func_020c0058: frees the voice's record and takes the voice out of its table list. A voice with an owner only
// clears the owner's word at +8 instead.
extern "C" void func_020c0058(SndVoice *voice);
ARM void func_020c0058(SndVoice *voice) {
    if (voice->record == 0) {
        return;
    }
    SndRecord_Free(voice->record);
    if (voice->owner != 0) {
        voice->owner->unk_08 = 0;
        return;
    }
    func_020c2004(data_02184304 + voice->index * 0x24 + 0xc, voice);
}

// SndVoice_SetPriority: takes the voice out of its own list and the global list, stores the priority, then puts it
// back into the sorted lists.
extern "C" void SndVoice_SetPriority(SndVoice *voice, u8 priority);
ARM void SndVoice_SetPriority(SndVoice *voice, u8 priority) {
    SndList *list;

    list = voice->list;
    if (list != 0) {
        func_020c2004(list, voice);
        voice->list = 0;
    }
    func_020c2004(&data_02183eb8, voice);
    voice->priority = priority;
    if (list != 0) {
        func_020bfe90(list, voice);
    }
    func_020bfee0(voice);
}

// SndVoice_ReleaseChannel: unlocks the voice's channel mask and clears it.
extern "C" void SndVoice_ReleaseChannel(SndVoice *voice);
ARM void SndVoice_ReleaseChannel(SndVoice *voice) {
    if (voice->channelMask != 0) {
        SndChannel_Unlock(voice->channelMask);
        voice->channelMask = 0;
        voice->unk_50 = 0;
    }
}
