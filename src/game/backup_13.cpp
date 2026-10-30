#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"
#include "game/savemedia.h"

// Save media unit 13 (module backup). Address -> name:
//   0x02056c7c Knife_readSaveFile (provisional, was Knife_readSaveFile)

// data_02171d10: save load state. +04 set once a file is in the save buffer, +08 its length.
typedef struct SaveLoadState {
    void *unk_00;
    u32 loaded;
    u32 fileLength;
} SaveLoadState;
#define SAVE_LOAD_STATE (*(SaveLoadState *)&data_02171d10)

ARM s32 Knife_readSaveFile(void *buffer, const char *path) {
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
