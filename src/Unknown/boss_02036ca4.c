#include "Unknown/Boss_02036ca4.h"
#include "global.h"

ARM void func_02036ca4(Entity *e) {
    if (e->health == 0 && e->action < 0x23) {
        e->action = 0x23;
    }
    data_020d177c[e->action](e);
}

ARM void func_02036cdc(Entity *e) {
    e->action = 1;
    e->timer = 0xb4;
    e->x.HALF.HI = 0x1f8;
    e->y.HALF.HI = 0x188;
    e->z.HALF.HI = -0x70;
    e->spriteSettings.b4 = 2;
    e->unk_5e.b2 = 2;
    e->hitbox = data_020d1438;
    V(e)->unk_7c = Random();
    e->health = data_020d1428[data_0212c7c8.unk_3];
    if (func_0208de54(func_0208da4c()) != 0) {
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
    func_020547ec();
    SoundReq(0x80080000);
    data_0212c7c8.unk_26 = 0xffff;
}

ARM void func_02036df4(Entity *e) {
    func_020547ec();
    u8 timer = --e->timer;
    if (timer == 0) {
        e->action = 2;
        e->timer = 0x78;
        e->spriteSettings.b0 = 1;
        data_0212c648 = e;
        for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
            data_0212ceb0[i].entity->animationState = 0;
            func_02076988(data_0212ceb0[i].entity, -8, -12);
        }
        return;
    }
    if (e->subtimer < 0x20) {
        e->subtimer++;
        data_0212c5ac.unk_c = 0xfff0;
        data_0212c5ac.unk_7 = 0;
        func_020463f0((e->subtimer >> 2) << 4);
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

ARM void func_02036f54(Entity *e) {
    func_020547ec();
    UpdateAnimationSingleFrame(e);
    func_02060a70(e);
    e->z.WORD += 0x8000;
    if (e->z.HALF.HI != -0x30) {
        return;
    }
    e->action = 3;
    e->subAction = 0;
    e->timer = 8;
    e->spriteSettings.b0 = 1;
    func_02049f0c(0x194);
}

ARM void func_02036fbc(Entity *e) {
    func_020547ec();
    UpdateAnimationSingleFrame(e);
    func_02060a70(e);
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    if (e->subAction == 0) {
        if ((data_0217d384 & 0x7f) != 6) {
            return;
        }
        func_02049eb8();
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
    func_020463f0(0x100);
}

ARM void func_02037094(Entity *e) {
}

ARM void func_02037098(Entity *e) {
    func_02060a70(e);
    func_020547ec();
    if (--e->timer != 0) {
        if (e->timer == 4) {
            func_02021ec4(data_020d70c8, 1);
            data_02134914 = 0;
        }
        return;
    }
    e->action = 6;
    e->timer = 0x3e;
    func_0204625c(2, 8);
}

ARM void func_02037108(Entity *e) {
    func_020547ec();
    UpdateAnimationSingleFrame(e);
    func_02060a70(e);
    if (--e->timer == 0) {
        e->action = 7;
        e->timer = 0x1e;
    }
}

ARM void func_02037148(Entity *e) {
    func_020547ec();
    UpdateAnimationSingleFrame(e);
    func_02060a70(e);
    if (--e->timer != 0) {
        return;
    }
    Entity *child = CreateProjectile(0xa);
    if (child == NULL) {
        return;
    }
    child->parent = e;
    child->type = 1;
    e->child = child;
    e->action = 8;
}

ARM void func_020371a4(Entity *e) {
    func_020547ec();
    UpdateAnimationSingleFrame(e);
    func_02060a70(e);
    if (e->child->frame == 0) {
        return;
    }
    Entity *child = CreateProjectile(0xb);
    if (child == NULL) {
        return;
    }
    CopyPosition(e, child);
    child->type2 = 1;
    child->direction = 0x10;
    e->child = child;
    e->action = 9;
}

ARM void func_0203720c(Entity *e) {
    func_020547ec();
    UpdateAnimationSingleFrame(e);
    func_02060a70(e);
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

ARM void func_020372e4(Entity *e) {
    func_020547ec();
    UpdateAnimationSingleFrame(e);
    func_02060a70(e);
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

ARM void func_02037390(Entity *e) {
    func_020547ec();
    UpdateAnimationSingleFrame(e);
    func_02060a70(e);
    e->z.WORD += 0x8000;
    if (e->z.HALF.HI == -4) {
        e->action = 0xc;
        e->timer = 0x1e;
        e->unk_2e = 0xc;
    }
}

ARM void func_020373d8(Entity *e) {
    UpdateAnimationSingleFrame(e);
    func_02060a70(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 0xd;
    e->speed = 0x100;
    e->timer = 1;
    e->spriteSettings.b14 = 2;
    e->spriteSettings.b30 = 2;
    e->unk_5e.b0 = 2;
    if (func_0208de54(func_0208da4c()) != 0) {
        data_0212c648 = data_0212ceb0[data_0212c504].entity;
    } else {
        data_0212c648 = data_0212ceb0[*func_02093b5c()].entity;
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
    func_0205396c();
    func_02026720();
}

ARM void func_02037528(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((u16)(e->x.HALF.HI - 0x1f7) <= 2 && (u16)(e->y.HALF.HI - 0x19f) <= 2) {
        e->x.HALF.HI = 0x1f8;
        e->y.HALF.HI = 0x1a0;
        if (--e->timer != 0) {
            return;
        }
        func_02037f6c(e);
        return;
    }
    e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, 0x1f8, 0x1a0);
    ProcessMovement(e);
    func_02060a70(e);
}

ARM void func_020375c8(Entity *e) {
    if (e->frame & 1) {
        if (func_0203808c(e) == 0) {
            return;
        }
        func_02038138(e);
        e->speed = data_020d142c[func_020384b8(e)];
        UpdateAnimationSingleFrame(e);
        return;
    }
    UpdateAnimationSingleFrame(e);
}

ARM void func_02037620(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (V(e)->unk_70 != 0) {
        return;
    }
    V(e)->unk_70 = 3;
    e->action = 0x10;
    e->timer = 0x3c;
}

ARM void func_02037654(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (V(e)->unk_70 != 0xf) {
        return;
    }
    if (--e->timer != 0) {
        return;
    }
    V(e)->unk_70 = 0;
    e->action = 0x11;
    e->speed = 0x100;
    func_02038194(e);
    e->spriteSettings.b30 = 1;
    e->spriteSettings.b14 = e->spriteSettings.b30;
}

ARM void func_020376c4(Entity *e) {
    if (V(e)->unk_70 == 0) {
        if (func_020381ec(e) == 0) {
            V(e)->unk_70 = 7;
        }
    } else if (V(e)->unk_70 == 4) {
        e->action = 0x12;
        e->timer = 0x14;
        e->spriteSettings.b30 = 2;
        e->spriteSettings.b14 = e->spriteSettings.b30;
    }
    UpdateAnimationSingleFrame(e);
}

ARM void func_02037730(Entity *e) {
    if (--e->timer == 0) {
        e->action = 0x13;
        e->timer = 0x3c;
        V(e)->unk_70 = 0;
    }
    UpdateAnimationSingleFrame(e);
}

ARM void func_02037768(Entity *e) {
    if (V(e)->unk_70 == 3 && --e->timer == 0) {
        V(e)->unk_70 = data_020cf9b8[V(e)->unk_71 + 2];
        e->action = 0x14;
    }
    UpdateAnimationSingleFrame(e);
}

ARM void func_020377b4(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (V(e)->unk_70 == 0) {
        e->action = 0x15;
    }
}

ARM void func_020377d4(Entity *e) {
    if (--e->subtimer != 0) {
        func_02038138(e);
        return;
    }
    e->action = 0x16;
    V(e)->unk_70 = 0xff;
    InitAnimationForceUpdate(e, 4);
}

ARM void func_02037810(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 0xd;
    e->timer = 0x3c;
    e->speed = 0x100;
    InitAnimationForceUpdate(e, 0);
}

ARM void func_02037850(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 0x18;
    V(e)->unk_70 = 0;
    V(e)->unk_72 = 0x20;
    InitAnimationForceUpdate(e, 3);
    EnqueueSFX(0xb2);
    e->spriteSettings.b30 = 1;
    e->spriteSettings.b14 = e->spriteSettings.b30;
}

ARM void func_020378c0(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 1) {
        func_020382fc(e);
        e->type2 = 0;
        return;
    }
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 0x19;
    e->timer = 0x3c;
    V(e)->unk_6e = 0;
    V(e)->unk_7d = (Random() & 1) ? 1 : -1;
    InitAnimationForceUpdate(e, 0);
}

ARM void func_02037930(Entity *e) {
    UpdateAnimationSingleFrame(e);
    func_02038414(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 0x1a;
    func_020383bc(e);
}

ARM void func_0203796c(Entity *e) {
    UpdateAnimationSingleFrame(e);
    func_02038414(e);
    if (func_020381ec(e) != 0 && V(e)->unk_70 == 0) {
        return;
    }
    e->action = 0x1b;
}

ARM void func_020379a8(Entity *e) {
    UpdateAnimationSingleFrame(e);
    func_02038414(e);
    if (V(e)->unk_6e == 0) {
        e->action = 0x1c;
        e->timer = 0x1e;
    }
}
