#ifndef SDK_SND_SND_BANK_H
#define SDK_SND_SND_BANK_H

// TwlSDK SND banks and wave archives (snd_bank.c).
#include "types.h"

struct SndWaveArc;

// Link that ties one wave archive slot of a bank into the archive's list of users.
typedef struct SndWaveArcLink {
    struct SndWaveArc *waveArc;  // 0x00
    struct SndWaveArcLink *next; // 0x04
} SndWaveArcLink;

// A wave archive: the list of bank slots that use it and the table of wave data addresses (offsets until resolved).
// include/ui/sndwavearc.h has a second view of the same object (count at +0x38, entries at +0x3c).
typedef struct SndWaveArc {
    u8 unk_00[0x18];
    SndWaveArcLink *topLink; // 0x18
    u8 unk_1c[0x1c];
    u32 waveCount;           // 0x38
    u32 waveAddress[1];      // 0x3c: waveCount entries
} SndWaveArc;

// A sound bank: four wave archive slots and the instrument table.
typedef struct SndBank {
    u8 unk_00[0x18];
    SndWaveArcLink waveArcLink[4]; // 0x18
    u32 instCount;                 // 0x38
    u32 instData[1];               // 0x3c: instCount entries (type in the low byte, offset above)
} SndBank;

// The five halfwords of a plain instrument record (also found inside drum-set and key-split records).
typedef struct SndInstParam {
    u16 value[5];
} SndInstParam;

// Returned by value; the SDK advances the instrument and its sub-entry separately.
typedef struct SndInstDataPosition {
    u32 instrumentIndex;
    u32 subIndex;
} SndInstDataPosition;

// One instrument record as SND_GetNextInstData returns it (0xc bytes).
typedef struct SndInstDataEntry {
    u8 type;          // 0x00
    u8 unk_01;        // 0x01
    u16 waveIndex;    // 0x02
    u16 archiveIndex; // 0x04
    u8 unk_06[6];     // 0x06: the rest of the instrument parameters (SndInstParam from +0x02)
} SndInstDataEntry;

extern "C" {
void SND_AssignWaveArc(SndBank *bank, s32 slot, SndWaveArc *waveArc);
void SND_DestroyBank(SndBank *bank);
void SND_DestroyWaveArc(SndWaveArc *waveArc);
SndInstDataPosition SND_GetFirstInstDataPos(void);
void SND_SetWaveDataAddress(SndWaveArc *waveArc, s32 waveNo, u32 address);
const void *SND_GetWaveDataAddress(SndWaveArc *waveArc, s32 waveNo);

// Not decompiled yet.
BOOL SND_GetNextInstData(void *bank, SndInstDataEntry *entry, SndInstDataPosition *position);
}

#endif
