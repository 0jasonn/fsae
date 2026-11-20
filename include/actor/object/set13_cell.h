#ifndef ACTOR_OBJECT_SET13_CELL_H
#define ACTOR_OBJECT_SET13_CELL_H

#include "engine/functions.h"

extern const s16 cellDeltaTable[];       // cell index step, indexed by animationState / 2
extern const u16 set13_cellValueTable[]; // expected cell value, indexed by animationState / 2

extern "C" void hidari_rewritecell(Entity *e); // original rewritecell(OBJ_WORK_*), also in actor/object/g_callees.h
// cellcheck is declared in engine/functions.h

#endif
