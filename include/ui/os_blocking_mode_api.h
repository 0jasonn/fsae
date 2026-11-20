#ifndef UI_OS_BLOCKING_MODE_API_H
#define UI_OS_BLOCKING_MODE_API_H

// Functions defined in src/engine/os_blocking_mode*.cpp.

#include "engine/entity.h"

extern "C" {
s32 OS_GetPrintBlockingMode(void *self);
}

#endif
