#include "engine/functions.h"
#include "global.h"

// Knife::Sound::Handle, the constructor and reset (0x0208beac, 0x0208bef8). A handle is a byte record: the vtable pointer
// is at +0, reset clears the play fields and sets the default volume (0x7f00 at +0x0a, 0x7f at +0x0e) and pan (0x4000
// at +0x12, 0x40 at +0x16).
extern u8 data_0211ab64[]; // Knife::Sound::Handle vtable

extern "C" void Knife_Sound_Handle_reset(void *self);

ARM void Knife_Sound_Handle_reset(void *self) {
    u8 *h;

    h = (u8 *)self;
    h[0x0a] = 0;
    h[0x0b] = 0;
    h[0x12] = 0;
    h[0x13] = 0;
    *(u32 *)(h + 0x04) = 0;
    h[0x08] = 0;
    h[0x09] = 0;
    h[0x0c] = 0;
    h[0x0d] = 0;
    h[0x0f] = 0;
    h[0x10] = 0;
    h[0x11] = 0;
    h[0x14] = 0;
    h[0x15] = 0;
    h[0x17] = 0;
    *(u16 *)(h + 0x0a) = 0x7f00;
    h[0x0e] = 0x7f;
    *(u16 *)(h + 0x12) = 0x4000;
    h[0x16] = 0x40;
}
