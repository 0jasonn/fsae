#ifndef ENGINE_FS_WRAP_API_H
#define ENGINE_FS_WRAP_API_H

// Functions defined in src/engine/fs_wrap*.cpp.

#include "engine/entity.h"

extern "C" {
u32 Fs_GetFileLengthWrap(u32 a, u32 b, u32 c, u32 d);
}

#endif
