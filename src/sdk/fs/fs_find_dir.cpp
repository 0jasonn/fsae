#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_open.h"

// Tail call into FsFile_OpenPath with mode 1.
s32 FS_FindDir(FSFile *file, const char *path) {
    return FsFile_OpenPath(file, path, 1);
}
