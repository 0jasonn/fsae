#ifndef ACTOR_OBJECT_EFFECT_TORI_H
#define ACTOR_OBJECT_EFFECT_TORI_H

#include "engine/functions.h"
#include "global.h"
#include "actor/object/ss.h"

extern const EntityFunc effectToriTable[]; // effectToriTable, indexed by action

void effect_tori(Entity *e);
void effect_tori_init(Entity *e);
void effect_tori_move(Entity *e);

#endif
