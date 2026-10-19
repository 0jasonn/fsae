#include "enemy/em2f.h"
#include "global.h"

ARM void em2f_stormSmashEnd(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    if (--e->subtimer != 0) {
        e->action = 0x17;
        e->timer = 0x3c;
    } else {
        e->action = 0xd;
        e->timer = 0x3c;
        e->speed = 0x100;
        InitAnimationForceUpdate(e, 0);
    }
    e->spriteSettings.b30 = 2;
    e->spriteSettings.b14 = e->spriteSettings.b30;
}

ARM void em2f_fiveInitWait(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer == 0) {
        e->action = 0x1f;
        e->speed = 0x100;
    }
}

ARM void em2f_fiveAttackMove(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((u16)(e->x.HALF.HI - 0x1f7) <= 2 && (u16)(e->y.HALF.HI - 0x1f7) <= 2) {
        e->action = 0x20;
        e->timer = 0x3c;
        e->x.HALF.HI = 0x1f8;
        e->y.HALF.HI = 0x1f8;
        return;
    }
    e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, 0x1f8, 0x1f8);
    if ((data_0212c5bc & 7) == 0) {
        SetDisp(e, 1, 1, 0x14);
    }
    MoveDir(e);
    GufuFuyusnd(e);
}

ARM void em2f_fiveAttackWait(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 0x21;
    e->timer = 0xd2;
    V(e)->unk_6e = data_020d1440[Random() & 7];
}

ARM void em2f_fiveAttack(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer == 0) {
        if (V(e)->unk_6e != 0) {
            V(e)->unk_6e--;
            e->timer = 0xf0;
            return;
        }
        e->action = 0x22;
        getFiveMoveInfo(e);
        return;
    }
    if (e->timer != 0x78) {
        return;
    }
    if (V(e)->unk_6e == 0) {
        Entity *child = GetTamaWork(0xa);
        if (child != NULL) {
            child->type2 = 1;
            child->parent = e;
        }
    } else {
        Entity *child = GetTamaWork(0xa);
        if (child != NULL) {
            child->parent = e;
        }
    }
}

ARM void em2f_fiveMove(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    if ((data_0212c5bc & 7) == 0) {
        SetDisp(e, 1, 1, 0x14);
    }
    int result = tblMove(e);
    if (result == 0) {
        if (--e->subtimer != 0) {
            e->action = 0x20;
            e->timer = 0x3c;
            return;
        }
        e->action = 0xd;
        e->timer = 0x3c;
        e->speed = 0x100;
        InitAnimationForceUpdate(e, 0);
        return;
    }
    if (result == 2) {
        e->timer = 0x1e;
    }
}

ARM void em2f_die(Entity *e) {
    if (e->unk_3c != 0) {
        e->unk_3c = 0;
        e->timer = 0xb4;
        Scene_SetFlag5();
        CockpitOff();
        SoundReq(0x80010000);
        SoundReq(0x2e);
    }
    e->spriteSettings.b0 ^= 1;
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    u8 count = data_0212c7c8.unk_0;
    for (u32 i = 0; i < count; i++) {
        PlayerData *player = &data_0212ceb0[i];
        if ((player->unk_36 & 1) || player->unk_3c != 0) {
            return;
        }
        if (player->entity->health == 0) {
            return;
        }
    }
    for (u32 i = 0; i < data_0212c7c8.unk_0; i++) {
        PlayerData *player = &data_0212ceb0[i];
        player->entity->z.HALF.HI = 0;
        player->entity->zVelocity = 0;
        player->entity->direction = 0xff;
        player->entity->iframes = 0x88;
        player->unk_36 &= 0xf3ff;
        func_020899e4(player->entity);
    }
    e->action = 0x24;
    e->timer = 0x20;
    InitAnimationForceUpdate(e, 0);
    FadeSet(3, 0x10);
    Status_ArmIfEnabled();
    gufuBindPls();
}

ARM void em2f_dieWait(Entity *e) {
    UpdateAnimationSingleFrame(e);
    e->spriteSettings.b0 ^= 1;
    gufuBindPls();
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    Entity *child = GetSetWork(0x69, 0, 0);
    if (child == NULL) {
        return;
    }
    child->parent = e;
    e->action = 0x25;
    e->spriteSettings.b0 = 1;
}

ARM void em2f_dieDemo(Entity *e) {
    BindPlayers();
    UpdateAnimationSingleFrame(e);
}
