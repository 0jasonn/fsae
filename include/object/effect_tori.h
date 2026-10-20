#ifndef WIP_A_EFFECT_TORI_H
#define WIP_A_EFFECT_TORI_H

#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"

extern const EntityFunc effectToriTable[]; // effectToriTable, indexed by action

void effect_tori(Entity *e);
void effect_tori_init(Entity *e);
void effect_tori_move(Entity *e);

#endif
