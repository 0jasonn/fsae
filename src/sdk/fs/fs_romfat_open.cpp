#include "global.h"
#include "types.h"
#include "sdk/fs/fs_rom.h"

s32 FSi_ROMFAT_GetPath(FSArchive *arc, FSFile *file, void *id, void *buffer, u32 *length) {
    s32 result;

    file->command.c.half.lo = 0;
    file->command.c.half.hi = 0;
    file->command.a.buffer = buffer;
    file->command.b.word = *length;
    result = FSi_TranslateCommand(file, 5, 1);
    if (result == 0) {
        *length = file->command.b.word;
    }
    return result;
}

s32 FSi_ROMFAT_OpenFileFast(FSArchive *arc, FSFile *file, u32 id) {
    s32 result;

    file->command.b.word = id;
    file->command.a.arc = arc;
    result = FSi_TranslateCommand(file, 6, 1);
    if (result == 0) {
        file->stat = (file->stat | 0x10) & ~0x20;
        file->prop = &file->property;
        file->arc = arc;
    }
    return result;
}
