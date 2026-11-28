#include "global.h"
#include "types.h"
#include "sdk/fs/fs_rom.h"

s32 FSi_ROMFAT_OpenDirectory(FSArchive *arc, FSFile *file, u32 baseId, const char *path) {
    u32 resolved = 0;
    s32 result;

    result = FSi_ROMFAT_FindPath(arc, baseId, path, &resolved, 1);
    if (result != 0) {
        return result;
    }
    return FSi_ROMFAT_SeekDirectory(arc, file, resolved, 0);
}
