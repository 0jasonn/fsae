#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"

s32 FS_CloseDirectory(FSFile *dir) {
    s32 result = 0;

    if (func_0200f69c(dir, 0x21, 1)) {
        result = 1;
    }
    return result;
}
