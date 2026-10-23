#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"

// Second unit of actor em1b (type 0 movement, type 1). Vars_Em1b matches src/enemy/em1b.cpp plus the 0x7d field.
typedef struct Vars_Em1b {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 savedX;
    /* 72 */ u16 savedY;
    /* 74 */ Entity *child1;
    /* 78 */ Entity *child2;
    /* 7c */ u8 unk_7c;
    /* 7d */ s8 dirDelta;   // added to e->direction every 4 frames, picked from em1b_dirDeltaTable
} Vars_Em1b;

extern const s8 em1b_dirDeltaTable[]; // em1b_dirDeltaTable, two entries (-1, +1)

// Type 1 (trailing segments). trail[] holds one packed (dx, dy) byte per frame slot, each nibble offset by 8.
typedef struct Vars_Em1bType1 {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 savedX;
    /* 72 */ u16 savedY;
    /* 74 */ u8 trail[8];
    /* 7c */ u32 frameAnims; // one animation nibble per trail slot
} Vars_Em1bType1;

extern u16 frameCounter;
void ofsset(Entity *e); // em1b_2 is not the unit that defines it, see the note in the report
extern EntityFunc em1b_type1Actions[];   // em1b_type1Actions, indexed by e->action
extern const u8 em1b_type1Hitbox[];      // em1b_type1Hitbox, used when type == 1
extern const u8 em1b_otherHitbox[];      // em1b_otherHitbox, used for the other types

// Type 0 wander: turns the enemy every few frames and updates the walk animation.
ARM void em1b_type0_move(Entity *e) {
    Vars_Em1b *vars = VARS(Vars_Em1b, e);
    u8 nextAnim;

    e->timer--;
    if (e->timer == 0) {
        e->timer = 4;
        e->subtimer--;
        if (e->subtimer == 0) {
            e->subtimer = 8;
            vars->dirDelta = em1b_dirDeltaTable[Random() & 1];
        }
        e->direction = (e->direction + vars->dirDelta) & 0x1f;
        nextAnim = ((e->direction + 4) & 0x1c) >> 2;
        if (nextAnim != e->animationState) {
            e->animationState = nextAnim;
            InitAnimationForceUpdate(e, nextAnim);
        }
    }
    if (func_020847b0(e) != 0) {
        InitAnimationForceUpdate(e, e->animationState = ((e->direction + 4) & 0x1c) >> 2);
    }
    UpdateAnimationSingleFrame(e);
}

// Type 1 wrapper: runs the action table, then copies the parent's sprite flags and layer.
ARM void em1b_type1(Entity *e) {
    if (*(u32 *)&e->parent->unk_00[4] != 0) {
        em1b_type1Actions[e->action](e);
        e->spriteSettings.b30 = e->parent->spriteSettings.b30;
        e->spriteSettings.b14 = e->parent->spriteSettings.b14;
        e->layer = e->parent->layer;
    } else {
        PutObjWork(e);
    }
}
