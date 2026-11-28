#include "global.h"
#include "types.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_state.h"
#include "sdk/fs/fs_path.h"
#include "sdk/fs/fs_open.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/std/std_string.h"

FSArchive *FS_FindArchive(const char *name, s32 length) {
    u32 irqState;
    FSArchive *arc;
    const char *archiveName;
    s32 mounted;

    irqState = OS_DisableInterrupts();
    for (arc = data_02128924.archiveList; arc != NULL; arc = arc->next) {
        mounted = (arc->flag & FS_ARCHIVE_FLAG_MOUNTED) != 0 ? 1 : 0;
        if (mounted != 0) {
            archiveName = FS_GetArchiveName(arc);
            if (STD_CompareNString(archiveName, name, length) == 0 && archiveName[length] == 0) {
                break;
            }
        }
    }
    OS_RestoreInterrupts(irqState);
    return arc;
}

s32 FS_GetArchiveResultCode(const char *path) {
    u32 irqState;
    FSArchive *arc;

    irqState = OS_DisableInterrupts();
    arc = data_02128924.archiveList;
    while (arc != NULL && arc != (FSArchive *)path) {
        arc = arc->next;
    }
    if (arc == NULL) {
        arc = func_0200f9fc(path, NULL, NULL);
    }
    OS_RestoreInterrupts(irqState);
    if (arc != NULL) {
        return arc->lastResult;
    }
    return 5;
}

s32 FS_SetCurrentDirectory(const char *path) {
    u32 resolved;
    FsChangeDirectoryArgs args;
    u8 buffer[FS_PATH_LENGTH];
    FSFile file;
    FSArchive *arc;
    s32 result;

    result = 0;
    resolved = 0;
    arc = func_0200f9fc(path, &resolved, buffer);
    if (arc != NULL) {
        data_02128924.currentArchive = arc;
        data_02128924.currentDirectory = 0;
        data_02128924.unk_0a = 0;
        data_02128924.unk_0c = 0;
        STD_CopyLString(data_02128a34, (const char *)buffer, FS_PATH_LENGTH);
        if (arc->vtbl->command[4] != NULL) {
            FS_InitFile(&file);
            file.arc = arc;
            file.argument = &args;
            args.resolved = resolved;
            args.buffer = buffer;
            args.flag = 1;
            if (func_0200f69c(&file, 4, 1) != 0) {
                data_02128924.currentDirectory = args.directory;
                STD_CopyLString(data_02128a34, (const char *)buffer, FS_PATH_LENGTH);
            }
        }
        result = 1;
    }
    return result;
}

#pragma optimization_level 2
s32 FSi_CopySafeString(char *dst, s32 size, const char *src, s32 length, s32 *overflow) {
    s8 character;
    s32 index;
    s32 limit;

    limit = size - 1;
    if (limit >= length) {
        limit = length;
    }
    for (index = 0; index < limit && (character = src[index]) != 0; index++) {
        dst[index] = character;
    }
    if (index < length && src[index] != 0) {
        *overflow = 1;
    }
    dst[index] = 0;
    return index;
}
