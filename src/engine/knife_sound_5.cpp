#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/knife_sound_4.h"

// Knife::Sound::WaveHandle, 0x02090634 to 0x02090708: setVolume, setPan, setStop and setPause. Follows play (parked).

namespace Knife {
namespace Sound {

// WaveHandle::setVolume (0x02090634): sets the volume on the player unless paused, and keeps it in the slot
ARM void WaveHandle::setVolume(s32 volume) {
    if (isValid() == 0) {
        return;
    }
    if (paused == 0) {
        func_020bf6a8(player, volume);
    }
    this->volume = (u16)volume;
}

// WaveHandle::setPan (0x02090674): sets the pan on the player
ARM void WaveHandle::setPan(s32 pan) {
    if (isValid() == 0) {
        return;
    }
    func_020bf6d0(player, pan);
}

// WaveHandle::setStop (0x020906a4): stops the player
ARM void WaveHandle::setStop(void) {
    if (isValid() == 0) {
        return;
    }
    func_020bf66c(player);
}

// WaveHandle::setPause (0x020906cc): pauses the player (volume 0) or resumes it at the slot volume, and records the flag
ARM void WaveHandle::setPause(s32 pause) {
    s32 level;

    if (isValid() == 0) {
        return;
    }
    level = 0;
    if (pause == 0) {
        level = volume;
    }
    func_020bf6a8(player, level);
    paused = (u8)pause;
}

}
}
