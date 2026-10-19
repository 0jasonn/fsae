#include "engine/functions.h"
#include "enemy/em2f.h"
#include "global.h"

ARM void em2f_main(Entity *e) {
    if (e->health == 0 && e->action < 0x23) {
        e->action = 0x23;
    }
    em2f_actions[e->action](e);
}

ARM void em2f_init(Entity *e) {
    e->action = 1;
    e->timer = 0xb4;
    e->x.HALF.HI = 0x1f8;
    e->y.HALF.HI = 0x188;
    e->z.HALF.HI = -0x70;
    e->spriteSettings.b4 = 2;
    e->unk_5e.b2 = 2;
    e->hitbox = em2f_hitbox;
    V(e)->attackSeed = Random();
    e->health = em2f_healthByDifficulty[data_0212c7c8.unk_3];
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        switch (data_0212c7c8.unk_0) {
            case 2:
                e->health = e->health + e->health / 5;
                break;
            case 3:
                e->health = 0xff;
                break;
            case 4:
                e->health = 0xff;
                break;
        }
    }
    e->unk_6a = 1;
    func_0208ae30(e);
    InitAnimationForceUpdate(e, 0);
    BindPlayers();
    SoundReq(0x80080000);
    data_0212c7c8.unk_26 = 0xffff;
}

ARM void em2f_initWait(Entity *e) {
    BindPlayers();
    u8 timer = --e->timer;
    if (timer == 0) {
        e->action = 2;
        e->timer = 0x78;
        e->spriteSettings.b0 = 1;
        data_0212c648 = e;
        for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
            data_0212ceb0[i].entity->animationState = 0;
            BikkuriSet(data_0212ceb0[i].entity, -8, -12);
        }
        return;
    }
    if (e->subtimer < 0x20) {
        e->subtimer++;
        data_0212c5ac.unk_c = 0xfff0;
        data_0212c5ac.unk_7 = 0;
        MakeFadeBuff256((e->subtimer >> 2) << 4);
        data_0212c5ac.unk_c = -1;
        return;
    }
    if (timer >= 0x96) {
        return;
    }
    if (timer & 0xf) {
        return;
    }
    for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
        if (Random() & 7) {
            data_0212ceb0[i].entity->animationState = Random() & 6;
        }
    }
}

ARM void em2f_appear(Entity *e) {
    BindPlayers();
    UpdateAnimationSingleFrame(e);
    GufuFuyusnd(e);
    e->z.WORD += 0x8000;
    if (e->z.HALF.HI != -0x30) {
        return;
    }
    e->action = 3;
    e->subAction = 0;
    e->timer = 8;
    e->spriteSettings.b0 = 1;
    MessageRequest(0x194);
}

ARM void em2f_mesWait(Entity *e) {
    BindPlayers();
    UpdateAnimationSingleFrame(e);
    GufuFuyusnd(e);
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
    for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
        if (data_0212c584[i] & 0x1000) {
            return;
        }
    }
    e->action = 5;
    e->timer = 8;
    SoundReq(0x1f9);
    data_0212c5ac.unk_7 = 0x16;
    MakeFadeBuff256(0x100);
}

ARM void em2f_noOp(Entity *e) {
}

ARM void em2f_flash1(Entity *e) {
    GufuFuyusnd(e);
    BindPlayers();
    if (--e->timer != 0) {
        if (e->timer == 4) {
            MapLoad((u32 *)em2f_mapData, 1);
            em2f_mapFlag = 0;
        }
        return;
    }
    e->action = 6;
    e->timer = 0x3e;
    FadeSet(2, 8);
}

ARM void em2f_flashWait(Entity *e) {
    BindPlayers();
    UpdateAnimationSingleFrame(e);
    GufuFuyusnd(e);
    if (--e->timer == 0) {
        e->action = 7;
        e->timer = 0x1e;
    }
}

ARM void em2f_demoWait(Entity *e) {
    BindPlayers();
    UpdateAnimationSingleFrame(e);
    GufuFuyusnd(e);
    if (--e->timer != 0) {
        return;
    }
    Entity *child = GetTamaWork(0xa);
    if (child == NULL) {
        return;
    }
    child->parent = e;
    child->type = 1;
    e->child = child;
    e->action = 8;
}

ARM void em2f_taiden(Entity *e) {
    BindPlayers();
    UpdateAnimationSingleFrame(e);
    GufuFuyusnd(e);
    if (e->child->frame == 0) {
        return;
    }
    Entity *child = GetTamaWork(0xb);
    if (child == NULL) {
        return;
    }
    ObjPosCopy(e, child);
    child->type2 = 1;
    child->direction = 0x10;
    e->child = child;
    e->action = 9;
}

ARM void em2f_plDown(Entity *e) {
    BindPlayers();
    UpdateAnimationSingleFrame(e);
    GufuFuyusnd(e);
    if (e->child->z.HALF.HI < -2) {
        return;
    }
    e->action = 0xa;
    e->timer = 0x24;
    for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
        PlayerData *player = &data_0212ceb0[i];
        player->unk_0c = 0xf;
        player->unk_08 = 0x1af;
        player->unk_38 = 0xb4;
        player->unk_39 = 0;
        player->entity->direction = CalculateDirectionTo(0x1f8, 0x1c0, player->entity->x.HALF.HI, player->entity->y.HALF.HI);
        player->entity->animationState = player->entity->direction < 0x10 ? 2 : 6;
    }
}

ARM void em2f_downWait(Entity *e) {
    BindPlayers();
    UpdateAnimationSingleFrame(e);
    GufuFuyusnd(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 0xb;
    e->spriteSettings.b14 = 1;
    e->spriteSettings.b30 = 1;
    e->unk_5e.b0 = 3;
    for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
        data_0212ceb0[i].entity->direction = 0xff;
    }
}

ARM void em2f_demoMove(Entity *e) {
    BindPlayers();
    UpdateAnimationSingleFrame(e);
    GufuFuyusnd(e);
    e->z.WORD += 0x8000;
    if (e->z.HALF.HI == -4) {
        e->action = 0xc;
        e->timer = 0x1e;
        e->unk_2e = 0xc;
    }
}

ARM void em2f_demoEnd(Entity *e) {
    UpdateAnimationSingleFrame(e);
    GufuFuyusnd(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 0xd;
    e->speed = 0x100;
    e->timer = 1;
    e->spriteSettings.b14 = 2;
    e->spriteSettings.b30 = 2;
    e->unk_5e.b0 = 2;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        data_0212c648 = data_0212ceb0[localPlayerIndex].entity;
    } else {
        data_0212c648 = data_0212ceb0[*Knife_Single_SinglePlay_GetInstance()].entity;
    }
    for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
        PlayerData *player = &data_0212ceb0[i];
        player->unk_08 = 0xc;
        player->unk_38 = 1;
        player->unk_02 = 0x41;
        player->entity->zVelocity = 0x20000;
    }
    SoundReq(0x1af);
    data_0212c618 = 1;
    Scene_ClearFlag5();
    CockpitOn();
}

ARM void em2f_change(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((u16)(e->x.HALF.HI - 0x1f7) <= 2 && (u16)(e->y.HALF.HI - 0x19f) <= 2) {
        e->x.HALF.HI = 0x1f8;
        e->y.HALF.HI = 0x1a0;
        if (--e->timer != 0) {
            return;
        }
        nextSet(e);
        return;
    }
    e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, 0x1f8, 0x1a0);
    MoveDir(e);
    GufuFuyusnd(e);
}

ARM void em2f_tsubomiInit(Entity *e) {
    if (e->frame & 1) {
        if (setTsubomi(e) == 0) {
            return;
        }
        tsubomiCloseWaitSet(e);
        e->speed = em2f_tsubomiSpeeds[gufuVitalCheck(e)];
        UpdateAnimationSingleFrame(e);
        return;
    }
    UpdateAnimationSingleFrame(e);
}

ARM void em2f_tsubomiCloseWait(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (V(e)->subPhase != 0) {
        return;
    }
    V(e)->subPhase = 3;
    e->action = 0x10;
    e->timer = 0x3c;
}

ARM void em2f_tsubomiSuihei(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (V(e)->subPhase != 0xf) {
        return;
    }
    if (--e->timer != 0) {
        return;
    }
    V(e)->subPhase = 0;
    e->action = 0x11;
    e->speed = 0x100;
    getTsubomiMoveInfo(e);
    e->spriteSettings.b30 = 1;
    e->spriteSettings.b14 = e->spriteSettings.b30;
}

ARM void em2f_tsubomiCercle(Entity *e) {
    if (V(e)->subPhase == 0) {
        if (tblMove(e) == 0) {
            V(e)->subPhase = 7;
        }
    } else if (V(e)->subPhase == 4) {
        e->action = 0x12;
        e->timer = 0x14;
        e->spriteSettings.b30 = 2;
        e->spriteSettings.b14 = e->spriteSettings.b30;
    }
    UpdateAnimationSingleFrame(e);
}

ARM void em2f_tsubomiKamae(Entity *e) {
    if (--e->timer == 0) {
        e->action = 0x13;
        e->timer = 0x3c;
        V(e)->subPhase = 0;
    }
    UpdateAnimationSingleFrame(e);
}

ARM void em2f_tsubomiAttackInit(Entity *e) {
    if (V(e)->subPhase == 3 && --e->timer == 0) {
        V(e)->subPhase = flagBits[V(e)->tsubomiSlot + 2];
        e->action = 0x14;
    }
    UpdateAnimationSingleFrame(e);
}

ARM void em2f_tsubomiAttack(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (V(e)->subPhase == 0) {
        e->action = 0x15;
    }
}

ARM void em2f_tsubomiAttackEnd(Entity *e) {
    if (--e->subtimer != 0) {
        tsubomiCloseWaitSet(e);
        return;
    }
    e->action = 0x16;
    V(e)->subPhase = 0xff;
    InitAnimationForceUpdate(e, 4);
}

ARM void em2f_tsubomiEnd(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 0xd;
    e->timer = 0x3c;
    e->speed = 0x100;
    InitAnimationForceUpdate(e, 0);
}

ARM void em2f_stormInitWait(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 0x18;
    V(e)->subPhase = 0;
    V(e)->stormTimer = 0x20;
    InitAnimationForceUpdate(e, 3);
    EnqueueSFX(0xb2);
    e->spriteSettings.b30 = 1;
    e->spriteSettings.b14 = e->spriteSettings.b30;
}

ARM void em2f_stormGetTama(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 1) {
        stormGetTama(e);
        e->type2 = 0;
        return;
    }
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 0x19;
    e->timer = 0x3c;
    V(e)->attackCounter = 0;
    V(e)->stormDir = (Random() & 1) ? 1 : -1;
    InitAnimationForceUpdate(e, 0);
}

ARM void em2f_stormWait(Entity *e) {
    UpdateAnimationSingleFrame(e);
    stormMove(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 0x1a;
    getStormMoveInfo(e);
}

ARM void em2f_stormMove(Entity *e) {
    UpdateAnimationSingleFrame(e);
    stormMove(e);
    if (tblMove(e) != 0 && V(e)->subPhase == 0) {
        return;
    }
    e->action = 0x1b;
}

ARM void em2f_stormSmashInit(Entity *e) {
    UpdateAnimationSingleFrame(e);
    stormMove(e);
    if (V(e)->attackCounter == 0) {
        e->action = 0x1c;
        e->timer = 0x1e;
    }
}
