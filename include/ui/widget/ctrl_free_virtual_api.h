#ifndef ENGINE_CTRL_FREE_VIRTUAL_API_H
#define ENGINE_CTRL_FREE_VIRTUAL_API_H

// Functions defined in src/engine/ctrl_free_virtual*.cpp.

#include "engine/entity.h"

extern "C" {
void Ctrl_freeVirtualBlockB(void *holder, void *block);
}

#endif
