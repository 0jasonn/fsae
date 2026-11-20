#ifndef SDK_OS_OS_HALT_API_H
#define SDK_OS_OS_HALT_API_H

// Functions defined in src/engine/os_halt*.cpp.

#include "engine/entity.h"

extern "C" {
void Os_DisableIrqAndHalt(void);
}

#endif
