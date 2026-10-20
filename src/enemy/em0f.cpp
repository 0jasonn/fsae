#include "engine/functions.h"
#include "engine/entity.h"
#include "engine/player.h"
#include "global.h"
#include "enemy/em0e_units.h"

// Functions in this file (actor em0f, original names from the debug build):
//   em0f_main (em0f_main), em0f_normal, em0f_damage, em0f_init (em0f_init), em0f_eyeopen,
//   em0f_meswait, em0f_flight

typedef struct Vars_Em0f {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *aimTarget; // EmGetAimPl() result, set by em0f_init
    /* 68 */ u8 unk_68[0x14];
    /* 7c */ u8 hitsLeft;       // hits still needed before the daruma state
    /* 7d */ u8 unk_7d;
    /* 7e */ u8 unk_7e;
    /* 7f */ u8 darumaMode;     // non-zero: darumaMgr takes over the update
} Vars_Em0f;

extern EntityFunc em0f_actions[];
extern EntityFunc em0f_normalActions[];
extern const u8 em0f_hitbox[];
extern Entity *data_0212c648;
extern u8 messageRequest;
extern u8 localPlayerIndex;
extern u16 data_0212c584[4];

ARM void em0f_main(Entity *e) {
    em0f_actions[func_02085294(e)](e);
}

ARM void em0f_normal(Entity *e) {
    if (VARS(Vars_Em0f, e)->darumaMode != 0) {
        darumaMgr(e);
        return;
    }
    em0f_normalActions[e->action](e);
}

ARM void em0f_damage(Entity *e) {
    Vars_Em0f *vars = VARS(Vars_Em0f, e);

    if (vars->hitsLeft != 0 && e->contactFlags == 0x96) {
        e->iframes = 0x3c;
        vars->hitsLeft--;
        vars->darumaMode = 7;
        e->zVelocity = 0x8000;
        vars->unk_7d = 0;
        InitAnimationForceUpdate(e, 0);
        EnqueueSFX(0x80);
    }
    GenericKnockback(e, em0f_actions);
}

ARM void em0f_init(Entity *e) {
    e->action = 1;
    e->unk_2e = 8;
    e->z.HALF.HI = -0x20;
    e->statusFlags |= 0x10;
    e->hitbox = em0f_hitbox;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b4 = 2;
    e->spriteSettings.b14 = 1;
    e->spriteSettings.b30 = 1;
    e->unk_5e.b0 = 3;
    e->unk_6a = 1;
    VARS(Vars_Em0f, e)->aimTarget = EmGetAimPl();
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        switch (data_0212c7c8.unk_0) {
            case 2:
                e->health = 0x4c;
                break;
            case 3:
                e->health = 0x60;
                break;
            case 4:
                e->health = 0x80;
                break;
        }
    }
    InitAnimationForceUpdate(e, 5);
    BindPlayers();
}

ARM void em0f_eyeopen(Entity *e) {
    u8 i;

    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        PlayerData *player = &data_0212ceb0[i];
        if (player->entity->z.HALF.HI == 0) {
            player->unk_08 = 0;
            player->entity->direction = 0xff;
        }
    }
    BindPlayers();
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->action = 2;
        e->subAction = 0;
        e->timer = 5;
        MessageRequest(0x193);
    }
}

ARM void em0f_meswait(Entity *e) {
    u16 i;

    BindPlayers();
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    if (e->subAction == 0) {
        if ((messageRequest & 0x7f) != 6) {
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
    e->action = 3;
}

ARM void em0f_flight(Entity *e) {
    void *app;

    app = KnifeApp_getInstance();
    if ((KnifeApp_isWirelessMode(app) != 0 && data_0212c648 != data_0212ceb0[localPlayerIndex].entity) ||
        (KnifeApp_isWirelessMode(app) == 0 && data_0212c648 != data_0212ceb0[0].entity &&
         data_0212c648 != data_0212ceb0[1].entity)) {
        BindPlayers();
    }
    e->z.WORD -= 0x8000;
    if (e->z.HALF.HI != -0x40) {
        return;
    }
    e->action = 4;
    e->timer = 0x32;
    e->poseId = 1;
    InitAnimationForceUpdate(e, 0);
}
