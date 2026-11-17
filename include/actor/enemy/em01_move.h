#ifndef ACTOR_ENEMY_EM01_MOVE_H
#define ACTOR_ENEMY_EM01_MOVE_H

#include "engine/functions.h"

extern const u8 em01_turnAmountTable[]; // direction deltas 0, -1, 0, +1 (as bytes), indexed by Random() & 3

// Sets a new direction sequence for em01 (original dirSeqSet(OBJ_WORK_*)), 0x0202eb54.
void dirSeqSet(Entity *e);

// em01 walking action (original em01_move(OBJ_WORK_*)), 0x0202ea2c.
void em01_move(Entity *e);

#endif
