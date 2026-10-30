#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/fs_open.h"

// Opens a path: the resolver (func_0200f9fc) fills a value and a scratch buffer. A zero handle returns 0 at once.
// Otherwise the record is initialised, its argument block is passed to func_0200f69c (mode 0xd, flag 1), and the
// result is 1 on success or 0 with the handle cleared.
extern "C" s32 FsFile_OpenPath(FsOpenRecord *rec, u32 path, u32 arg);

ARM s32 FsFile_OpenPath(FsOpenRecord *rec, u32 path, u32 arg) {
    u32 resolved;
    u8 buffer[0x118];
    FsOpenArgs args;
    s32 handle;
    s32 result;

    result = 0;
    resolved = 0;
    handle = func_0200f9fc(path, &resolved, buffer);
    if (handle != 0) {
        FS_InitFile(rec);
        rec->args = &args;
        rec->handle = handle;
        args.resolved = resolved;
        args.buffer = buffer;
        args.arg = arg;
        if (func_0200f69c(rec, 0xd, 1) != 0) {
            result = 1;
        } else {
            rec->handle = 0;
        }
    }
    return result;
}
