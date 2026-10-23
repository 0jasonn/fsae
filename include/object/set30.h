#ifndef WIP_A_SET30_H
#define WIP_A_SET30_H

#include "engine/functions.h"

// Not in engine/functions.h yet (original motiagecheck(OBJ_WORK_*), 0x020690a0).
int motiagecheck(Entity *e);
// Unnamed helpers used by motiagecheck: func_02084110 returns the player mask, CountBits (functions.h) counts its bits.

// Actor fields of the Set30 family, file-local.
typedef struct Vars_Set30 {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u16 typeFlag; // set by set30_init from bit 7 of type2; enables set30_move
} Vars_Set30;

extern const u32 flagBits[];
extern const s8 motiaAnimTable[];
extern u32 em12_typeMasks[];

#endif
