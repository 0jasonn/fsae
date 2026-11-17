#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"
#include "game/savemedia.h"
#include "game/backup.h"

// Save media unit 13 (module backup). Address -> name:
//   0x02056c7c Knife_readSaveFile (provisional, was Knife_readSaveFile)

#define SAVE_LOAD_STATE (*(SaveLoadState *)&data_02171d10)

s32 Knife_readSaveFile(void *buffer, const char *path) {
    FSFile file;
    s32 opened;
    u32 length;

    FS_InitFile(&file);
    opened = FsFile_OpenPath(&file, path, 1);
    if (opened == 0) {
        return FS_GetArchiveResultCode(path);
    }
    length = FS_GetFileLength(&file);
    SAVE_LOAD_STATE.fileLength = length;
    FS_ReadFile(&file, buffer, length);
    FS_CloseFile(&file);
    SAVE_LOAD_STATE.loaded = 1;
    return 0;
}

// Save buffer access and NAND helpers. Address -> name (original names):
//   0x02056b40 NAND_CreateDirectory
//   0x02056d00 ReadSaveBufferDword
//   0x02056d44 VerifySaveBufferDword
//   0x02056ddc ProgramSaveBufferDwordEx
// The save buffer is the u16 table at KnifeApp + 0x4b0, four halfwords per dword index.

s32 ReadSaveBufferDword(u16 index, u16 *data) {
    u16 base = index * 4;
    u32 i;

    for (i = 0; i < 4; i++) {
        data[i] = ((u16 *)((u8 *)KnifeApp_getInstance() + 0x4b0 + base * 2))[i];
    }
    return 0;
}

// Checks the four halfwords at index and returns 1 on the first mismatch.
s32 VerifySaveBufferDword(u16 index, u16 *data) {
    u32 wordIndex;
    const u8 *appBase;

    appBase = (const u8 *)KnifeApp_getInstance();
    wordIndex = (u32)index << 2;
    if (data[0] != *(const u16 *)(appBase + wordIndex * 2 + 0x400 + 0xb0)) {
        goto mismatch;
    }
    appBase = (const u8 *)KnifeApp_getInstance();
    if (data[1] != *(const u16 *)(appBase + (wordIndex + 1) * 2 + 0x400 + 0xb0)) {
        goto mismatch;
    }
    appBase = (const u8 *)KnifeApp_getInstance();
    if (data[2] != *(const u16 *)(appBase + (wordIndex + 2) * 2 + 0x400 + 0xb0)) {
        goto mismatch;
    }
    appBase = (const u8 *)KnifeApp_getInstance();
    if (data[3] == *(const u16 *)(appBase + (wordIndex + 3) * 2 + 0x400 + 0xb0)) {
        return 0;
    }
mismatch:
    return 1;
}

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
