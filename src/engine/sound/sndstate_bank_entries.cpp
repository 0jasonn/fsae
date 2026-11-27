#include "engine/menusound.h"
#include "engine/sound/sndbank_acquire_api.h"
#include "engine/sound/sndstate_lookup_api.h"
#include "ui/sndwavearc.h"
#include "engine/sound/sndstate_wave_ref.h"
#include "engine/sound/sndbank_wave_api.h"

extern "C" void SND_AssignWaveArc(void *bank, s32 index, void *wave);

typedef struct SndStateBankEntry {
    u32 bankIndex;
    u16 waveIndices[4];
} SndStateBankEntry;

// Resolve a bank descriptor and process its four wave slots. Errors from nested lookups are returned unchanged.
s32 func_020c0e50(s32 index, u32 flags, void *record, s32 flag, MenuSoundData **out) {
    SndStateBankEntry *stateEntry;
    MenuSoundData *bank;
    void *wave;
    u32 result;
    s32 slot;
    SndStateAcquireDescriptor *descriptor;

    stateEntry = (SndStateBankEntry *)SndState_LookupAt10(index);
    if (stateEntry == 0) {
        return 4;
    }
    if ((flags & 2) != 0) {
        bank = (MenuSoundData *)SndBank_AcquireBank(stateEntry->bankIndex, record, flag);
        if (bank == 0) {
            return 8;
        }
    } else {
        bank = (MenuSoundData *)SndTable_GetWord14((s32)stateEntry->bankIndex);
    }
    slot = 0;
    do {
        if (stateEntry->waveIndices[slot] != 0xffff) {
            descriptor = (SndStateAcquireDescriptor *)SndState_LookupAt14(stateEntry->waveIndices[slot]);
            if (descriptor == 0) {
                return 5;
            }
            result = func_020c0f90(stateEntry->waveIndices[slot], flags, record, flag, &wave);
            if (result != 0) {
                return result;
            }
            if ((descriptor->kind & 1) != 0 && (flags & 4) != 0) {
                if (!func_020c15a0(wave, bank, slot, descriptor->index, record)) {
                    return 9;
                }
            }
            if (bank != 0 && wave != 0) {
                SND_AssignWaveArc(bank, slot, wave);
            }
        }
        slot++;
    } while (slot < 4);
    if (out != 0) {
        *out = bank;
    }
    return 0;
}
