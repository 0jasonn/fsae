#include "global.h"
#include "types.h"
#include "sdk/mi/mi_memory.h"
#include "sdk/card/card.h"
#include "sdk/fs/fs_rom.h"

s32 FSi_ROMFAT_GetPathInfo(FSArchive *arc, u32 baseId, const char *path, FsPathInfo *info) {
    u32 resolved = 0;
    u32 entryWords[2];
    FsTableReader reader;
    s32 result = 5;
    u32 zero = 0;
    u32 id;
    FSArchiveContext *ctx;

    MI_CpuFill8(info, 0, sizeof(FsPathInfo));
    if (FSi_ROMFAT_FindPath(arc, baseId, path, &resolved, 1) == 0) {
        info->attributes = 0x100;
        info->id = resolved;
        result = 0;
    } else if (FSi_ROMFAT_FindPath(arc, baseId, path, &resolved, 0) == 0) {
        info->attributes = zero;
        info->id = resolved;
        info->fileSize = zero;
        ctx = arc->context;
        id = resolved;
        if (id * 8 < ctx->unk_04[1]) {
            reader.arc = arc;
            reader.offset = id * 8 + ctx->unk_04[0];
            if (FSi_ReadTable(&reader, entryWords, 8) == 0) {
                info->fileSize = entryWords[1] - entryWords[0];
                if (FSi_IsUnreadableRomOffset(arc, entryWords[0])) {
                    info->attributes |= 0x400;
                }
            }
        }
        result = 0;
    }
    info->attributes |= 0x200;
    return result;
}
