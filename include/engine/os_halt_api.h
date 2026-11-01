#ifndef ENGINE_OS_HALT_API_H
#define ENGINE_OS_HALT_API_H

// Functions defined in src/engine/os_halt*.cpp.

#include "engine/entity.h"

extern "C" {
void Os_DisableIrqAndHalt(void);
}

#endif
