#include "global.h"
#include "types.h"
#include "sdk/fs/fs_rom.h"

s32 FSi_ROMFAT_CloseFile(FSArchive *arc, FSFile *file) {
    s32 result = FSi_TranslateCommand(file, 8, 1);

    file->prop = NULL;
    file->stat &= ~0x30;
    return result;
}

s32 FSi_ROMFAT_Activate(FSArchive *arc) {
    FSFile file;

    FS_InitFile(&file);
    file.arc = arc;
    return FSi_TranslateCommand(&file, 9, 0);
}

s32 FSi_ROMFAT_Idle(FSArchive *arc) {
    FSFile file;

    FS_InitFile(&file);
    file.arc = arc;
    return FSi_TranslateCommand(&file, 10, 0);
}

s32 FSi_ROMFAT_Suspend(FSArchive *arc) {
    FSFile file;

    FS_InitFile(&file);
    file.arc = arc;
    return FSi_TranslateCommand(&file, 11, 0);
}

s32 FSi_ROMFAT_Resume(FSArchive *arc) {
    FSFile file;

    FS_InitFile(&file);
    file.arc = arc;
    return FSi_TranslateCommand(&file, 12, 0);
}
