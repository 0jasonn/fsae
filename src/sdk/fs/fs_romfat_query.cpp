#include "global.h"
#include "types.h"
#include "sdk/fs/fs_rom.h"

s32 FSi_ROMFAT_GetFileLength(FSArchive *arc, FSFile *file, u32 *length) {
    *length = file->prop->bottom - file->prop->top;
    return 0;
}

s32 FSi_ROMFAT_GetFilePosition(FSArchive *arc, FSFile *file, u32 *position) {
    *position = file->prop->pos - file->prop->top;
    return 0;
}
