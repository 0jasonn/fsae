#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/set66.h"

// Set66 actor (module set66). Address -> name:
//   0x0207502c Set66 (original name; dispatches on e->type)
//   0x02075048 set66_type0 (original name; dispatches on e->action)
//   0x02075064 rr_type0_init_075064 (dsd name, original type0_init)
//   0x020750f8 rr_type0_wait (dsd name, original type0_wait)
//   0x020751e4 rr_type0_move (dsd name, original type0_move)
//   0x02075218 type0_setgufu (original name)

ARM void Set66(Entity *e) {
    set66_typeActions[e->type](e);
}

ARM void set66_type0(Entity *e) {
    set66_type0Actions[e->action](e);
}

ARM void rr_type0_init_075064(Entity *e) {
    const s16 *pos;
    u16 i;
    Entity *spawn;

    pos = rr_type0_posTable[data_0212c7c8.unk_0 - 1];
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        spawn = GetSetWork(0x66, 1, (u8)i);
        if (spawn != NULL) {
            spawn->parent = e;
            ObjPosCopyOfs32(e, spawn, pos[0] << 16, pos[1] << 16);
            pos += 2;
        }
    }
    e->action = 1;
}

ARM void rr_type0_wait(Entity *e) {
    Vars_Set66 *v;
    u8 i;

    v = VARS(Vars_Set66, e);
    if (data_0212c7c8.unk_0 != CountBits(v->typeBits)) {
        return;
    }
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        if (plStCheck(&data_0212ceb0[i])) {
            return;
        }
    }
    e->action = 2;
    v->typeBits = 0xffff;
    data_0212c618 = 2;
    BindPlayers();
    Scene_SetFlag5();
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        data_0212ceb0[i].state = 0xf;
        data_0212ceb0[i].unk_08 = 0xc3;
        data_0212ceb0[i].stateTimer = 0xb4;
        data_0212ceb0[i].unk_39 = 1;
        data_0212ceb0[i].entity->animationState = 4;
    }
}

ARM void rr_type0_move(Entity *e) {
    Vars_Set66 *v;

    v = VARS(Vars_Set66, e);
    BindPlayers();
    if (16 - data_0212c7c8.unk_0 == CountBits(v->typeBits)) {
        e->action = 3;
    }
}

ARM void type0_setgufu(Entity *e) {
    BindPlayers();
    if (GetEnemyWork(0x2f) != NULL) {
        PutObjWork(e);
    }
}
