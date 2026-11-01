#ifndef ENGINE_PM_CALLBACK_API_H
#define ENGINE_PM_CALLBACK_API_H

// Functions defined in src/engine/pm_callback*.cpp.

#include "engine/entity.h"

extern "C" {
void PMi_RunCallback(u32 result);
}

#endif
