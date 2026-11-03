#include "engine/functions.h"
#include "game/rankingsave.h"
#include "game/savemedia.h"
#include "engine/backup_media.h"
#include "global.h"

// Save media (backup) layer. 0x0205687c Knife_WriteToMedia

extern u8 multiSioSelect[]; // multiSioSelect: save buffer of slot 7

// Writes the save header (checksum and its complement) and the save data of a slot to the media.
// The slot 7 area is written first, then the data of the requested slot unless it is 7.
s32 Knife_WriteToMedia(u8 slot, const u32 *data) {
    u32 magic;
    u16 header[2];
    u16 checksum;
    const SaveEepInfo *info;
    s32 result;

    info = getEepInfo(7);
    magic = 0x54463453;
    checksum = CalcChecksum((const u16 *)&magic, 4) + CalcChecksum((const u16 *)multiSioSelect, *(const u16 *)info);
    header[0] = checksum;
    header[1] = 0x10000 - checksum;
    func_020569cc(multiSioSelect, *(const u16 *)((u8 *)info + 6), *(const u16 *)info);
    func_020569cc(header, *(const u16 *)((u8 *)info + 2), 8);

    if (slot != 7) {
        info = getEepInfo(slot);
        magic = 0x54463453;
        checksum = CalcChecksum((const u16 *)&magic, 4) + CalcChecksum((const u16 *)data, *(const u16 *)info);
        header[0] = checksum;
        header[1] = 0x10000 - checksum;
        func_020569cc((const void *)data, *(const u16 *)((u8 *)info + 6), *(const u16 *)info);
        func_020569cc(header, *(const u16 *)((u8 *)info + 2), 8);
    }
    result = FSResultToKnifeFsResult(Knife_mediaWrite());
    SAVE_LOAD_RESULT = result;
    return result;
}

// Save media unit 5. Address -> name:
//   0x02056998 Knife_InitialSaveFile (original name)

void Knife_InitialSaveFile(u8 slot) {
    const u8 *name = data_020d8524;
    const SaveEepInfo *info;

    if ((slot & 0xc0) != 0) {
        return;
    }
    info = getEepInfo((u8)(slot | 4));
    func_020569cc(name, info->unk_02, 8);
}
