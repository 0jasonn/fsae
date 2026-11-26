#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"

s32 FSi_OpenFileDirectDefault(FSFile *file) {
    file->property.pos = file->property.top = file->command.a.value;
    file->property.bottom = file->command.b.word;
    file->property.id = file->command.c.word;
    return 0;
}
