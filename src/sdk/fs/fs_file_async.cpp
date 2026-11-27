#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/fs/fs_open.h"

s32 FS_ReadFileAsync(FSFile *file, void *buffer, s32 length) {
    u32 fileLength;
    u32 position;
    FSFileCommand *command;

    if (FsRomFile_PositionIsZero(file, &position) != 0 && FsRomFile_LengthIsZero(file, &fileLength) != 0) {
        if (position + length > fileLength) {
            length = fileLength - position;
        }
    }
    command = &file->command;
    file->argument = command;
    command->a.buffer = buffer;
    command->b.word = length;
    func_0200f69c(file, 0, 0);
    return length;
}

s32 FS_WriteFileAsync(FSFile *file, const void *buffer, u32 size) {
    u32 fileLength;
    u32 position;
    FSFileCommand *command;

    if (FsRomFile_PositionIsZero(file, &position) != 0 && FsRomFile_LengthIsZero(file, &fileLength) != 0) {
        if (position + size > fileLength) {
            size = fileLength - position;
        }
    }
    command = &file->command;
    file->argument = command;
    command->a.source = buffer;
    command->b.word = size;
    func_0200f69c(file, 1, 0);
    return size;
}
