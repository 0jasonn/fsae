#ifndef ACTOR_OBJECT_TENKU_KUMO_H
#define ACTOR_OBJECT_TENKU_KUMO_H

#include "engine/functions.h"
#include "global.h"
#include "actor/object/set46.h"

extern const EntityFunc tenkuKumoTable[]; // tenkuKumoTable, indexed by action
#include "engine/effect_state.h"
int ZeldaFadeFlagGet(void);

void tenku_kumo(Entity *e);
void tenku_kumo_init(Entity *e);
void tenku_kumo_move(Entity *e);

#endif
