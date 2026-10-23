#ifndef WIP_E_EM1C_H
#define WIP_E_EM1C_H

#include "engine/entity.h"

// Actor em1c. Declarations of functions defined in other units of the same actor, and of its data.
typedef struct Vars_Em1c {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *grabbed;      // set from func_02084f98 while the enemy holds an object, NULL otherwise
    /* 68 */ u8 unk_68[8];
    /* 70 */ u8 cachedQuadrant;    // last value of em1c_charAnimTable, see charMove
    /* 71 */ u8 cooldown;          // counts down, set to 0x78 when an attack ends
} Vars_Em1c;

// Shared state (em1c_sharedState): two words, both cleared by em1c_init.
typedef struct Em1cSharedState {
    /* 00 */ u32 unk_00;
    /* 04 */ u32 timer;
} Em1cSharedState;
extern Em1cSharedState em1c_sharedState;

extern EntityFunc em1c_actions[];         // em1c_actions, indexed by e->action through EnemyFunctionHandler
extern EntityFunc em1c_normalActions[];   // em1c_normalActions, indexed by e->action
extern const u8 em1c_hitbox[];            // em1c_hitbox
extern const u8 em1c_charAnimTable[];     // em1c_charAnimTable, indexed by ((child->direction + 4) & 0x18) >> 3

void EmMagneMove(Entity *e, u16 speed);   // EmMagneMove
void em1c_waitSet(Entity *e);             // em1c_waitSet, in em1c_2.cpp
void charMove(Entity *e, u8 mode);        // charMove, in em1c_2.cpp

#endif
