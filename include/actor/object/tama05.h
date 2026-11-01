#ifndef WIP_C_TAMA05_H
#define WIP_C_TAMA05_H

// Declarations for the tama05 actor family (src/wip/C/tama05.cpp).
#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"

extern "C" {
void func_0208b644(Entity *e); // label, thumb
void func_0208af0c(Entity *e); // label, thumb
}

extern const u8 data_020dccc4[]; // hitbox of tama05
extern const s8 data_020dccb8[]; // signed offset table indexed by animationState
extern const u16 data_02117ba8[]; // wall mask table indexed by direction >> 3
extern const s8 data_020dccbc[]; // (dx, dy) pairs indexed by 2 * animationState
extern const u16 data_020dcccc[]; // sound id indexed by type

void hasshaSet(Entity *e); // original name hasshaSet(OBJ_WORK_*)
void prtInfoDel(Entity *e); // original name prtInfoDel(OBJ_WORK_*)

#endif
