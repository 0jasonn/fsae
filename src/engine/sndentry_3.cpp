#include "engine/functions.h"
#include "global.h"
#include "engine/sndentry.h"

// Per-channel volume entry: the offset at +4 is added to the entry's volume base.
typedef struct SndVolumeDesc {
    /* 00 */ u32 unk_00;
    /* 04 */ s32 offset;
} SndVolumeDesc;

extern "C" SndVolumeDesc data_02184794[];

// SndEntry_ApplyVolumes: stores the volume base and sets the volume of each of the entry's channels from the base plus the
// channel's offset.
extern "C" void SndEntry_ApplyVolumes(SndEntry *entry, s32 volumeBase);
ARM void SndEntry_ApplyVolumes(SndEntry *entry, s32 volumeBase) {
    u8 channel;
    s32 i;
    s32 volume;

    entry->volumeBase = volumeBase;
    for (i = 0; i < entry->channelCount; i++) {
        channel = entry->channels[i];
        volume = SND_CalcChannelVolume(entry->volumeBase + data_02184794[channel].offset);
        SND_SetChannelVolume(1 << channel, volume & 0xff, volume >> 8);
    }
}
