#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/setmisc.h"

// Set5f actor (module set5f). Address -> name:
//   0x02060104 Set5f (original name)
//   0x02060120 set5f_type0, 0x02060140 set5f_type0_init, 0x020601ec type0_initWait
//   0x02060280 type0_plEntrance, 0x020602f8 type0_meswait, 0x02060404 type0_fall
//   (type0_tenmetsu at 0x02060450 is in scratch/agentG/nonmatching; the rest is in set5f_2.cpp)

typedef struct Vars_Set5f {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u16 messageId; // message shown by type0_meswait
} Vars_Set5f;

extern const EntityFunc set5f_typeHandlers[]; // set5f_typeHandlers, indexed by e->type
extern const EntityFunc set5f_type0Actions[]; // set5f_type0Actions, indexed by e->action
extern u8 messageRequest[];
extern Entity *data_0212c648;
extern s16 scrollArgs[3];
extern const s16 data_020d7e58[];
extern const s16 data_020d7f58[];
extern const s8 data_020d90ac[];
extern const s8 data_020d90c0[];

void set5f_plset(Entity *e);

ARM void Set5f(Entity *e) {
    set5f_typeHandlers[e->type](e);
}

ARM void set5f_type0(Entity *e) {
    set5f_type0Actions[e->action](e);
    BindPlayers();
}

ARM void set5f_type0_init(Entity *e) {
    Entity *child;

    child = GetSetWork(0x5f, 1, 0);
    if (child == NULL) {
        return;
    }
    ObjPosCopy(e, child);
    e->child = child;
    e->action = 1;
    e->timer = 0xb4;
    e->spriteSettings.b0 = 1;
    e->z.HALF.HI = -0x78;
    e->unk_5e.b0 = 3;
    VARS(Vars_Set5f, e)->messageId = 0x191;
    InitAnimationForceUpdate(e, 0);
    set5f_plset(e);
    data_0212c648 = e;
    Scene_SetFlag5();
    CockpitOff();
    ScrPosSet(e->x.HALF.HI, e->y.HALF.HI);
}

ARM void type0_initWait(Entity *e) {
    u8 i;

    GufuFuyusnd(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 2;
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        data_0212ceb0[i].state = 0xf;
        data_0212ceb0[i].unk_08 = 4;
        data_0212ceb0[i].stateTimer = 0xff;
        data_0212ceb0[i].entity->direction = 0;
        data_0212ceb0[i].entity->animationState = 0;
    }
}

ARM void type0_plEntrance(Entity *e) {
    u8 i;

    GufuFuyusnd(e);
    if (data_0212ceb0[0].entity->y.HALF.HI > 0x21c) {
        return;
    }
    e->action = 3;
    e->timer = 0x3c;
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        data_0212ceb0[i].entity->timer = 1;
    }
}

ARM void type0_meswait(Entity *e) {
    u16 i;

    UpdateAnimationSingleFrame(e);
    GufuFuyusnd(e);
    if (e->timer != 0) {
        e->timer--;
        if (e->timer != 5) {
            return;
        }
        e->subAction = 0;
        MessageRequest(VARS(Vars_Set5f, e)->messageId);
        if (e->action == 3) {
            messageRequest[3] = (messageRequest[3] & ~0x1f) | 1;
            messageRequest[4] = (messageRequest[4] & ~0x1f) | 5;
        }
        SoundReq(0x203);
        return;
    }
    if (e->subAction == 0) {
        if ((messageRequest[0] & 0x7f) != 6) {
            return;
        }
        Status_ArmIfEnabled();
        e->subAction = 1;
        return;
    }
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        if (data_0212c584[i] & 0x1000) {
            return;
        }
    }
    e->action++;
}

ARM void type0_fall(Entity *e) {
    UpdateAnimationSingleFrame(e);
    GufuFuyusnd(e);
    e->z.WORD += 0x8000;
    if (e->z.HALF.HI < -0x20) {
        return;
    }
    e->action = 5;
    e->timer = 0x3c;
    VARS(Vars_Set5f, e)->messageId = 0x192;
}
