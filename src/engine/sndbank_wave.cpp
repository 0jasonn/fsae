#include "engine/functions.h"
#include "global.h"

extern "C" {
void *SND_GetWaveDataAddress(void *table, s32 index);
void SND_SetWaveDataAddress(void *table, s32 index, void *value);
void SND_InvalidateWaveData(void *obj, void *end);
}

// SndBank_ReleaseWaveData: when the wave address stored for index is obj, clears it, then invalidates obj's wave data
// for size bytes.
extern "C" void SndBank_ReleaseWaveData(void *obj, u32 size, void *table, s32 index);
ARM void SndBank_ReleaseWaveData(void *obj, u32 size, void *table, s32 index) {
    if (obj == SND_GetWaveDataAddress(table, index)) {
        SND_SetWaveDataAddress(table, index, 0);
    }
    SND_InvalidateWaveData(obj, (u8 *)obj + size);
}
