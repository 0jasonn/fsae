#include "engine/functions.h"
#include "global.h"
#include "engine/knife_sound_handle.h"
// Functions in this file (original names from the debug build):
//   Knife::Sound::Handle::volume (0x0208bf60), Knife::Sound::Handle::stop (0x0208bfe4)

// volume(handle, volume, frames) (0x0208bf60): starts a volume fade of frames frames to volume. With no frames the level is
// set at once.
void Knife_Sound_Handle_volume(void *self, s32 volume, s32 frames) {
    KnifeSoundHandle *h = (KnifeSoundHandle *)self;
    if (h->flags & 0x4) {
        h->pauseSlot(0);
    }
    if (frames <= 0) {
        h->setVolume(volume);
        h->flags &= ~0x1;
        return;
    }
    h->fadeFrames = frames;
    h->volumeStep = _s32_div_f((volume - h->curVolume) << 8, frames);
    h->curVolume = volume;
    h->flags = 0x1;
}

void Knife_Sound_Handle_stop(void *self, s32 frames, s32 pause) {
    KnifeSoundHandle *h = (KnifeSoundHandle *)self;
    Knife_Sound_Handle_volume(self, 0, frames);
    if (frames > 0) {
        if (pause != 0) {
            h->panFlags |= 0x4;
        } else {
            h->panFlags |= 0x2;
        }
    } else {
        if (pause != 0) {
            h->pauseSlot(1);
        } else {
            h->stopSlot();
        }
    }
}

