#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/fs/fs_open.h"

u32 FS_GetFileLength(FSFile *file) {
    u32 result;
    u32 length;

    result = 0;
    if (FsRomFile_LengthIsZero(file, &result) == 0) {
        file->argument = &length;
        length = 0;
        if (func_0200f69c(file, 0xf, 1) != 0) {
            result = length;
        }
    }
    return result;
}

s32 FS_SeekFile(FSFile *file, s32 offset, s32 origin) {
    s32 args[2];
    s32 done;

    done = FSi_SeekFileIfProc(file);
    if (done != 0) {
        return done;
    }
    file->argument = args;
    args[0] = offset;
    args[1] = origin;
    return func_0200f69c(file, 0xe, 1);
}
