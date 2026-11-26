#include "global.h"
#include "types.h"
#include "sdk/fs/fs_rom.h"

s32 FSi_ROMFAT_CloseDirectory(FSArchive *arc, FSFile *file) {
    file->prop = NULL;
    file->stat &= ~0x30;
    return 0;
}
