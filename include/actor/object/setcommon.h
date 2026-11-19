#ifndef UNKNOWN_WIP_F_COMMON_H
#define UNKNOWN_WIP_F_COMMON_H

#include "engine/entity.h"
#include "engine/player.h"

// Declarations shared by the set object files in src/object.

#include "engine/map_state.h"

// Actor-template table: one 0x94-byte entry per type; the first word of an entry points to a template Entity.
extern u8 data_0212ced8[];
#define TEMPLATE_OF(type) (*(Entity **)(data_0212ced8 + (type) * 0x94))

extern u32 em12_typeMasks[];
extern const u8 data_020d8858[]; // hitbox used when type2 & 2
extern const u8 data_020d8850[]; // hitbox used otherwise

extern "C" void RewCellBack(u16 cell, u16 layer);
void AshimotoCheck(Entity *e);

#endif
