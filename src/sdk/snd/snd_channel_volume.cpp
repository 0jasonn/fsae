#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/snd/snd_util.h"

// SND_CalcChannelVolume(value) (0x0201ba08): converts an attenuation (-723..0) into the hardware volume word: the
// table byte plus a shift in bits 8-9 (3, 2, 1 or 0 for values below -240, -120, -60 or above).
s32 SND_CalcChannelVolume(s32 value) {
    u8 volume;
    s32 shift;
    u32 index;

    if (value < -723) {
        value = -723;
    } else if (value > 0) {
        value = 0;
    }
    index = value + 723;
    volume = data_020cd380[index];
    if (value < -240) {
        shift = 3;
    } else if (value < -120) {
        shift = 2;
    } else if (value < -60) {
        shift = 1;
    } else {
        shift = 0;
    }
    return (u16)(volume | (shift << 8));
}
