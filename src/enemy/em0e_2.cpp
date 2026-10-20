#include "engine/functions.h"
#include "engine/entity.h"
#include "engine/player.h"
#include "global.h"

// Functions in this file (actor em0e, original names from the debug build; second unit of em0e):
//   em0e_type0_init, em0e_type0_nop, type0_motiage, motiage0_move, em0e_type0_actionDec,
//   em0e_type1, em0e_type1_init, em0e_type1_nop, type1_motiage, motiage1_move,
//   em0e_type2_actionDec, em0e_type2, type2_normal

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
extern u32 em0e_template[];
extern EntityFunc em0e_type0_motiageStates[];
extern EntityFunc em0e_type1_actions[];
extern EntityFunc em0e_type1_motiageStates[];
extern EntityFunc em0e_type2_normalActions[];
extern EntityFunc em0e_type2_actions[];
extern u8 em0e_dieSpawnTypes[];

ARM void em0e_type0_init(Entity *e) {
    Entity *motiage1;
    Entity *center;
    Entity *part3;

    motiage1 = GetObjWork();
    if (motiage1 == NULL) {
        return;
    }
    center = GetObjWork2(motiage1);
    if (center == NULL) {
        return;
    }
    part3 = GetObjWork2(center);
    if (part3 == NULL) {
        return;
    }
    motiage1->objKind = 3;
    center->objKind = 3;
    part3->objKind = 3;
    motiage1->objId = 0xe;
    center->objId = 0xe;
    part3->objId = 0xe;
    motiage1->type = 1;
    center->type = 2;
    part3->type = 3;
    ObjPosCopy(e, motiage1);
    EmPalamCopy(e, center);
    VARS(Vars_Em0e, center)->body0 = e;
    VARS(Vars_Em0e, center)->motiage1 = motiage1;
    center->child = part3;
    e->parent = center;
    motiage1->parent = center;
    part3->parent = center;
    RegistObjWork(4, motiage1);
    RegistObjWork(4, center);
    RegistObjWork(4, part3);
    e->spriteSettings.b0 = 0;
    e->unk_2e = 0;
    e->speed = 0x80;
    e->direction = 0x18;
    e->hitbox = (const void *)em0e_template[40];
    e->unk_1a = 1;
    e->linkedEntity = NULL;
    e->action++;
    InitAnimationForceUpdate(e, 3);
}

ARM void em0e_type0_nop(Entity *e) {
}

ARM void type0_motiage(Entity *e) {
    ObjHippariCheck(e);
    if (data_0212ceb0[e->type2].unk_03[2] == 0) {
        e->subAction = 6;
    }
    em0e_type0_motiageStates[e->subAction - 5](e);
}

ARM void motiage0_move(Entity *e) {
    PlayerData *player = &data_0212ceb0[e->type2];
    Entity *playerEntity = player->entity;

    if (player->unk_03[2] != 0) {
        VARS(Vars_Em0e, e->parent)->partFlags |= (u8)((e->type2 + 4) & 0xff);
        if (playerEntity->frame != 0) {
            if ((playerEntity->animationState & 2) == 0) {
                player->unk_03[2] = 0;
                playerEntity->iframes = 0xfe;
                playerEntity->unk_42 = 2;
                playerEntity->baseDirection = (playerEntity->animationState ^ 4) << 2;
                VARS(Vars_Em0e, e->parent)->partFlags &= 0xf0;
            } else if (playerEntity->animationState == 2) {
                VARS(Vars_Em0e, e->parent)->partFlags |= 8;
            }
        }
    } else {
        e->action--;
    }
}

ARM void em0e_type0_actionDec(Entity *e) {
    e->action--;
}

ARM void em0e_type1(Entity *e) {
    em0e_type1_actions[e->action](e);
}

ARM void em0e_type1_init(Entity *e) {
    e->spriteSettings.b0 = 0;
    e->unk_2e = 0;
    e->speed = 0x80;
    e->direction = 8;
    e->hitbox = (const void *)((u32 *)em0e_template)[41];
    e->unk_1a = 1;
    e->action++;
    InitAnimationForceUpdate(e, 4);
}

ARM void em0e_type1_nop(Entity *e) {
}

ARM void type1_motiage(Entity *e) {
    ObjHippariCheck(e);
    em0e_type1_motiageStates[e->subAction - 5](e);
}

ARM void motiage1_move(Entity *e) {
    PlayerData *player = &data_0212ceb0[e->type2];
    Entity *playerEntity = player->entity;

    if (player->unk_03[2] != 0) {
        VARS(Vars_Em0e, e->parent)->partFlags |= (u8)(((e->type2 + 4) << 4) & 0xff);
        if (playerEntity->frame != 0) {
            if ((playerEntity->animationState & 2) == 0) {
                player->unk_03[2] = 0;
                playerEntity->iframes = 0xfe;
                playerEntity->unk_42 = 2;
                playerEntity->baseDirection = (playerEntity->animationState ^ 4) << 2;
                VARS(Vars_Em0e, e->parent)->partFlags &= 0x0f;
            } else if (playerEntity->animationState == 6) {
                VARS(Vars_Em0e, e->parent)->partFlags |= 0x80;
            }
        }
    } else {
        e->action--;
    }
}

ARM void em0e_type2_actionDec(Entity *e) {
    e->action--;
}

ARM void em0e_type2(Entity *e) {
    Entity *other;

    func_02084700(e);
    other = func_020849c8(e);
    if (other != NULL) {
        func_02084ab8(e, other);
        if (e->spriteSettings.b0 != 0) {
            return;
        }
        PutObjWork(VARS(Vars_Em0e, e)->body0);
        PutObjWork(VARS(Vars_Em0e, e)->motiage1);
        return;
    }
    em0e_type2_actions[func_02084a30(e)](e);
}

ARM void type2_normal(Entity *e) {
    Vars_Em0e *vars;
    s32 y;

    em0e_type2_normalActions[e->action](e);
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

