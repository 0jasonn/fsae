#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Save buffer access and NAND helpers. Address -> name (original names):
//   0x02056b40 NAND_CreateDirectory
//   0x02056d00 ReadSaveBufferDword
//   0x02056ddc ProgramSaveBufferDwordEx
// The save buffer is the u16 table at KnifeApp + 0x4b0, four halfwords per dword index.

void ProgramSaveBufferDwordEx(u16 index, u16 *data) {
    u16 base = index * 4;
    u32 i;

    for (i = 0; i < 4; i++) {
        *(u16 *)((u8 *)KnifeApp_getInstance() + 0x4b0 + base * 2 + i * 2) = data[i];
    }
}

// Save media unit 4. Address -> name:
//   0x02056e1c Knife_checkFileSpace (provisional)
//   0x02056e70 FSResultToKnifeFsResult (original name)
//   0x02056ee0 Knife_getSaveBuffer (provisional)

s32 Knife_checkFileSpace(s32 fileSize, const char *path) {
    u8 resource[0x30];

    if (FS_GetArchiveResource(path, resource) == 0) {
        return 10;
    }
    if (FS_HasEnoughSpaceToCreateFile(resource, path, fileSize) != 0) {
        return 0;
    }
    return 7;
}

s32 FSResultToKnifeFsResult(s32 result) {
    switch (result) {
    case 0:
        return 0;
    case 14:
        return 3;
    case 10:
        return 4;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 11:
    case 12:
    case 13:
        return 1;
    }
    return 1;
}

void *Knife_getSaveBuffer(void) {
    return data_02171d10;
}
