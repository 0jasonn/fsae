#include "global.h"
#include "types.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/fs/fs_open.h"

s32 FS_CreateFile(const char *path, u32 mode) {
    u32 resolved;
    u8 buffer[0x118];
    FsPathArgsEx args;
    FSFile file;
    FSArchive *arc;
    s32 result;

    result = 0;
    resolved = 0;
    arc = func_0200f9fc(path, &resolved, buffer);
    if (arc != NULL) {
        FS_InitFile(&file);
        file.arc = arc;
        file.argument = &args;
        args.resolved = resolved;
        args.buffer = buffer;
        args.extra = mode;
        result = func_0200f69c(&file, 0x14, 1);
    }
    return result;
}

s32 FS_DeleteFile(const char *path) {
    u32 resolved;
    u8 buffer[0x118];
    FSFile file;
    FsPathArgs args;
    FSArchive *arc;
    s32 result;

    result = 0;
    resolved = 0;
    arc = func_0200f9fc(path, &resolved, buffer);
    if (arc != NULL) {
        FS_InitFile(&file);
        file.arc = arc;
        file.argument = &args;
        args.resolved = resolved;
        args.buffer = buffer;
        result = func_0200f69c(&file, 0x15, 1);
    }
    return result;
}

s32 FS_GetPathInfo(const char *path, void * extra) {
    u32 resolved;
    u8 buffer[0x118];
    FsPathArgsEx args;
    FSFile file;
    FSArchive *arc;
    s32 result;

    result = 0;
    resolved = 0;
    arc = func_0200f9fc(path, &resolved, buffer);
    if (arc != NULL) {
        FS_InitFile(&file);
        file.arc = arc;
        file.argument = &args;
        args.resolved = resolved;
        args.buffer = buffer;
        args.extra = (u32)extra;
        result = func_0200f69c(&file, 0x17, 1);
    }
    return result;
}

s32 FS_CreateDirectory(const char *path, u32 extra) {
    u32 resolved;
    u8 buffer[0x118];
    FsPathArgsEx args;
    FSFile file;
    FSArchive *arc;
    s32 result;

    result = 0;
    resolved = 0;
    arc = func_0200f9fc(path, &resolved, buffer);
    if (arc != NULL) {
        FS_InitFile(&file);
        file.arc = arc;
        file.argument = &args;
        args.resolved = resolved;
        args.buffer = buffer;
        args.extra = (u32)extra;
        result = func_0200f69c(&file, 0x19, 1);
    }
    return result;
}

s32 FS_DeleteDirectory(const char *path) {
    u32 resolved;
    u8 buffer[0x118];
    FSFile file;
    FsPathArgs args;
    FSArchive *arc;
    s32 result;

    result = 0;
    resolved = 0;
    arc = func_0200f9fc(path, &resolved, buffer);
    if (arc != NULL) {
        FS_InitFile(&file);
        file.arc = arc;
        file.argument = &args;
        args.resolved = resolved;
        args.buffer = buffer;
        result = func_0200f69c(&file, 0x1a, 1);
    }
    return result;
}
