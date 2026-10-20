#ifndef WIP_A_EFFECT_TUTO0_H
#define WIP_A_EFFECT_TUTO0_H

#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"

extern const EntityFunc effectTuto0Table[]; // effectTuto0Table, indexed by action

void effect_tuto0(Entity *e);
void effect_tuto0_init(Entity *e);
void effect_tuto0_move(Entity *e);

#endif
