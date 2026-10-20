#include "engine/functions.h"
#include "engine/entity.h"
#include "engine/player.h"
#include "global.h"
#include "enemy/em0e_units.h"

// Functions in this file (actor em0e, original names from the debug build; third unit of em0e):
//   type2_damage, type2_buttobi, type2_die, em0e_type2_init, em0e_type2_move

typedef struct Vars_Em0e {
    /* 00 */ u8 unk_00[0x6c];
    /* 6c */ u8 unk_6c[2];
    /* 6e */ u16 pieceOffset;  // x offset of motiage1 from body0 (type2_piyori)
    /* 70 */ u8 unk_70;
    /* 71 */ u8 unk_71;
    /* 72 */ u8 unk_72[2];
    /* 74 */ u8 lastHealth;     // health seen at the last hit check
    /* 75 */ u8 partFlags;      // bit flags of the body parts
    /* 76 */ u16 timeout;
    /* 78 */ Entity *body0;     // the type 0 body this group is built around
    /* 7c */ Entity *motiage1;  // the type 1 part
} Vars_Em0e;

// Hitbox pointers and the action tables of this actor (dsd names: em0e_template, em0e_type1_actions, ...)
extern const u32 em0e_template[];
extern EntityFunc em0e_type0_motiageStates[];
extern EntityFunc em0e_type1_actions[];
extern EntityFunc em0e_type1_motiageStates[];
extern EntityFunc em0e_type2_normalActions[];
extern EntityFunc em0e_type2_actions[];
extern u8 em0e_dieSpawnTypes[];
extern u16 em0e_scrollTable[];
extern EntityFunc em0e_type3_actions[];
extern s8 em0e_type3_moveOffsets[];
extern u16 scrollArgs[3];

ARM void type2_damage(Entity *e) {
    Vars_Em0e *vars;

    if (e->action == 1) {
        vars = VARS(Vars_Em0e, e);
        if (vars->lastHealth != e->health) {
            e->action++;
            e->z.HALF.HI = -10;
            e->zVelocity = 0x12000;
            e->poseId = 0x19;
            e->attackKnockback = 2;
            e->iframes = e->iframes << 1;
            e->unk_42 = 0;
            e->hitbox = (const void *)em0e_template[39];
            vars->timeout = 0x4b0;
            e->health = 0xff;
            vars->lastHealth = 0xff;
            e->animationState = 1;
            InitAnimationForceUpdate(e, 1);
        }
    }
    if (VARS(Vars_Em0e, e)->partFlags != 0 || VARS(Vars_Em0e, e)->pieceOffset != 0) {
        e->unk_42 = 0;
    }
    GenericKnockback(e, em0e_type2_actions);
}

ARM void type2_buttobi(Entity *e) {
    Vars_Em0e *vars;
    s32 y;

    func_02084788(e);
    if (e->health == 0) {
        return;
    }
    vars = VARS(Vars_Em0e, e);
    if ((vars->partFlags & 0x44) != 0x44) {
        y = e->y.WORD;
        if ((u16)y != 0xffff) {
            e->y.WORD = y + 1;
        }
        ObjPosCopy(e, vars->body0);
        ObjPosCopy(e, vars->motiage1);
        e->y.WORD--;
    }
    vars->partFlags = 0;
}

ARM void type2_die(Entity *e) {
    Entity *spawn;

    func_02085d34(e);
    PutObjWork(VARS(Vars_Em0e, e)->body0);
    PutObjWork(VARS(Vars_Em0e, e)->motiage1);
    spawn = GetSetWork(0, em0e_dieSpawnTypes[Random() & 7], 1);
    if (spawn != NULL) {
        spawn->direction = 0x88;
        ObjPosCopy(e, spawn);
    }
    spawn = GetSetWork(0, em0e_dieSpawnTypes[Random() & 7], 1);
    if (spawn != NULL) {
        spawn->direction = 0x98;
        ObjPosCopy(e, spawn);
    }
    EmDie(e);
}

ARM void em0e_type2_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 6;
    e->statusFlags |= 0x80;
    e->hitbox = (const void *)em0e_template[38];
    VARS(Vars_Em0e, e)->lastHealth = e->health;
    e->action++;
    e->timer = 1;
    VARS(Vars_Em0e, e)->unk_71 = 0x20;
    InitAnimationForceUpdate(e, 0);
}

ARM void em0e_type2_move(Entity *e) {
    if (e->animationState == 2) {
        e->poseId = 0x18;
        e->hitbox = (const void *)em0e_template[38];
        e->animationState = 0;
        InitAnimationForceUpdate(e, 0);
        func_02085d34(e);
        VARS(Vars_Em0e, e)->body0->spriteSettings.b0 = 0;
        VARS(Vars_Em0e, e)->motiage1->spriteSettings.b0 = 0;
    }
    if (--e->timer == 0) {
        e->timer = 0x1e;
        e->direction = Random() & 0x1f;
    }
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
}

