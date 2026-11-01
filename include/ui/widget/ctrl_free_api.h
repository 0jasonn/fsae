#ifndef ENGINE_CTRL_FREE_API_H
#define ENGINE_CTRL_FREE_API_H

// Functions defined in src/engine/ctrl_free*.cpp.

#include "engine/entity.h"

extern "C" {
void Ctrl_freeBlock(void *holder, void *block);
void Ctrl_freeSpanBlock(void *holder, void *block);
}

#endif
