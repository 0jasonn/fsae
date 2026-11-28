#ifndef SDK_SND_SND_UTIL_H
#define SDK_SND_SND_UTIL_H

// TwlSDK SND utilities (snd_util.c).
#include "types.h"

// Volume table: one byte per attenuation step, indexed by (attenuation + 723).
extern const u8 data_020cd380[];

extern "C" {
s32 SND_CalcChannelVolume(s32 value);
}

#endif
