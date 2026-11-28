#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_path.h"
#include "sdk/fs/fs_api.h"

s32 FS_CreateDirectoryAuto(const char *path, u32 mode) {
    char buffer[0x118];
    s32 result;

    result = 0;
    if (FSi_ComplementDirectory(path, buffer) != 0) {
        result = FS_CreateDirectory(path, mode);
        if (result == 0) {
            FS_DeleteDirectoryAuto(buffer);
        }
    }
    return result;
}
