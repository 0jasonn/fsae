#ifndef ENGINE_LEVEL_TABLE_API_H
#define ENGINE_LEVEL_TABLE_API_H

// Functions defined in src/engine/level_table*.cpp.

#include "engine/entity.h"

extern "C" {
void *Level_deletingDtor(void *self);
void *Level_getEntry(void *self, u32 level);
void Level_noop(void *self);
}

#endif
