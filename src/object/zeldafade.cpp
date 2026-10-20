#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_f.h"

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

// Fade work at data_0212c5ac, only the fields read here.
typedef struct FadeWorkZelda {
    /* 00 */ u8 blendEnabled;
    /* 01 */ u8 unk_01[3];
    /* 04 */ u8 fadeRunning;
} FadeWorkZelda;

extern const ZeldaFadeEntry zeldaFadeTable[]; // zeldaFadeTable, indexed by the fade index
extern u8 data_02171d1c;                      // 1 while no fade partner is active (see ZeldaFadeFlagGet)
extern FadeWorkZelda data_0212c5ac;

ARM void ZeldaFadeSet(Entity *e, u32 index) {
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
    data_0212c5ac.fadeRunning = 0;
    FadeSet(entry->paletteA & 0xff, entry->paletteB & 0xff);
}

ARM u8 ZeldaFadeFlagGet(void) {
    return data_02171d1c;
}
