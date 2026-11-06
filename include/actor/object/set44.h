#ifndef WIP_A_SET44_H
#define WIP_A_SET44_H

#include "engine/functions.h"
#include "global.h"
#include "game/player_flags.h"
#include "actor/object/cellcalls.h"
#include "actor/object/nemoto_3.h"
#include "engine/player.h"

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

// Entity of player i (PlayerData.entity at +0x28 in each 0x94-byte block)
#define PLAYER_ENTITY(i) (playerWork[i].entity)

void Set44(Entity *e);
void set44_init(Entity *e);
void set44_wait(Entity *e);
void set44_move(Entity *e);
void set44_reset(Entity *e);

#endif
