#ifndef WIP_K_KNIFE_SOUND_HANDLE_H
#define WIP_K_KNIFE_SOUND_HANDLE_H

#include "types.h"

// Knife::Sound::Handle as the volume, stop and update code see it. Only the virtual slots they call are named; the class
// is never constructed here, so no vtable is emitted. Levels are 8.8 fixed point; the integer part goes to the slots.
class KnifeSoundHandle {
public:
    virtual void slot0(void);
    virtual void slot1(void);
    virtual void slot2(void);
    virtual void setVolume(s32 volume);   // slot 3
    virtual void setPan(s32 pan);         // slot 4
    virtual void stopSlot(void);          // slot 5
    virtual void pauseSlot(s32 resume);   // slot 6

    u8 unk_04[4];
    u16 fadeFrames;     // 0x08: frames left in the volume fade
    s16 volume;         // 0x0a: current volume, 8.8
    s16 volumeStep;     // 0x0c: volume added every frame of the fade
    u8 curVolume;       // 0x0e: volume the last fade was set to
    u8 flags;           // 0x0f: bit0 volume fade running, bit1 stop at the end, bit2 pause at the end
    u16 panFrames;      // 0x10: frames left in the pan fade
    s16 pan;            // 0x12: current pan, 8.8
    s16 panStep;        // 0x14: pan added every frame of the fade
    u8 panTarget;       // 0x16: pan the fade ends at
    u8 panFlags;        // 0x17: bit0 pan fade running (stop sets bits 1 and 2 here)
};

extern "C" {
void Knife_Sound_Handle_volume(void *self, s32 volume, s32 frames);
void Knife_Sound_Handle_stop(void *self, s32 frames, s32 pause);
void Knife_Sound_Handle_update(void *self);
}

#endif
