#ifndef WIP_E_EM1A_H
#define WIP_E_EM1A_H

#include "engine/entity.h"

// Actor em1a (original names from the debug build). Shared by src/wip/E/em1a.cpp and em1a_2.cpp.
typedef struct Vars_Em1a {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u8 unk_64[0xa];
    /* 6e */ u16 revivalTimer;   // set to 0x2d0 on a spawned copy, counts down while the enemy is revived
    /* 70 */ const u8 *infoPtr;  // current entry of the route table, see em1a_getNextInfo
    /* 74 */ const u8 *infoBase; // start of the route table returned by GetInfoAdrs
    /* 78 */ u16 targetX;        // next waypoint x, used by the em1a_move_* functions
    /* 7a */ u16 targetY;        // next waypoint y
    /* 7c */ u16 homeX;          // position at init, copied to a spawned copy by em1a_damage
    /* 7e */ u16 homeY;
} Vars_Em1a;

// ROM tables and data (names from symbols.txt)
extern const u8 em1a_hitbox[];            // em1a_hitbox
extern EntityFunc em1a_actions[];         // em1a_actions, indexed by func_02084a30(e)
extern EntityFunc em1a_normalActions[];   // em1a_normalActions, indexed by e->action
extern EntityFunc em1a_moveActions[];     // em1a_moveActions, indexed by e->subAction
extern const s8 em1a_bobTable[];          // em1a_bobTable, z offset from frameCounter and subtimer
extern u16 frameCounter;                  // frameCounter

typedef struct UnkStruct_0212c540 {
    u16 unk_0;
    u16 unk_2;
} UnkStruct_0212c540;
extern UnkStruct_0212c540 data_0212c540;

// Not yet in engine/functions.h
void em1a_getNextInfo(Entity *e);

#endif
