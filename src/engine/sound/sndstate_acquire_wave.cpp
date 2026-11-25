#include "global.h"
#include "engine/functions.h"
#include "engine/sound/sndbank_acquire_api.h"
#include "engine/sound/sndstate_lookup_api.h"
#include "engine/sound/sndstate_wave_ref.h"

extern "C" {
void *SndBank_AcquireWaveArc(s32 index, void *record, s32 flag);
u32 SndTable_GetWord14(s32 index);
}

// Resolve the state entry, acquire a wave or wave archive when requested, and optionally return the resolved table word.
s32 func_020c0f90(s32 index, u32 flags, void *record, s32 flag, void **out) {
    SndStateAcquireDescriptor *descriptor;
    void *result;

    descriptor = (SndStateAcquireDescriptor *)SndState_LookupAt14(index);
    if (descriptor == 0) {
        return 5;
    }
    if ((flags & 4) != 0) {
        if ((descriptor->kind & 1) != 0) {
            result = SndBank_AcquireWaveArc((s32)descriptor->index, record, flag);
        } else {
            result = SndBank_AcquireWave((s32)descriptor->index, record, flag);
        }
        if (result == 0) {
            return 9;
        }
    } else {
        result = (void *)SndTable_GetWord14((s32)descriptor->index);
    }
    if (out != 0) {
        *out = result;
    }
    return 0;
}
