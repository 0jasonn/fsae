#ifndef SDK_SND_SND_CHANNEL_H
#define SDK_SND_SND_CHANNEL_H

// TwlSDK SND channel information (snd_channel.c): reads the state of one hardware channel out of the sound driver work.
#include "types.h"

// One extended channel of the sound driver work (SNDExChannel, 0x54 bytes). Only the fields SND_ReadChannelInfo reads
// are named.
typedef struct SndExChannel {
    u8 unk_00[2];           // 0x00
    u8 envelopeStatus;      // 0x02
    u8 activeFlag : 1;      // 0x03
    u8 unused_03 : 7;
    u8 unk_04[0x1f];        // 0x04
    u8 pan;                 // 0x23
    u16 volumeData;         // 0x24: low byte volume, high byte the volume shift (0 none, 1 half, 2 quarter, 3 sixteenth)
    u8 unk_26[0x2e];        // 0x26
} SndExChannel; // 0x54 bytes

// Sound driver work as far as SND_ReadChannelInfo reads it.
typedef struct SndChannelWork {
    SndExChannel channels[16];  // 0x0000
    u8 unk_540[0xc40];          // 0x0540
    u32 channelRegs[16];        // 0x1180: the SOUNDxCNT register words
    u32 unk_11c0;               // 0x11c0
    u32 lockedChannels;         // 0x11c4: bit mask of the channels reserved by the user
} SndChannelWork;

// Result of SND_ReadChannelInfo.
typedef struct SndChannelInfo {
    u32 activeFlag : 1;         // 0x00
    s32 lockFlag : 1;
    u32 unused : 30;
    u16 volume;                 // 0x04
    u8 pan;                     // 0x06
    u8 pad_07;                  // 0x07
    u32 envelopeStatus;         // 0x08
} SndChannelInfo;

extern "C" {
s32 SND_ReadChannelInfo(const SndChannelWork *work, s32 channel, SndChannelInfo *info);
}

#endif
