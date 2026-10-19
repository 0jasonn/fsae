#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Save media (backup) unit. Address -> name:
//   0x02056120 CalcChecksum (original name)
//   0x0205614c Knife_writeMediaFlagged -> Knife_writeMediaFlagged (provisional)
//   0x02056160 Knife_readMediaFlagged -> Knife_readMediaFlagged (provisional)
//   0x02056174 Knife_writeHeaderBlock -> Knife_writeHeaderBlock (provisional)
//   0x02056188 ReadCartInfo (original name)
//   0x020561a4 DeleteSaveFile (original name)

ARM u16 CalcChecksum(const u16 *data, s32 size) {
    u32 sum = 0;

    if (size != 0) {
        do {
            sum += *data++ ^ size;
            size -= 2;
        } while (size != 0);
    }
    return (u16)sum;
}

ARM s32 Knife_writeMediaFlagged(u8 slot, const u32 *data) {
    return Knife_WriteToMedia((u8)(slot | 4), data);
}

ARM s32 Knife_readMediaFlagged(u8 slot, u32 *data) {
    return ReadFromMedia((u8)(slot | 4), data);
}

ARM s32 Knife_writeHeaderBlock(const u32 *data) {
    return Knife_WriteToMedia(7, data);
}

ARM s8 ReadCartInfo(u32 *data) {
    return (s8)ReadFromMedia(7, data);
}

ARM void DeleteSaveFile(u8 slot) {
    const SaveEepInfo *info = getEepInfo((u8)(slot | 4));

    func_020569cc(data_020d851c, info->unk_02, 8);
    Knife_mediaWrite();
}

// getEepInfo: slot table entry, slots 0..7 (the table data_020d8550 has 0x0c bytes per slot).
