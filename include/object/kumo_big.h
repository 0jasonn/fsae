#ifndef WIP_A_KUMO_BIG_H
#define WIP_A_KUMO_BIG_H

#include "engine/functions.h"
#include "global.h"
#include "object/set46.h"

extern const EntityFunc kumoBig0Table[]; // kumoBig0Table, indexed by action
extern const EntityFunc kumoBig1Table[]; // kumoBig1Table, indexed by action

void kumo_big0(Entity *e);
void kumo_big0_init(Entity *e);
void kumo_big0_move(Entity *e);
void kumo_big1(Entity *e);
void kumo_big1_move(Entity *e);

#endif
