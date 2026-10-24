#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/knife_sound.h"

// Knife::Sound::WaveHandle, 0x02090510 (the first function of the wave handle code; the rest of it is not written yet).

extern "C" void Knife_Sound_WaveHandle_setFlagByte(void *handle, s32 flag);
ARM void Knife_Sound_WaveHandle_setFlagByte(void *handle, s32 flag) {
    ((u8 *)handle)[0x1e] = flag;
}
