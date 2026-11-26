#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"

s32 FS_CloseFile(FSFile *file) {
    return func_0200f69c(file, 8, 1);
}

s32 FS_SetSeekCache(FSFile *file, void *buffer, u32 length) {
    u32 args[2];

    file->argument = args;
    args[0] = (u32)buffer;
    args[1] = length;
    return func_0200f69c(file, 0x22, 1);
}
