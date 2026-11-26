#ifndef SDK_FS_FS_OPEN_H
#define SDK_FS_FS_OPEN_H

// Declarations for src/sdk/fs/fs_open.cpp. Parameter types follow the call sites in the ROM.
#include "types.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_archive.h"

// Argument block passed to the open command through FSFile.argument.
typedef struct FsOpenArgs {
    u32 resolved;           // 0x00: value written by the path resolver
    u8 *buffer;             // 0x04: scratch buffer that was handed to the resolver
    u32 mode;               // 0x08: third argument of FsFile_OpenPath
} FsOpenArgs;

extern "C" {
s32 FsFile_OpenPath(FSFile *file, const char *path, u32 mode);

// Not decompiled yet.
FSArchive *func_0200f9fc(const char *path, u32 *resolved, u8 *buffer); // path resolver, returns the archive
}

#endif
