#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/knife_sound.h"

// Knife::Sound::WaveHandle constructor (0x020904b0, no name in the debug build): runs the Handle constructor, then sets
// the vtable (data_0211b080), clears the sound pointer at +0x18 and the bytes at +0x1e and +0x1f. Written as a plain
// function taking self, returning self.

// The WaveHandle fields the constructor sets (0x20 bytes, the Handle part comes first)
typedef struct WaveHandleFields {
    void *vtbl;             // 0x00
    u8 unk_04[0x14];       // 0x04: the Handle part
    void *sound;            // 0x18: sound playing through the handle, NULL while idle
    u8 unk_1c;              // 0x1c
    u8 unk_1d;              // 0x1d
    u8 unk_1e;              // 0x1e
    u8 flag_1f;             // 0x1f: cleared by finalize too
} WaveHandleFields;

extern char data_0211b080[]; // WaveHandle vtable (rodata)

extern "C" void *Knife_Sound_WaveHandle_WaveHandle(void *self);
ARM void *Knife_Sound_WaveHandle_WaveHandle(void *self) {
    WaveHandleFields *wave;

    wave = (WaveHandleFields *)self;
    Knife_Sound_Handle_Handle(self);
    wave->vtbl = (void *)data_0211b080;
    wave->sound = NULL;
    wave->unk_1e = 0;
    wave->flag_1f = 0;
    return self;
}
