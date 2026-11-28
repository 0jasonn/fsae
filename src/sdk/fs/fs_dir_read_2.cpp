#include "global.h"
#include "types.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_open.h"
#include "sdk/fs/fs_rom.h"
#include "sdk/mi/mi_memory.h"

s32 FS_ReadDirectory(FSFile *dir, FsDirectoryEntryInfo *entry) {
    FsDirectoryEntryInfo *argument;
    s32 result;

    result = 0;
    dir->argument = &argument;
    argument = entry;
    MI_CpuFill8(entry, 0, 4);
    entry->id = -1;
    if (func_0200f69c(dir, 3, 1) != 0) {
        result = 1;
    }
    return result;
}
