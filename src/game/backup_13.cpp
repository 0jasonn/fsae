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
