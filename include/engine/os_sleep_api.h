#ifndef ENGINE_OS_SLEEP_API_H
#define ENGINE_OS_SLEEP_API_H

// Functions defined in src/engine/os_sleep*.cpp.

#include "engine/entity.h"

extern "C" {
void Os_SleepAlarm(u32 count);
}

#endif
