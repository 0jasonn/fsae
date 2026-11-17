#include "engine/functions.h"
#include "engine/menusound.h"
#include "engine/sound/snd_seq.h"

void SndRef_setPriority(void * volatile *ref, u8 priority) {
    if (*ref != NULL) {
        SND_SetPlayerChannelPriority(((SndVoiceFull *)*ref)->track, priority);
    }
}

void SndRef_setPan(void * volatile *ref, u32 trackMask, s32 pan) {
    if (*ref != NULL) {
        SND_SetTrackPan(((SndVoiceFull *)*ref)->track, trackMask, pan);
    }
}
