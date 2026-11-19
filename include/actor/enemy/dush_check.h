#ifndef ACTOR_ENEMY_DUSH_CHECK_H
#define ACTOR_ENEMY_DUSH_CHECK_H

#include "engine/functions.h"
#include "actor/enemy/attset.h"

#include "engine/map_state.h"
extern const u8 cellDeltaTable[]; // per-direction cell step (s16), indexed by direction >> 3
int func_02083d4c(u16 cell, u16 layer); // thumb helper, C++ linkage (_Z13func_02083d4ctt)

// 1 when the cell at the end of the dash is open for it (original dushCheck(OBJ_WORK_*)), 0x0203ee28.
int dushCheck(Entity *e);

#endif
