#include "Unknown/Boss_02036ca4.h"
#include "global.h"

ARM void func_02037a6c(Entity *e) {
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

ARM void func_02037af8(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer == 0) {
        e->action = 0x1f;
        e->speed = 0x100;
    }
}

ARM void func_02037b28(Entity *e) {
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
        func_02076a50(e, 1, 1, 0x14);
    }
    ProcessMovement(e);
    func_02060a70(e);
}

ARM void func_02037bd8(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 0x21;
    e->timer = 0xd2;
    V(e)->unk_6e = data_020d1440[Random() & 7];
}

ARM void func_02037c24(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer == 0) {
        if (V(e)->unk_6e != 0) {
            V(e)->unk_6e--;
            e->timer = 0xf0;
            return;
        }
        e->action = 0x22;
        func_02038460(e);
        return;
    }
    if (e->timer != 0x78) {
        return;
    }
    if (V(e)->unk_6e == 0) {
        Entity *child = CreateProjectile(0xa);
        if (child != NULL) {
            child->type2 = 1;
            child->parent = e;
        }
    } else {
        Entity *child = CreateProjectile(0xa);
        if (child != NULL) {
            child->parent = e;
        }
    }
}

ARM void func_02037cb4(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    if ((data_0212c5bc & 7) == 0) {
        func_02076a50(e, 1, 1, 0x14);
    }
    int result = func_020381ec(e);
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

ARM void func_02037d68(Entity *e) {
    if (e->unk_3c != 0) {
        e->unk_3c = 0;
        e->timer = 0xb4;
        func_02053958();
        func_020266f8();
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
        if (player->unk_28->health == 0) {
            return;
        }
    }
    for (u32 i = 0; i < data_0212c7c8.unk_0; i++) {
        PlayerData *player = &data_0212ceb0[i];
        player->unk_28->z.HALF.HI = 0;
        player->unk_28->zVelocity = 0;
        player->unk_28->direction = 0xff;
        player->unk_28->iframes = 0x88;
        player->unk_36 &= 0xf3ff;
        func_020899e4(player->unk_28);
    }
    e->action = 0x24;
    e->timer = 0x20;
    InitAnimationForceUpdate(e, 0);
    func_0204625c(3, 0x10);
    func_02049eb8();
    func_020384f8();
}

ARM void func_02037ed8(Entity *e) {
    UpdateAnimationSingleFrame(e);
    e->spriteSettings.b0 ^= 1;
    func_020384f8();
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    Entity *child = CreateFx(0x69, 0, 0);
    if (child == NULL) {
        return;
    }
    child->parent = e;
    e->action = 0x25;
    e->spriteSettings.b0 = 1;
}

ARM void func_02037f54(Entity *e) {
    func_020547ec();
    UpdateAnimationSingleFrame(e);
}
