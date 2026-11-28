#include "engine/functions.h"
#include "global.h"
#include "engine/sound/sndbank_wave_api.h"
#include "sdk/snd/snd_bank.h"

extern "C" {
void SND_InvalidateWaveData(void *obj, void *end);
}

// SndBank_ReleaseWaveData: when the wave address stored for index is obj, clears it, then invalidates obj's wave data
// for size bytes.
void SndBank_ReleaseWaveData(void *obj, u32 size, void *table, s32 index) {
    if (obj == SND_GetWaveDataAddress((SndWaveArc *)table, index)) {
        SND_SetWaveDataAddress((SndWaveArc *)table, index, 0);
    }
    SND_InvalidateWaveData(obj, (u8 *)obj + size);
}
