#include "global.h"
#include "types.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_open.h"
#include "sdk/fs/fs_rom.h"
#include "sdk/mi/mi_memory.h"

s32 FS_OpenDirectory(FSFile *dir, const char *path, u32 mode) {
    u32 resolved;
    u8 buffer[0x118];
    FsOpenArgs args;
    FSArchive *arc;
    s32 result;

    result = 0;
    resolved = 0;
    arc = func_0200f9fc(path, &resolved, buffer);
    if (arc != NULL) {
        FS_InitFile(dir);
        dir->argument = &args;
        dir->arc = arc;
        args.resolved = resolved;
        args.buffer = buffer;
        args.mode = mode;
        if (func_0200f69c(dir, 0x20, 1) != 0) {
            result = 1;
        } else {
            dir->arc = NULL;
        }
    }
    return result;
}

