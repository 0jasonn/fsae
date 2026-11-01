#ifndef WIP_B_EM16_H
#define WIP_B_EM16_H

#include "engine/functions.h"

// Actor fields of em16 (file-local overlay, offsets from the original code).
typedef struct Vars_em16 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *target; // entity the actor steers towards (set by em16_kyoro / kyoroSet clears it)
    /* 68 */ u8 unk_68[0x8];
    /* 70 */ u16 waitTimer; // frame counter, counted down in frontCheck; em16_nage sets it to 0x3c
} Vars_em16;

#define V(e) VARS(Vars_em16, e)

extern const EntityFunc em16_stateTable[]; // was em16_stateTable, passed to EnemyFunctionHandler / GenericKnockback
extern const EntityFunc em16_actionTable[]; // indexed by e->action, was em16_actionTable
extern const u8 em16_hitbox[];             // was em16_hitbox
extern const u8 em16_animTable[];          // animation per animationState (0..3), was em16_animTable
extern const u8 em16_timerTable[];         // random wait times for em16_getdir, was em16_timerTable

void kyoroSet(Entity *e);
BOOL frontCheck(Entity *e);
void func_02085990(Entity *e); // label, thumb, called after UpdateAnimationSingleFrame in em16_dush (no C++ name yet)

#endif
