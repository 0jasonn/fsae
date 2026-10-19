#ifndef UNKNOWN_WIP_F_MATSURI_H
#define UNKNOWN_WIP_F_MATSURI_H

#include "engine/objwork.h"
#include "object/setcommon.h"

// Matsuri (festival) actor. Table names are provisional, see scratch/agentF/renames.txt.
extern const EntityFunc matsuri_actions[]; // matsuri_actions, indexed by e->action

// Entity overlay: u32 at 0x60 holds the flags this actor waits for (set in matsuri_init from ParseTypeBits).
typedef struct Vars_Matsuri {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits;
    /* 64 */ u8 unk_64[4];
    /* 68 */ u16 baseX;      // spawn origin, added to the random offset of each child
    /* 6a */ u16 baseY;
    /* 6c */ u16 rangeX;     // modulus of the random x offset
    /* 6e */ u16 rangeY;
    /* 70 */ u16 spawnCount; // children left to spawn; at zero the actor files its flags and is removed
} Vars_Matsuri;
#define VMATSURI(e) VARS(Vars_Matsuri, e)

extern u8 data_0212c4f4;      // spawn limit, children are not spawned while it is 0x70 or more
extern const u32 flagBits[];  // 4-byte flag table indexed by e->type
extern u16 data_0213492c[];   // (x, y) u16 pairs per area (same table as enemy/em12.h), x half
extern u16 em12_spawnOffsetY[]; // y half of the same pairs (0x0213492e)

#endif
