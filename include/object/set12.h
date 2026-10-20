#ifndef WIP_G_SET12_H
#define WIP_G_SET12_H

#include "engine/functions.h"
#include "engine/player.h"
#include "object/setcommon.h"

// Set12 actor fields and tables, shared by the set12 units.
typedef struct Vars_Set12 {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 requestBits; // low nibble: pending request, bits 4..7: slot of the current move
    /* 64 */ u8 unk_64[0x10];
    /* 74 */ u8 isPresent;    // cleared when the area mask no longer matches
    /* 75 */ u8 lastSlot;     // slot used by the previous set12_move
    /* 76 */ u8 unk_76[2];
    /* 78 */ u16 homeX;       // position saved by set12_init
    /* 7a */ u16 homeY;
} Vars_Set12;

typedef struct Set12MusicEntry {
    const u8 *table; // record table, byte 1 is the index used for the vgroup lookup
    u32 unk_4;
} Set12MusicEntry;

extern const EntityFunc set12_stateTable[];   // indexed by e->action (was set12_stateTable)
extern const u8 set12_hitbox[];               // was set12_hitbox
extern const u8 set12_directionTable[];       // was set12_directionTable, indexed by the move slot
extern const u16 set12_vgroupIdsA[];          // was set12_vgroupIdsA
extern const u16 set12_vgroupIdsB[];          // was set12_vgroupIdsB
extern const Set12MusicEntry *const bgmIndexTable[];
extern u32 em12_typeMasks[];
extern const u32 flagBits[];

#endif
