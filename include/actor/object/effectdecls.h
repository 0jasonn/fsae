#ifndef WIP_A_DECLS_H
#define WIP_A_DECLS_H

#include "engine/entity.h"

// Prototypes used by the wip/A files that are not yet in engine/functions.h
void set_pos(Entity *e); // set_pos(OBJ_WORK_*), src/object/set46.cpp (0x0206d5e0)

// Per-type phase counters of the effect_rock, effect_omoideon, effect_particle and beam effects, effectPhaseTable
extern s32 effectPhaseTable[];

#endif
