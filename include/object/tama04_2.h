#ifndef WIP_C_TAMA04_2_H
#define WIP_C_TAMA04_2_H

// Declarations for the tama04 actor family (src/wip/C/tama04_2.cpp).
#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"

extern "C" {
int func_0208b668(Entity *e); // label, thumb, returns nonzero when the actor is blocked
void func_0208af0c(Entity *e); // label, thumb
}

extern const u8 data_020dcc80[]; // hitbox of the tama04 family
extern const EntityFunc data_020dccfc[]; // action table of the Tama05 dispatcher, indexed by e->action

ARM void tama04_hajikiInit(Entity *e);

#endif
