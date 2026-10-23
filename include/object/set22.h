#ifndef WIP_G_SET22_H
#define WIP_G_SET22_H

#include "engine/functions.h"
#include "object/setcommon.h"

// Actor fields of the Set22 family (file-local overlay, offsets from the original code).
typedef struct Vars_Set22 {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u32 typeBits;   // ParseTypeBits(type) of the wait command, tested against em12_typeMasks[area]
    /* 74 */ u16 waitTimer;  // frames to wait before the next command (x 60)
    /* 76 */ u16 frameTimer; // countdown started from e->timer
    /* 78 */ u16 *scriptPtr; // command stream of the actor, advanced by setinfo
    /* 7c */ u16 cellX;      // grid cell position, from the low bits of the entity x
    /* 7e */ u16 cellY;      // grid cell position, from the low bits of the entity y
} Vars_Set22;

extern const EntityFunc set22_stateTable[]; // indexed by e->action, was set22_stateTable
extern u16 data_0213492c[];                 // (x, y) u16 pairs per area, see enemy/em12.h
extern u16 em12_spawnOffsetY[];             // y offset per area (same table as data_0213492c[1 + 2 * area])
extern const u32 flagBits[];                  // area mask bit per type
extern "C" u16 *setinfo(Entity *e, u16 *script);

#endif
