#include "engine/functions.h"
#include "global.h"
#include "engine/blend_request.h"
#include "game/keyclear_api.h"
#include "engine/misc.h"

// Zelda fade module. Address -> name:
//   0x0205b67c ZeldaFadeSet (original name)
//   0x0205b6f0 ZeldaFadeFlagGet (dsd name ZeldaFadeFlagGet)
//   0x0205b700 ZeldaFadeFinish is in scratch/agentF/nonmatching/ZeldaFadeFinish.c

// One 0x14-byte entry per fade index in zeldaFadeTable.
typedef struct ZeldaFadeEntry {
    /* 00 */ u16 paletteA;
    /* 02 */ u16 paletteB;
    /* 04 */ u8 unk_04[0x10];
} ZeldaFadeEntry;

extern const ZeldaFadeEntry zeldaFadeTable[]; // zeldaFadeTable, indexed by the fade index
extern u8 data_02171d1c;                      // 1 while no fade partner is active (see ZeldaFadeFlagGet)

void ZeldaFadeSet(Entity *e, u32 index) {
    Entity *child;
    const ZeldaFadeEntry *entry;

    entry = &zeldaFadeTable[index];
    child = GetSetWork(0x3a, index & 0xff, 0);
    if (child != NULL) {
        child->parent = e;
        data_02171d1c = 0;
    } else {
        data_02171d1c = 1;
    }
    blendRequest.fadeRunning = 0;
    FadeSet(entry->paletteA & 0xff, entry->paletteB & 0xff);
}

u8 ZeldaFadeFlagGet(void) {
    return data_02171d1c;
}

// Zelda fade module, 0x0205b700 ZeldaFadeFinish (original name; follows ZeldaFadeFlagGet in zeldafade.cpp)

extern u8 data_02171d1c; // 1 while no fade partner is active (see ZeldaFadeFlagGet)

void ZeldaFadeFinish(void) {
    StopEffectWindow();
    data_02171d1c = 1;
    blendRequest.fadeRunning = 1;
    blendRequest.blendEnabled = 0;
}
