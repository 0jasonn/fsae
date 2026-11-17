#ifndef WIP_E_EM1D_H
#define WIP_E_EM1D_H

#include "engine/entity.h"

// Actor em1d. Declarations of functions from other units that are not in engine/functions.h yet.
void seqset(Entity *e, int baseAnim);     // seqset (src/enemy/seqset.cpp), signature from symbols.txt
Entity *gieniGetAimPl(void);              // gieniGetAimPl, original name
void func_02084794(Entity *e);            // no original name yet

extern const u8 em1d_hitbox[];            // em1d_hitbox

#endif
