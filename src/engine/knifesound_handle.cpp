#include "engine/functions.h"
#include "global.h"

// Knife::Sound::Handle, the constructor and reset (0x0208beac, 0x0208bef8). A handle is a byte record: the vtable pointer
// is at +0, reset clears the play fields and sets the default volume (0x7f00 at +0x0a, 0x7f at +0x0e) and pan (0x4000
// at +0x12, 0x40 at +0x16).
extern u8 data_0211ab64[]; // Knife::Sound::Handle vtable

extern "C" void Knife_Sound_Handle_reset(void *self);

extern "C" void *Knife_Sound_Handle_Handle(void *self);
ARM void *Knife_Sound_Handle_Handle(void *self) {
    *(void **)self = data_0211ab64;
    Knife_Sound_Handle_reset(self);
    return self;
}
