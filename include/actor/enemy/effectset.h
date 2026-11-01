#ifndef WIP_B_EFFECTSET_H
#define WIP_B_EFFECTSET_H

#include "engine/functions.h"

// Per-type byte table in ROM (data_020d2980), indexed by e->type, passed to GetSetWork.
extern const u8 data_020d2980[];

// Spawns the effect actor of this entity's type at its position.
void effectset(Entity *e);

#endif
