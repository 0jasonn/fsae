#ifndef ENGINE_CTRL_FIND_API_H
#define ENGINE_CTRL_FIND_API_H

// Functions defined in src/engine/ctrl_find*.cpp.

#include "engine/entity.h"

extern "C" {
void *Ctrl_findEntryD(void *self, s32 id);
void *Ctrl_findEntryE(void *self, s32 id);
}

#endif
