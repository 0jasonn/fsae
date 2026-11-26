#include "global.h"
#include "types.h"
#include "sdk/fs/fs_rom.h"

// The requested length at +0x34 is the caller's value; the clamped length goes to +0x38.

s32 FSi_ROMFAT_ReadFile(FSArchive *arc, FSFile *file, void *buffer, u32 *length) {
    u32 requested = *length;
    u32 remaining = file->prop->bottom - file->prop->pos;

    if (requested > remaining) {
        *length = remaining;
    }
    file->command.b.word = requested;
    file->command.a.buffer = buffer;
    file->command.c.word = *length;
    return FSi_TranslateCommand(file, 0, 0);
}

s32 FSi_ROMFAT_WriteFile(FSArchive *arc, FSFile *file, const void *source, u32 *length) {
    u32 requested = *length;
    u32 remaining = file->prop->bottom - file->prop->pos;

    if (requested > remaining) {
        *length = remaining;
    }
    file->command.b.word = requested;
    file->command.a.source = source;
    file->command.c.word = *length;
    return FSi_TranslateCommand(file, 1, 0);
}
