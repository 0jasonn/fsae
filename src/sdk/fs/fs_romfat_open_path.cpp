#include "global.h"
#include "types.h"
#include "sdk/fs/fs_rom.h"

s32 FSi_ROMFAT_OpenFile(FSArchive *arc, FSFile *file, u32 baseId, const char *path, u32 mode) {
    u32 resolved;
    s32 result;

    result = FSi_ROMFAT_FindPath(arc, baseId, path, &resolved, 0);
    if (result != 0) {
        return result;
    }
    return FSi_ROMFAT_OpenFileFast(arc, file, resolved, mode);
}
