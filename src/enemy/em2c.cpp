#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

typedef struct Vars_02033290 {
    /* 00 */ u8 unk_00[0x6e];
    /* 6e */ u16 demoTimer;
    /* 70 */ u8 unk_70[0xc];
    /* 7c */ u8 movePhase;      // 0 while waiting for the next move
    /* 7d */ u8 demoStep;       // set by the demo script
} Vars_02033290;
#define V(e) VARS(Vars_02033290, e)

extern const EntityFunc em2c_actions[];
extern const EntityFunc em2c_typeActions[];
extern const EntityFunc em2c_type0Actions[];
extern const u8 em2c_hitbox[];
extern Entity *data_0212c648;
extern u8 localPlayerIndex;
extern s32 em2c_leverDone;


ARM void Em2c(Entity *e) {
    EnemyFunctionHandler(e, em2c_actions);
    if (!(e->contactFlags & 0x80)) {
        return;
    }
    if ((e->contactFlags & 0x7f) != 0x10) {
        return;
    }
    data_0212ceb0[e->contactedEntity->type].state = 6;
    data_0212ceb0[e->contactedEntity->type].stateTimer = 1;
}

ARM void em2c_normal(Entity *e) {
    em2c_typeActions[e->type](e);
}

ARM void em2c_knockback(Entity *e) {
    GenericKnockback(e, em2c_actions);
}

ARM void em2c_type0(Entity *e) {
    em2c_type0Actions[e->action](e);
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 1)) {
        return;
    }
    e->frame = 0;
    e->unk_28 += Random() & 0x38;
}

ARM void em2c_type0_init_033378(Entity *e) {
    BindPlayers();
    if (set1st(e) == 0) {
        return;
    }
    e->action = 1;
    e->timer = 0x1e;
    e->spriteSettings.b0 = 1;
    e->hitbox = em2c_hitbox;
    e->unk_6a = 1;
    e->unk_5e.b0 = 0;
    InitAnimationForceUpdate(e, 0);
    data_0212c648 = e;
    CockpitOff();
}

ARM void em2c_type0_1stDemoWait_0333f0(Entity *e) {
    BindPlayers();
    if (V(e)->demoStep != 7) {
        return;
    }
    if (--e->timer != 0) {
        return;
    }
    e->action = 2;
    e->timer = 0xb4;
    V(e)->demoTimer = 0x4b0;
    SoundReq(0x19c);
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        data_0212c648 = data_0212ceb0[localPlayerIndex].entity;
    } else {
        data_0212c648 = data_0212ceb0[*Knife_Single_SinglePlay_GetInstance()].entity;
    }
    CockpitOn();
}

ARM void type0_1stMove(Entity *e) {
    if (V(e)->movePhase == 0) {
        if (e->timer != 0) {
            if (--e->timer == 0x5a) {
                InitAnimationForceUpdate(e, 0x1d);
            }
            return;
        }
        if (data_0212c7c8.stage != 1) {
            if (set2nd(e) == 0) {
                return;
            }
            e->action = 3;
            e->timer = 0x3c;
            e->y.WORD++;
            V(e)->demoTimer = 0xe10;
            em2c_leverDone = 0;
        } else {
            if (set3rd(e) == 0) {
                return;
            }
            e->action = 5;
            e->y.WORD++;
            V(e)->demoTimer = 0x4b0;
        }
        return;
    }
    V(e)->demoTimer--;
    if (V(e)->demoTimer != 0) {
        return;
    }
    V(e)->demoTimer = 0x4b0;
    TelopRequest(0x3f3);
}

ARM void type0_2ndDemoWait(Entity *e) {
    if (V(e)->demoStep == 3) {
        e->action = 4;
        e->timer = 0xb4;
    }
}

ARM void em2c_type0_2ndMove_0335b0(Entity *e) {
    if (V(e)->movePhase == 0) {
        if (e->timer != 0) {
            if (--e->timer == 0x5a) {
                InitAnimationForceUpdate(e, 0x1d);
            }
            return;
        }
        if (set3rd(e) == 0) {
            return;
        }
        e->action = 5;
        e->y.WORD++;
        V(e)->demoTimer = 0x4b0;
        return;
    }
    V(e)->demoTimer--;
    if (V(e)->demoTimer != 0) {
        return;
    }
    V(e)->demoTimer = 0xe10;
    if (em2c_leverDone == 0) {
        TelopRequest(0x3f5);
        return;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        return;
    }
    TelopRequest(0x3f4);
}

ARM void type0_3rdDemoWait(Entity *e) {
    if (V(e)->demoStep == 1) {
        e->action = 6;
    }
}

ARM void type0_3rdMove(Entity *e) {
    if (V(e)->movePhase == 0) {
        e->action = 7;
        e->timer = 0x96;
        return;
    }
    V(e)->demoTimer--;
    if (V(e)->demoTimer != 0) {
        return;
    }
    V(e)->demoTimer = 0xe10;
    TelopRequest(0x3f6);
}

ARM void type0_Die(Entity *e) {
    if (--e->timer == 0) {
        e->health = 0;
        e->statusFlags &= 0x7f;
    }
}
