#ifndef ENGINE_SOUND_SND_INST_DATA_H
#define ENGINE_SOUND_SND_INST_DATA_H

#include "types.h"

// Returned by value; the SDK advances the instrument and its sub-entry separately.
typedef struct SndInstDataPosition {
    u32 instrumentIndex;
    u32 subIndex;
} SndInstDataPosition;

typedef struct SndInstDataEntry {
    u8 type;
    u8 unk_01;
    u16 waveIndex;
    u16 archiveIndex;
    u8 unk_06[6];
} SndInstDataEntry;

extern "C" {
SndInstDataPosition SND_GetFirstInstDataPos(void);
BOOL SND_GetNextInstData(void *bank, SndInstDataEntry *entry, SndInstDataPosition *position);
}

#endif
