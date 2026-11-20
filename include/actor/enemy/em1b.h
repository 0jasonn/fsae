#ifndef ACTOR_ENEMY_EM1B_H
#define ACTOR_ENEMY_EM1B_H

#include "engine/entity.h"

// Type 1 (trailing segments). trail[] holds one packed (dx, dy) byte per frame slot, each nibble offset by 8.
typedef struct Vars_Em1bType1 {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 savedX;
    /* 72 */ u16 savedY;
    /* 74 */ u8 trail[8];
    /* 7c */ u32 frameAnims; // one animation nibble per trail slot
} Vars_Em1bType1;

typedef struct Vars_Em1b {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 savedX;     // copied from x in em1b_type0, one per frame
    /* 72 */ u16 savedY;     // copied from y in em1b_type0
    /* 74 */ Entity *child1; // second part, set by em1b_type0_init
    /* 78 */ Entity *child2; // third part
    /* 7c */ u8 unk_7c;
    /* 7d */ s8 dirDelta;    // added to e->direction every 4 frames, picked from em1b_dirDeltaTable
} Vars_Em1b;


// Hitbox tables of the em1b segments (rodata)
extern const u8 em1b_hitbox[];       // 0x020d0326, hitbox of the head (type 0)
extern const u8 em1b_otherHitbox[];  // 0x020d032e, hitbox of a type 1 segment that is not type 1 itself
extern const u8 em1b_type1Hitbox[];  // 0x020d0348

// Original names type0_init/type1_init(OBJ_WORK_*) are shared by many enemies, so these keep prefixed C names.
extern "C" {
void em1b_type0_init(Entity *e);  // 0x0202f138
void em1b_type1_init(Entity *e);  // 0x0202f3e4
}

#endif
