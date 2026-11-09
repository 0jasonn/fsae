#ifndef WIP_B_MOJI_H
#define WIP_B_MOJI_H

#include "engine/functions.h"

// (x, y) position tables indexed by e->type - 1 (original moji_posTables)
extern const u8 *const moji_posTables[];

void moji_init(Entity *e);

#endif
