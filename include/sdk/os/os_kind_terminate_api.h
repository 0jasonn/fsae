#ifndef ENGINE_OS_KIND_TERMINATE_API_H
#define ENGINE_OS_KIND_TERMINATE_API_H

// Functions defined in src/engine/os_kind_terminate*.cpp.

#include "engine/entity.h"

extern "C" {
void Os_TerminateByKind(u32 unused, u32 code);
}

#endif
