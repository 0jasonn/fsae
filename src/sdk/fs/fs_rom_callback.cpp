#include "global.h"
#include "types.h"
#include "engine/functions.h"
#include "sdk/fs/fs_rom.h"
#include "sdk/card/card.h"

// Archive callback for the card ROM: starts the read and reports completion through FSi_OnRomReadDone.

void FSi_OnRomReadDone(FSArchive *arc) {
    FS_NotifyArchiveAsyncEnd(arc, CARD_GetPulledOutFlag() ? 5 : 0);
}

s32 FSi_ReadRomCallback(FSArchive *arc, void *dst, u32 src, u32 length) {
    func_020a44ac(data_021297b8.dmaNo, src, dst, length, FSi_OnRomReadDone, arc, 1);
    return 0x100;
}
