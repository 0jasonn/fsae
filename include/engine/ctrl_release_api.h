#ifndef ENGINE_CTRL_RELEASE_API_H
#define ENGINE_CTRL_RELEASE_API_H

// Functions defined in src/engine/ctrl_release*.cpp.

#include "engine/entity.h"

extern "C" {
void Ctrl_releaseSubobjects(void *selfv, s32 arg);
}

#endif
