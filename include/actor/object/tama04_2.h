#ifndef ACTOR_OBJECT_TAMA04_2_H
#define ACTOR_OBJECT_TAMA04_2_H

// Declarations for the tama04 actor family (src/wip/C/tama04_2.cpp).
#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"

extern "C" {
}

extern const u8 data_020dcc80[]; // hitbox of the tama04 family
extern const EntityFunc data_020dccfc[]; // action table of the Tama05 dispatcher, indexed by e->action

void tama04_hajikiInit(Entity *e);

#endif
