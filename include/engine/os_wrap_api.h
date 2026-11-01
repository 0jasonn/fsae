#ifndef ENGINE_OS_WRAP_API_H
#define ENGINE_OS_WRAP_API_H

// Functions defined in src/engine/os_wrap*.cpp.

#include "engine/entity.h"

extern "C" {
u32 Os_DoLockByWordWrap(u32 a, u32 b, u32 c, u32 unused);
u32 Os_InitCommonWrap(u32 a, u32 b, u32 c, u32 d);
u32 Os_IrqCallbackWrap(u32 unused, u32 b, u32 c, u32 d);
}

#endif
