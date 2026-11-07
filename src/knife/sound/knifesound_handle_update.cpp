#include "engine/functions.h"
#include "global.h"
#include "engine/knife_sound_handle.h"

// Functions in this file (original names from the debug build):
//   Knife::Sound::Handle::update (0x0208c068)

// update(handle) (0x0208c068): advances the volume and pan fades by one frame and forwards the clamped levels
void Knife_Sound_Handle_update(void *self) {
    KnifeSoundHandle *h = (KnifeSoundHandle *)self;
    s32 level;

    if (h->flags & 0x1) {
        h->fadeFrames = h->fadeFrames - 1;
        if (h->fadeFrames == 0) {
            h->flags &= ~0x1;
            h->volume = h->curVolume << 8;
            if (h->flags & 0x4) {
                h->pauseSlot(1);
            }
            if (h->flags & 0x2) {
                h->stopSlot();
            }
        } else {
            h->volume = h->volume + h->volumeStep;
        }
        level = h->volume >> 8;
        if (level < 0) {
            level = 0;
        } else if (level > 0x7f) {
            level = 0x7f;
        }
        h->setVolume(level);
    }
    if (h->panFlags & 0x1) {
        h->panFrames = h->panFrames - 1;
        if (h->panFrames == 0) {
            h->panFlags &= ~0x1;
            h->pan = h->panTarget << 8;
        } else {
            h->pan = h->pan + h->panStep;
        }
        level = h->pan >> 8;
        if (level < 0) {
            level = 0;
        } else if (level > 0x7f) {
            level = 0x7f;
        }
        h->setPan(level);
    }
}
