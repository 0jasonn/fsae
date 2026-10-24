#ifndef WIP_D_KNIFE_SOUND_4_H
#define WIP_D_KNIFE_SOUND_4_H

#include "types.h"

// NitroSDK wave format (NNSSndWaveFormat)
enum NNSSndWaveFormat {
    NNS_SND_WAVE_FORMAT_PCM8 = 0,
    NNS_SND_WAVE_FORMAT_PCM16 = 1,
    NNS_SND_WAVE_FORMAT_ADPCM = 2
};

namespace Knife {
namespace Sound {

// Knife::Sound::WaveHandle (0x20 bytes): one sound slot that plays a wave on a sound player. Its vtable has the
// dtor in slots 0 and 1 (not written here) and isValid in slot 2. The fields are named from how the methods use them;
// the byte and halfword values stored by play are guesses from the callers.
class WaveHandle {
public:
    virtual void dtorSlot(void);
    virtual void deletingDtorSlot(void);
    virtual s32 isValid(void) const;

    void finalize(void);
    BOOL play(NNSSndWaveFormat format, const void *data, s32 channel, s32 loopStart, s32 loopEnd, s32 loopCount,
              s32 volume, s32 pitch, s32 pan);
    void setVolume(s32 volume);
    void setPan(s32 pan);
    void setStop(void);
    void setPause(s32 pause);

    u8 unk_04[0x0a - 0x04];
    u16 mixVolume;      // 0x0a: volume << 8 (low byte of the volume argument)
    u8 unk_0c[0x0e - 0x0c];
    u8 volumeByte;      // 0x0e: volume argument of play
    u8 unk_0f[0x12 - 0x0f];
    u16 mixPan;         // 0x12: pan << 8 (low byte of the pan argument)
    u8 unk_14[0x16 - 0x14];
    u8 panByte;         // 0x16: pan argument of play
    u8 unk_17;
    void *player;       // 0x18: sound player, NULL while the slot is idle
    u16 volume;         // 0x1c
    u8 playerType;      // 0x1e: sound player kind, set by setFlagByte before play
    u8 paused;          // 0x1f
};

}
}

extern "C" {
// Sound player and Handle calls used by WaveHandle (dsd names)
void *SndChannel_Reserve(u8 playerType);
s32 func_020bf540(void *player, NNSSndWaveFormat format, const void *data, s32 channel, s32 loopStart, s32 loopEnd,
                  s32 loopCount, s32 volume, s32 pitch, s32 pan);
s32 SndChannelRef_Update(void *player);
void SndChannelRef_SetVolume(void *player, s32 volume);
void SndChannelRef_SetPan(void *player, s32 pan);
void SndChannelRef_Stop(void *player);
void SndChannelRef_Wait(void *player);
void SndChannel_UnlockIndex(void *player);
void func_0208bee4(void *handle);
}

#endif
