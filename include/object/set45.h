#ifndef WIP_A_SET45_H
#define WIP_A_SET45_H

#include "engine/functions.h"
#include "global.h"
#include "object/cellcalls.h"
#include "object/nemoto_3.h"

extern const EntityFunc set45Table[];        // set45Table, indexed by action
extern const u16 set45JigoshoriIds[];        // set45JigoshoriIds, indexed by type (after clamping to 4)

void Set45(Entity *e);
void set45_init(Entity *e);
void set45_move(Entity *e);
void set45_jigoshori(Entity *e);
void set45_die(Entity *e);

#endif
