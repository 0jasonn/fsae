#ifndef SDK_FS_FS_PATH_H
#define SDK_FS_FS_PATH_H

// TwlSDK FS archive list and current directory.
#include "types.h"
#include "sdk/fs/fs_file.h"

struct FSArchive;

extern "C" {
struct FSArchive *FS_FindArchive(const char *name, s32 length);
s32 FS_GetArchiveResultCode(const char *path);
s32 FS_SetCurrentDirectory(const char *path);
s32 FSi_CopySafeString(char *dst, s32 size, const char *src, s32 length, s32 *overflow);
}

#endif
