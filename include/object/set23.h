#ifndef WIP_G_SET23_H
#define WIP_G_SET23_H

#include "engine/functions.h"
#include "object/setcommon.h"

// Actor fields of the Set23 family (file-local overlay, offsets from the original code).
typedef struct Vars_Set23 {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits;   // ParseTypeBits(type), tested against em12_typeMasks[area] in set23_wait
    /* 64 */ u8 unk_64[0x18];
    /* 7c */ u16 closeTimer; // frames of the closing animation
} Vars_Set23;

extern const EntityFunc set23_stateTable[]; // indexed by e->action, was set23_stateTable
extern const u16 set23_kindTable[];        // was set23_kindTable, indexed by the animation index (below 5)
extern const u16 set23_valueTable[];       // was set23_valueTable, indexed by the entry byte 1
extern const u8 *set23_ptrTable[];         // was bgmIndexTable, 8-byte entries per index
extern const u8 set23_hitbox[];            // was set23_hitbox, hitbox of the actor
extern const u32 flagBits[];               // area mask bit per type

#endif
