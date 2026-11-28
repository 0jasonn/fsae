#include "global.h"
#include "types.h"
#include "sdk/fs/fs_rom.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/card/card.h"


// For a file in the ROM FAT archive, seeks without going through the command queue. Returns 1 when it did.
s32 FSi_SeekFileIfProc(FSFile *file, s32 offset, s32 origin) {
    s32 result;

    if (file->arc->vtbl == &data_020c90fc) {
        result = FSi_ROMFAT_SeekFile(file->arc, file, &offset, origin);
        file->error = result;
        file->arc->lastResult = result;
        if (result == 0) {
            return 1;
        }
    }
    return 0;
}
