#ifndef ENGINE_SNDPCM_H
#define ENGINE_SNDPCM_H

#include "engine/functions.h"
#include "sdk/snd/snd_command.h"  // TwlSDK SND command API (and OS_InitMutex)

// PCM voice state: hardware channel, sample rate, playing flag and the command tag of the start request.
typedef struct SndPcmPlayer {
    /* 00 */ s32 channel;
    /* 04 */ s32 rate;
    /* 08 */ s32 playing;
    /* 0c */ s32 unk_0c;
    /* 10 */ u32 tag;
} SndPcmPlayer;

extern "C" {
s32 SndPcmPlayer_Start(SndPcmPlayer *self, s32 format, const void *data, s32 repeat, s32 loopStart, s32 length,
                       s32 rate, s32 volume, s32 divisor, s32 pan);
u32 SND_GetCurrentCommandTag(void);
}

#endif
