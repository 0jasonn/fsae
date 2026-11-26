#include "global.h"
#include "types.h"
#include "engine/functions.h"
#include "sdk/fs/fs_archive.h"

// Archive callbacks for archives that live in memory.

s32 FSi_ReadMemCallback(FSArchive *arc, void *dst, u32 offset, u32 length) {
    MI_CpuCopy8((void *)FS_GetArchiveOffset(arc, offset), dst, length);
    return 0;
}

s32 FSi_WriteMemCallback(FSArchive *arc, const void *src, u32 offset, u32 length) {
    MI_CpuCopy8(src, (void *)FS_GetArchiveOffset(arc, offset), length);
    return 0;
}
