#ifndef WIP_FS_PATH_OPS_H
#define WIP_FS_PATH_OPS_H

// Argument blocks of the FS path commands (FSFile.argument) and the ROM-file helpers the file operations call.
#include "types.h"
#include "sdk/fs/fs_file_fixed.h"
#include "sdk/fs/fs_archive.h"

// Create / get-path-info / create-directory commands: resolved path value, scratch buffer, extra word.
typedef struct FsPathArgsEx {
    u32 resolved;           // 0x00
    u8 *buffer;             // 0x04
    u32 extra;              // 0x08: mode or output pointer
} FsPathArgsEx;

// Delete commands.
typedef struct FsPathArgs {
    u32 resolved;           // 0x00
    u8 *buffer;             // 0x04
} FsPathArgs;

extern "C" {
s32 FsRomFile_LengthIsZero(FSFile *file, u32 *length);
s32 FsRomFile_PositionIsZero(FSFile *file, u32 *position);
s32 FSi_SeekFileIfProc(FSFile *file);
s32 FS_DeleteFile(const char *path);
s32 FS_GetPathInfo(const char *path, void *info);
s32 FS_CreateDirectory(const char *path, u32 mode);
s32 FS_DeleteDirectory(const char *path);
FSArchive *func_0200f9fc(const char *path, u32 *resolved, u8 *buffer);
}

#endif
