#ifndef WIP_A_SET44_H
#define WIP_A_SET44_H

#include "engine/functions.h"
#include "global.h"
#include "game/gamestateview_c.h"
#include "object/cellcalls.h"
#include "object/nemoto_3.h"

// Tables and data of the Set44 family (file-local, from the original code).
typedef struct BgmIndexEntry {
    /* 00 */ const u8 *table; // record table, byte 1 indexes set44VgroupTable
    /* 04 */ u32 unk_4;
} BgmIndexEntry;

extern const EntityFunc set44Table[];     // set44Table, indexed by action
extern const u8 set44Hitbox[];            // set44Hitbox, copied into e->hitbox
extern const u16 set44VgroupIds[];        // set44VgroupIds, indexed by pickIndex (< 5)
extern const u16 set44VgroupTable[];      // set44VgroupTable, indexed by a bgm row byte
extern const s16 set44MoveOffsets[];      // set44MoveOffsets, (dx, dy) pairs indexed by direction >> 2
extern const s16 cellDeltaTable[];        // cellDeltaTable, indexed by direction >> 3
extern const u32 flagBits[];              // flagBits, indexed by playerCount - 1
extern const BgmIndexEntry *const bgmIndexTable[];
extern u8 data_0212ceb0[];                // PlayerData block array, 0x94 bytes per player

// Entity of player i (PlayerData.entity at +0x28 in each 0x94-byte block)
#define PLAYER_ENTITY(i) (*(Entity **)(data_0212ceb0 + (i) * 0x94 + 0x28))

void Set44(Entity *e);
void set44_init(Entity *e);
void set44_wait(Entity *e);
void set44_move(Entity *e);
void set44_reset(Entity *e);

#endif
