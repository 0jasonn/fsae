#ifndef ENGINE_FATFS_WRAP_API_H
#define ENGINE_FATFS_WRAP_API_H

// Functions defined in src/engine/fatfs_wrap*.cpp.

#include "engine/entity.h"

extern "C" {
u32 Fatfs_SendToPxi(u32 a, u32 b, u32 c, u32 d);
}

#endif
