#ifndef WIP_B_EM22_2_H
#define WIP_B_EM22_2_H

#include "engine/functions.h"
#include "enemy/em22.h"

extern u16 frameCounter; // frame counter (frameCounter)

extern const u8 em22_hitbox[];          // em22_hitbox, hitbox of em22
extern const EntityFunc em22_stateTable[]; // em22_stateTable, GenericKnockback table of em22
extern const u8 em22_dmgAnimTable[];    // em22_dmgAnimTable, animation per damage stage
extern const u8 em22_aimTimerTable[];   // em22_aimTimerTable, aim time picked by Random() & 7
extern const u8 em22_moveTimerTable[];  // em22_moveTimerTable, move time picked by Random() & 7

// Actor-specific fields of em22 (0x64 onwards, see Entity for the rest).
typedef struct Vars_em22 {
    u8 unk_00[0x64];
    Entity *aimTarget;  // 0x64: player the actor aims at, from func_02084f98
    u8 unk_68[0x14];
    u8 damageStage;     // 0x7c: number of hits taken (0..3), moves to the next pose
    u8 damageTimer;     // 0x7d: frames left in the current damage stage
    u8 speedTimer;      // 0x7e: frames until the speed is raised again (spdmgr)
} Vars_em22;

void spdmgr(Entity *e); // original spdmgr(OBJ_WORK_*), speed up while the actor moves

#endif
