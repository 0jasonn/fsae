#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"

s32 FS_SetFileLength(FSFile *file, u32 length) {
    u32 arg;

    file->argument = &arg;
    arg = length;
    func_0200f69c(file, 0x1f, 1);
    return file->error;
}

s32 FS_OpenFileDirect(FSFile *file, FSArchive *arc, u32 bottom, u32 id, u32 top) {
    u32 args[4];

    file->arc = arc;
    file->argument = args;
    args[1] = bottom;
    args[0] = top;
    args[2] = id;
    args[3] = 0;
    return func_0200f69c(file, 7, 1);
}
