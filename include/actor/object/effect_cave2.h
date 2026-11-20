#ifndef ACTOR_OBJECT_EFFECT_CAVE2_H
#define ACTOR_OBJECT_EFFECT_CAVE2_H

#include "engine/functions.h"
#include "global.h"
#include "actor/object/ss.h"

extern const EntityFunc effectCave2Table[]; // effectCave2Table, indexed by action

void effect_cave2(Entity *e);
void effect_cave2_move(Entity *e);

#endif
