#ifndef WIP_C_TAMA07_3_H
#define WIP_C_TAMA07_3_H

// Declarations for the tama07 unit src/wip/C/tama07_3.cpp.
#include "engine/functions.h"
#include "global.h"

extern "C" {
int func_02085c28(Entity *e);   // thumb: nonzero when the carried actor is gone
int func_0208b644(Entity *e);   // thumb label: nonzero while the actor should keep moving
void func_0208af0c(Entity *e);  // thumb label, no result used
}

void tama07_remove(Entity *e);  // _Z13tama07_removeP9OBJ_WORK_, src/object/tama07_2.cpp

// Per-type tables (records of 0x94 bytes, indexed by child->type * 0x94; the same arrays as hitdecls.h)
extern u8 data_0212ceba[];
extern u8 data_0212ceb8[];
extern u8 data_0212cee6[];
extern u8 data_0212ceca[];
extern u16 data_0212c58c[];   // indexed by child->type
extern u8 data_020dcec0[];    // +-1 steps for the child's base direction, indexed by Random() & 1

#endif
