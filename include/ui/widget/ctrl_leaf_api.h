#ifndef ENGINE_CTRL_LEAF_API_H
#define ENGINE_CTRL_LEAF_API_H

// Functions defined in src/engine/ctrl_leaf*.cpp.

#include "engine/entity.h"

extern "C" {
void *Ctrl_lookupEntry(s32 id);
}

#endif
