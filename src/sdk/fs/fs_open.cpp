#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/fs/fs_open.h"

// Opens a path: the resolver (func_0200f9fc) returns the archive and fills a value and a scratch buffer. No archive
// returns 0 at once. Otherwise the file is initialised, its argument block is passed to func_0200f69c (command 0xd,
// blocking), and the result is 1 on success or 0 with the archive cleared.
s32 FsFile_OpenPath(FSFile *file, const char *path, u32 mode) {
    u32 resolved;
    u8 buffer[0x118];
    FsOpenArgs args;
    FSArchive *arc;
    s32 result;

    result = 0;
    resolved = 0;
    arc = func_0200f9fc(path, &resolved, buffer);
    if (arc != NULL) {
        FS_InitFile(file);
        file->argument = &args;
        file->arc = arc;
        args.resolved = resolved;
        args.buffer = buffer;
        args.mode = mode;
        if (func_0200f69c(file, 0xd, 1) != 0) {
            result = 1;
        } else {
            file->arc = NULL;
        }
    }
    return result;
}
