#ifndef ACTOR_ENEMY_EM30_H
#define ACTOR_ENEMY_EM30_H

#include "engine/functions.h"
#include "engine/entity.h"

// Helpers of the em29/em30 follower chain that are not in engine/functions.h yet (original names, C++ linkage).
BOOL movecheck(Entity *e);
BOOL hikiyoseSet(Entity *segment, Entity *leader, u16 speed);

#endif
