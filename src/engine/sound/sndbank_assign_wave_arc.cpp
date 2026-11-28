#include "engine/entity.h"
#include "sdk/snd/snd_bank.h"
#include "engine/sound/sndbank_wave_api.h"

// Scan the bank's instrument data and assign the matching wave archive data.
BOOL func_020c15a0(void *table, void *bank, u32 archiveIndex, s32 fileIndex, void *record) {
    SndInstDataPosition firstPosition;
    SndInstDataPosition position;
    SndInstDataEntry entry;
    SndInstDataEntry *entryPtr;
    SndInstDataPosition *positionPtr;

    firstPosition = SND_GetFirstInstDataPos();
    position = firstPosition;
    positionPtr = &position;
    if (bank == 0) {
        return 0;
    }
    entryPtr = &entry;
    if (SND_GetNextInstData(bank, entryPtr, positionPtr) != 0) {
        do {
            if (entry.type == 1 && archiveIndex == entry.archiveIndex) {
                if (!func_020c14d8(table, entry.waveIndex, fileIndex, record)) {
                    return 0;
                }
            }
        } while (SND_GetNextInstData(bank, entryPtr, positionPtr) != 0);
    }
    return 1;
}
