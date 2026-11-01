#ifndef ENGINE_OS_THREAD_EXIT_API_H
#define ENGINE_OS_THREAD_EXIT_API_H

// Functions defined in src/engine/os_thread_exit*.cpp.

#include "engine/entity.h"

extern "C" {
void Os_ExitCurrentThread(void);
}

#endif
