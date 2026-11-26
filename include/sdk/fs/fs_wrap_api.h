#ifndef SDK_FS_FS_WRAP_API_H
#define SDK_FS_FS_WRAP_API_H

// Functions defined in src/engine/fs_wrap*.cpp.

#include "engine/entity.h"
#include "sdk/fs/fs_file.h"

extern "C" {
u32 Fs_GetFileLengthWrap(FSFile *file);
}

#endif
