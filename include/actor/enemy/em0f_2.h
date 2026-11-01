#ifndef WIP_E_EM0F_2_H
#define WIP_E_EM0F_2_H

#include "engine/entity.h"

// Actor em0f, second unit (src/enemy/em0f.cpp is the first). Shared by src/wip/E/em0f_2.cpp, em0f_3.cpp.

// Not yet in engine/functions.h (mangled name _Z20CalculateDirectionTossss)
u8 CalculateDirectionTo(s16 x, s16 y, s16 a, s16 b);

typedef struct Vars_Em0f {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *aimTarget;      // EmGetAimPl() result, retargeted by homingMoveSet
    /* 68 */ u8 unk_68[8];
    /* 70 */ u16 homingTimer;        // counts down the homing phase, 0 starts the attack
    /* 72 */ u8 dashCount;           // speed-change cycles left before homingMoveSet picks a new aim
    /* 73 */ u8 unk_73;
    /* 74 */ u16 accel;              // added to speed every 8 frames by spdchange
    /* 76 */ u8 attackMode;          // low nibble kept across states, bit 0 set in em0f_vacuumWait
    /* 77 */ u8 darumaTimer;         // frames of the daruma wait, then the phase-2 steps
    /* 78 */ u8 unk_78[4];
    /* 7c */ u8 tatsumakiCount;      // whirlwind children spawned by em0f_setTatsumaki
    /* 7d */ u8 unk_7d;              // set by vacuumSet, cleared by em0f_vacuum
    /* 7e */ u8 unk_7e;              // checked by em0f_vacuum
    /* 7f */ u8 darumaMode;          // non-zero: darumaMgr takes over the update
} Vars_Em0f;

// ROM data (names from symbols.txt, renamed in scratch/agentE/renames.txt)
extern Entity *data_0212c648;
extern u8 localPlayerIndex;
extern u8 data_0212c618;
extern const u8 em0f_aimPlayerTable[];    // em0f_aimPlayerTable, 3 entries per Entity type
extern const u8 em0f_dashCountTable[];    // em0f_dashCountTable, indexed by Random() & 3
extern const u16 em0f_homingTimerTable[]; // em0f_homingTimerTable, indexed by Random() & 3
extern const s8 em0f_zLimitTable[];       // em0f_zLimitTable, height limit per tatsumakiCount
extern EntityFunc em0f_attackModeFuncs[]; // em0f_attackModeFuncs, indexed by attackMode >> 4

// Functions of this unit that another file or the parked functions call
void spdchange(Entity *e);
void homingMoveSet(Entity *e);
void vacuumSet(Entity *e);
void thunderSet(Entity *e);
void homingSet(Entity *e);

#endif
