#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/set66.h"

// Set66 actor (module set66). Address -> name:
//   0x0207502c Set66 (original name; dispatches on e->type)
//   0x02075048 set66_type0 (original name; dispatches on e->action)
//   0x02075064 rr_type0_init_075064 (dsd name, original type0_init)
//   0x020750f8 rr_type0_wait (dsd name, original type0_wait)
//   0x020751e4 rr_type0_move (dsd name, original type0_move)
//   0x02075218 type0_setgufu (original name)

void Set66(Entity *e) {
    set66_typeActions[e->type](e);
}

void set66_type0(Entity *e) {
    set66_type0Actions[e->action](e);
}

void rr_type0_init_075064(Entity *e) {
    const s16 *pos;
    u16 i;
    Entity *spawn;

    pos = rr_type0_posTable[gameState.playerCount - 1];
    for (i = 0; i < gameState.playerCount; i++) {
        spawn = GetSetWork(0x66, 1, (u8)i);
        if (spawn != NULL) {
            spawn->parent = e;
            ObjPosCopyOfs32(e, spawn, pos[0] << 16, pos[1] << 16);
            pos += 2;
        }
    }
    e->action = 1;
}

void rr_type0_wait(Entity *e) {
    Vars_Set66 *v;
    u8 i;

    v = VARS(Vars_Set66, e);
    if (gameState.playerCount != CountBits(v->typeBits)) {
        return;
    }
    for (i = 0; i < gameState.playerCount; i++) {
        if (plStCheck(&playerWork[i])) {
            return;
        }
    }
    e->action = 2;
    v->typeBits = 0xffff;
    cockpitState = 2;
    BindPlayers();
    Scene_SetFlag5();
    for (i = 0; i < gameState.playerCount; i++) {
        playerWork[i].state = 0xf;
        playerWork[i].motionId = 0xc3;
        playerWork[i].stateTimer = 0xb4;
        playerWork[i].unk_39 = 1;
        playerWork[i].entity->animationState = 4;
    }
}

void rr_type0_move(Entity *e) {
    Vars_Set66 *v;

    v = VARS(Vars_Set66, e);
    BindPlayers();
    if (16 - gameState.playerCount == CountBits(v->typeBits)) {
        e->action = 3;
    }
}

void type0_setgufu(Entity *e) {
    BindPlayers();
    if (GetEnemyWork(0x2f) != NULL) {
        PutObjWork(e);
    }
}

// Set66 type1 (module set66, second unit). Address -> name:
//   0x02075240 set66_type1 (original name; dispatches on e->action)
//   0x0207525c rr_type1_init_07525c (dsd name, original type1_init)
//   0x0207528c type1_charload (original name)
//   0x020752f8 rr_type1_move (dsd name, original type1_move)
//   0x0207543c rr_type1_wait_07543c (dsd name, original type1_wait)
//   0x020754ac rr_type1_vanish (dsd name, original type1_vanish)
//   0x02075528 rr_poscopy (original name)
//   0x0207553c plStCheck (original name)

void set66_type1(Entity *e) {
    set66_type1Actions[e->action](e);
}

void rr_type1_init_07525c(Entity *e) {
    e->action = 1;
    e->timer = 0x1e;
    e->spriteSettings.b14 = 3;
    InitAnimationForceUpdate(e, 0);
}

void type1_charload(Entity *e) {
    Vars_Set66 *v;

    if (e->timer != 0) {
        e->timer--;
        return;
    }
    if (VGroupLoadWait(e)) {
        return;
    }
    v = VARS(Vars_Set66, e);
    func_020845b0((u32)(0x6400000 + ((v->vramSlot + 1) << 9)),
                  KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x9a) + 0x200, 0x100);
    e->action = 2;
    e->spriteSettings.b0 = 1;
}
