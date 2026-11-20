#ifndef ACTOR_OBJECT_EFFECT_TUTO0_H
#define ACTOR_OBJECT_EFFECT_TUTO0_H

#include "engine/functions.h"
#include "global.h"
#include "actor/object/ss.h"

extern const EntityFunc effectTuto0Table[]; // effectTuto0Table, indexed by action

void effect_tuto0(Entity *e);
void effect_tuto0_init(Entity *e);
void effect_tuto0_move(Entity *e);

#endif
