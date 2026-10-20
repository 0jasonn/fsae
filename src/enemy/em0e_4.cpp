#include "engine/functions.h"
#include "engine/entity.h"
#include "engine/player.h"
#include "global.h"
#include "enemy/em0e_units.h"

// Functions in this file (actor em0e, original names from the debug build; fourth unit of em0e):
//   em0e_type3, type3_init, type3_move

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

ARM void em0e_type3(Entity *e) {
    em0e_type3_actions[e->action](e);
}

ARM void type3_init(Entity *e) {
    e->spriteSettings.b0 = 0;
    e->action++;
    InitAnimationForceUpdate(e, 5);
}

ARM void type3_move(Entity *e) {
    Entity *parent = e->parent;

    if (parent->health != 0) {
        ObjPosCopy(parent, e);
        e->y.WORD--;
        e->y.HALF.HI += em0e_type3_moveOffsets[e->timer >> 1];
        UpdateAnimationSingleFrame(e);
    } else {
        PutObjWork(e);
    }
}
