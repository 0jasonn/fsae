#include "engine/functions.h"
#include "engine/entity.h"
#include "engine/player.h"
#include "global.h"
#include "enemy/em0e_units.h"
#include "enemy/em0e.h"

// Functions in this file (actor em0e, original names from the debug build; fourth unit of em0e):
//   em0e_type3, type3_init, type3_move

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

void em0e_type3(Entity *e) {
    em0e_type3_actions[e->action](e);
}

void type3_init(Entity *e) {
    e->spriteSettings.b0 = 0;
    e->action++;
    InitAnimationForceUpdate(e, 5);
}

void type3_move(Entity *e) {
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
