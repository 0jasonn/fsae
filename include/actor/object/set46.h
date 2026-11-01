#ifndef WIP_A_SET46_H
#define WIP_A_SET46_H

#include "engine/functions.h"
#include "global.h"

extern const EntityFunc set46Table[];   // set46Table, indexed by type
extern const s16 set46PosTable[];       // set46PosTable, (x, y) pairs indexed by type

void Set46(Entity *e);
void set_pos(Entity *e);

#endif
