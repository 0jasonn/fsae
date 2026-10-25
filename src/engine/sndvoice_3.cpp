#include "engine/functions.h"
#include "global.h"
#include "engine/snd_seq.h"

// SndVoiceRef_SetTempo: sets the tempo ratio of the track of the voice the reference holds, when there is one.
extern "C" void SndVoiceRef_SetTempo(SndVoiceRef *ref, s32 tempo);
ARM void SndVoiceRef_SetTempo(SndVoiceRef *ref, s32 tempo) {
    if (ref->voice != 0) {
        SND_SetPlayerTempoRatio(((SndVoiceFull *)ref->voice)->track, tempo);
    }
}
