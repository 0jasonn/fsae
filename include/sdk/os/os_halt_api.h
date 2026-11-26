#ifndef SDK_OS_OS_HALT_API_H
#define SDK_OS_OS_HALT_API_H

// Functions defined in src/sdk/os/os_halt.cpp and OS_Halt (the CP15 wait-for-interrupt that follows it in the ROM).

#include "engine/entity.h"

extern "C" {
void Os_DisableIrqAndHalt(void);
void OS_Halt(void);
}

#endif
