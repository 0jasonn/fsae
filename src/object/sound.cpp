#include "engine/functions.h"
#include "global.h"

// Sound module, 0x02076f0c to 0x02076fe0: the volume state, its init, and the song request with the player's id.
//   volumeSet (0x02076f0c), SoundInit (0x02076f40), PlSoundReq (0x02076f6c). SoundReq (0x02076fe0) is in the next unit.

// Volume state at soundVolumeState: volume, the default 0x7f set by SoundInit, and an enable byte
typedef struct SoundVolumeState {
    u16 volume;   // 00
    u16 unk_02;   // 02
    u8 enabled;   // 04, volumeSet does nothing while this is 0
    u8 unk_05[3]; // 05
} SoundVolumeState;

extern SoundVolumeState soundVolumeState;
extern u8 localPlayerIndex; // player index used by PlSoundReq when the game is not wireless
extern "C" void m4aSongNumSetParam(u16 value, u16 mask, s32 current);

// volumeSet (0x02076f0c)
extern "C" void volumeSet(u32 volume);
ARM void volumeSet(u32 volume) {
    if (soundVolumeState.enabled == 0) {
        return;
    }
    m4aSongNumSetParam((u16)volume, 0xffff, soundVolumeState.volume);
}

// SoundInit (0x02076f40): clears the state, then sets the default volume
extern "C" void SoundInit(void);
ARM void SoundInit(void) {
    func_02029a50(&soundVolumeState, 8);
    soundVolumeState.unk_02 = 0;
    soundVolumeState.volume = 0x7f;
}

// PlSoundReq (0x02076f6c): requests a sound. For a type 1 object that belongs to another player, the id is moved to
// the upper half of the range (ids below 0xc8 get 0xc8 added).
extern "C" void PlSoundReq(Entity *e, u32 sound);
ARM void PlSoundReq(Entity *e, u32 sound) {
    u8 playerIndex;

    playerIndex = localPlayerIndex;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        playerIndex = *Knife_Single_SinglePlay_GetInstance();
    }
    if (e->objKind == 1 && e->type != playerIndex) {
        u16 id = (u16)sound;
        if (id < 0xc8) {
            sound = (sound & 0xffff0000) | (id + 0xc8);
        }
    }
    SoundReq(sound);
}
