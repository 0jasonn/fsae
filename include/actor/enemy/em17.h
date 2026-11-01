#ifndef WIP_B_EM17_H
#define WIP_B_EM17_H

#include "engine/functions.h"

// Actor fields of em17 (file-local overlay, offsets from the original code).
typedef struct Vars_em17 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *target; // entity being carried / lifted (set in em17_move)
    /* 68 */ u8 unk_68[0x8];
    /* 70 */ union {
        u8 liftFlag;    // set by em17_batabata, cleared by em17_lift_throw
        u16 shakeTimer; // countdown in buruburu, also set by em17_fall
    } field70;
    /* 71 */ u8 unk_71;
    /* 72 */ u8 carryFlag; // non-zero while the actor carries its target
    /* 73 */ u8 carryTimer; // frames until the carry is dropped
} Vars_em17;

#define V(e) VARS(Vars_em17, e)

extern const EntityFunc em17_stateTable[];  // was em17_stateTable, passed to EnemyFunctionHandler
extern const EntityFunc em17_actionTable[]; // indexed by e->action, was em17_actionTable
extern const EntityFunc em17_liftTable[];   // indexed by e->subAction, was em17_liftTable
extern const u8 em17_hitbox[];              // was em17_hitbox
extern const u8 em17_hitboxLift[];          // was em17_hitboxLift, used by em17_damage and em17_lift_end
extern const u8 em17_throwHitbox[];         // was em17_throwHitbox

int buruburu(Entity *e); // returns 1 while the actor is still shaking

#endif
