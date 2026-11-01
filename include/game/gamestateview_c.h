#ifndef UNKNOWN_C_GAMESTATEVIEW_C_H
#define UNKNOWN_C_GAMESTATEVIEW_C_H

#include "types.h"

#include "engine/player.h"

// 8-byte per-player flags entry (enemyTypeFlags, indexed by player). The entity type table is shared with
// CheckKenBeam/2 in state_02049020.c.
typedef struct PlayerFlags {
    /* 00 */ u32 flags;
    /* 04 */ u8 unk_04;
    /* 05 */ u8 unk_05;
    /* 06 */ u16 counter;
} PlayerFlags;
extern PlayerFlags enemyTypeFlags[];


#endif
