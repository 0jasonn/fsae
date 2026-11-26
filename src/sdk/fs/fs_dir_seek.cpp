#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"

s32 FSi_SeekDirDirect(FSFile *file, u16 entryId) {
    file->command.b.half.lo = entryId;
    file->command.a.arc = file->arc;
    file->command.b.half.hi = 0;
    file->command.c.word = 0;
    return FSi_TranslateCommand(file, 2, 1);
}
