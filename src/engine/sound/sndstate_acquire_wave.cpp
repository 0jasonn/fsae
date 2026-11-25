#include "global.h"
#include "engine/functions.h"
#include "engine/sound/sndbank_acquire_api.h"
#include "engine/sound/sndstate_lookup_api.h"

extern "C" {
void *SndBank_AcquireWaveArc(s32 index, void *record, s32 flag);
u32 SndTable_GetWord14(s32 index);
}

typedef struct SndStateAcquireDescriptor {
    u32 index : 24;
    u32 kind : 8;
} SndStateAcquireDescriptor;

// Resolve the state entry, acquire a wave or wave archive when requested, and optionally return the resolved table word.
s32 func_020c0f90(s32 index, u32 flags, void *record, s32 flag, u32 *out) {
    SndStateAcquireDescriptor *descriptor;
    u32 result;

    descriptor = (SndStateAcquireDescriptor *)SndState_LookupAt14(index);
    if (descriptor == 0) {
        return 5;
    }
    if ((flags & 4) != 0) {
        if ((descriptor->kind & 1) != 0) {
            result = (u32)SndBank_AcquireWaveArc((s32)descriptor->index, record, flag);
        } else {
            result = (u32)SndBank_AcquireWave((s32)descriptor->index, record, flag);
        }
        if (result == 0) {
            return 9;
        }
    } else {
        result = SndTable_GetWord14((s32)descriptor->index);
    }
    if (out != 0) {
        *out = result;
    }
    return 0;
}
