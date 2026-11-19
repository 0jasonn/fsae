#ifndef ACTOR_OBJECT_SET30_2_H
#define ACTOR_OBJECT_SET30_2_H

#include "engine/entity.h"

// motiagecheck (0x020690a0) returns a byte in the original: the callers use it without masking.
// include/actor/object/set30.h declares it as int; that declaration has to change to u8 before both are included together.
u8 motiagecheck(Entity *e);

extern const u32 flagBits[];
#include "engine/em12_type_masks.h"
extern const u8 set30Hitbox[];
extern const u16 data_020da714[]; // vgroup ids per stage, three per type2
extern const u16 data_020da754[]; // vgroup ids per bgm record row, three per type2

// Actor fields of the Set30 family, file-local.
typedef struct Vars_Set30 {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u16 typeFlag; // set by set30_init from bit 7 of type2; enables set30_move
} Vars_Set30;

#endif
