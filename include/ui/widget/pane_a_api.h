#ifndef ENGINE_PANE_A_API_H
#define ENGINE_PANE_A_API_H

// Functions defined in src/engine/pane_a*.cpp.

#include "engine/entity.h"

extern "C" {
void **Pane_allocPtrArray(void *owner, s32 count);
void Pane_freeBlock(void *heap, void *block);
}

#endif
