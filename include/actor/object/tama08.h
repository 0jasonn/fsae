#ifndef WIP_C_TAMA08_H
#define WIP_C_TAMA08_H

// Declarations for the Tama08 actor family (src/wip/C/tama08.cpp).
#include "engine/functions.h"
#include "global.h"

extern "C" {
int func_02085294(void); // label, thumb: state index of the Tama08 dispatcher
}

extern const EntityFunc data_020dcf74[]; // Tama08 dispatcher table, indexed by func_02085294()
extern const EntityFunc data_020dcf60[]; // tama08_normal action table, indexed by e->action
extern const u8 data_020dcf50[]; // hitbox of tama08 (direction bit 3 set)
extern const u8 data_020dcf58[]; // hitbox of tama08 (direction bit 3 clear)

#endif
