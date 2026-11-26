#include "global.h"
#include "types.h"
#include "sdk/fs/fs_archive.h"

u32 FS_GetArchiveBase(FSArchive *arc) {
    return arc->context->base;
}

u32 FS_GetArchiveOffset(FSArchive *arc, u32 offset) {
    return arc->context->base + offset;
}

s32 FS_IsArchiveTableLoaded(FSArchive *arc) {
    return (arc->flag & 4) != 0;
}
