#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"

s32 FSi_SeekAndReadSRL(FSFile *file, void *buffer, s32 offset, s32 length) {
    if (file != NULL) {
        FS_SeekFile(file, offset, 0);
        FS_ReadFile(file, buffer, length);
    }
    return length;
}
