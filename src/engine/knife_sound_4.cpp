#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/knife_sound_4.h"

// Knife::Sound::WaveHandle, 0x020904e0 to 0x02090578: the two dtors, setFlagByte, finalize and isValid. The rest of the wave handle
// code is in knife_sound_5.cpp; play (0x02090578) is parked in
// scratch/agentD/nonmatching/Knife_Sound_WaveHandle_play.cpp. The destructors stay plain extern "C" functions: their D0/D1 mangled
// names cannot be resolved to symbols.txt yet.

// WaveHandle::~WaveHandle, non-deleting dtor (0x020904e0): runs the Handle base dtor
extern "C" void *Knife_Sound_WaveHandle_dtor_WaveHandle_0904e0(void *self);
ARM void *Knife_Sound_WaveHandle_dtor_WaveHandle_0904e0(void *self) {
    func_0208bee4(self);
    return self;
}

// WaveHandle::~WaveHandle, deleting dtor (0x020904f4): runs the Handle base dtor and frees the block
extern "C" void *Knife_Sound_WaveHandle_dtor_WaveHandle_0904f4(void *self);
ARM void *Knife_Sound_WaveHandle_dtor_WaveHandle_0904f4(void *self) {
    func_0208bee4(self);
    operator delete(self);
    return self;
}

// Knife::Sound::WaveHandle::setFlagByte (0x02090510): stores the flag byte at +0x1e
extern "C" void Knife_Sound_WaveHandle_setFlagByte(void *handle, s32 flag);
ARM void Knife_Sound_WaveHandle_setFlagByte(void *handle, s32 flag) {
    ((u8 *)handle)[0x1e] = flag;
}

namespace Knife {
namespace Sound {

// WaveHandle::finalize (0x02090518): stops the player (if any), clears the player pointer and the paused flag
ARM void WaveHandle::finalize(void) {
    if (player == NULL) {
        return;
    }
    SndChannelRef_Stop(player);
    SndChannelRef_Wait(player);
    SndChannel_UnlockIndex(player);
    player = NULL;
    paused = 0;
}

// WaveHandle::isValid (0x02090550): TRUE while a player is attached and reports itself valid
ARM s32 WaveHandle::isValid(void) const {
    s32 result;

    result = 0;
    if (player != NULL) {
        if (SndChannelRef_Update(player) != 0) {
            result = 1;
        }
    }
    return result;
}

}
}
