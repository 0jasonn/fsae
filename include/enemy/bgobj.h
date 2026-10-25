#ifndef WIP_B_BGOBJ_H
#define WIP_B_BGOBJ_H

#include "engine/functions.h"
#include "enemy/effectset.h"

// bgobj_lift dispatch table in ROM (bgobj_liftTable, index = e->subAction).
extern const EntityFunc bgobj_liftTable[];
// ROM offsets used by bgobj_poscopy (bgobj_poscopyTable, signed bytes).
extern const s8 bgobj_poscopyTable[];

// Timer values picked by bgobj_moveset (bgobj_moveTimerTable, indexed by Random() & 3).
extern const u8 bgobj_moveTimerTable[];

#endif
