#ifndef ACTOR_OBJECT_SETCOMMON_H
#define ACTOR_OBJECT_SETCOMMON_H

#include "engine/entity.h"
#include "engine/player.h"

// Declarations shared by the set object files in src/object.

#include "engine/map_state.h"

// Actor-template table: one 0x94-byte entry per type; the first word of an entry points to a template Entity.

#include "engine/em12_type_masks.h"
extern const u8 data_020d8858[]; // hitbox used when type2 & 2
extern const u8 data_020d8850[]; // hitbox used otherwise

void AshimotoCheck(Entity *e);

#endif
