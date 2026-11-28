#include "global.h"
#include "types.h"
#include "sdk/fs/fs_rom.h"

s32 FSi_ROMFAT_OpenFileDirect(FSArchive *arc, FSFile *file, u32 top, u32 bottom, const u32 *id) {
    s32 result;

    file->command.a.value = top;
    file->command.b.word = bottom;
    file->command.c.word = *id;
    result = FSi_TranslateCommand(file, 7, 1);
    if (result == 0) {
        file->stat = (file->stat | 0x10) & ~0x20;
        file->prop = &file->property;
        file->arc = arc;
    }
    return result;
}
