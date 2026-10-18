#include "boss/boss_02030a14.h"
#include "global.h"

ARM void func_02031304(Entity *e) {
    func_02032e04(e);
    if (e->type == 2 && V(e)->unk_79 != 0xf) {
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (e->frame == 0) {
        ProcessMovement(e);
        if (UpdateGravity(e, 0x2000) == 0) {
            e->unk_28 = 1;
            e->timer--;
            e->subtimer--;
            if (e->timer == 0) {
                if (e->type2) {
                    e->direction = (e->direction - 8) & 0x1f;
                } else {
                    e->direction = (e->direction + 8) & 0x1f;
                }
            }
            func_020329c8(e);
            return;
        }
        if (e->zVelocity == 0) {
            e->unk_28 = 1;
        }
        return;
    }
    if (!(e->frame & 0x80)) {
        return;
    }
    if (e->type == 2) {
        V(e)->unk_79 = 0;
    }
    if (e->subtimer != 0) {
        if (e->timer == 0) {
            if (V(e)->unk_73) {
                V(e)->unk_73 = 0;
                e->timer = 1;
            } else {
                e->timer = 2;
            }
        }
        e->zVelocity = 0x30000;
        InitAnimationForceUpdate(e, (e->type - 1) * 10 + 1);
        return;
    }
    e->action = 0xc;
    e->timer = 0xff;
    if ((e->timer = func_02032d34(e)) == 0xff) {
        func_02032ac4(e);
        return;
    }
    e->subtimer = data_020d0a42[Random() & 7];
    func_02032c2c(e);
}

ARM void func_02031498(Entity *e) {
    func_02032e04(e);
    if (e->type == 2 && V(e)->unk_79 != 0xf) {
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (V(e)->unk_70 != 0) {
        V(e)->unk_70--;
    }
    if (e->frame == 0) {
        ProcessMovement(e);
        if (UpdateGravity(e, 0x2000) == 0) {
            e->unk_28 = 1;
            func_020329c8(e);
        } else if (e->zVelocity == 0) {
            e->unk_28 = 1;
        }
    } else if (e->frame & 0x80) {
        if (V(e)->unk_70 != 0) {
            if (e->type == 2) {
                V(e)->unk_79 = 0;
            }
            func_02032c2c(e);
        } else if (--e->subtimer != 0) {
            e->action = 0xd;
            V(e)->unk_70 = 0xb4;
            InitAnimationForceUpdate(e, (e->type - 1) * 10);
        } else {
            func_02032ac4(e);
        }
    }
    func_02032cac(e);
}

ARM void func_020315ac(Entity *e) {
    func_02032e04(e);
    if (V(e)->unk_70 != 0) {
        if (e->unk_23 != 0) {
            InitAnimationForceUpdate(e, (e->type - 1) * 10);
        } else {
            UpdateAnimationSingleFrame(e);
        }
        V(e)->unk_70--;
        return;
    }
    e->action = 0xc;
    if ((e->timer = func_02032d34(e)) == 0xff) {
        func_02032ac4(e);
        return;
    }
    if (e->type == 2) {
        V(e)->unk_79 = 0;
    }
    func_02032c2c(e);
}

ARM void func_02031650(Entity *e) {
    func_02032e04(e);
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->action = V(e)->unk_72;
    }
}

ARM void func_02031678(Entity *e) {
    UpdateAnimationSingleFrame(e);
    ProcessMovement(e);
    if (e->x.HALF.HI <= 0x184) {
        e->x.HALF.HI = 0x184;
    }
    if (e->y.HALF.HI >= 0x24b) {
        e->y.HALF.HI = 0x24b;
    }
    if (e->y.HALF.HI <= 0x1a3) {
        e->y.HALF.HI = 0x1a3;
    }
    if (e->x.HALF.HI > 0x2a8) {
        e->iframes = 0xe0;
        e->unk_3f = 0x48;
        e->x.HALF.HI = 0x2a8;
        InitAnimationForceUpdate(e, (e->type - 1) * 10 + 6);
        e->action = 8;
        e->zVelocity = 0;
        e->spriteSettings.b16 = e->spriteSettings.b20 + 1;
        e->spriteSettings.b20 = e->spriteSettings.b16;
        V(e)->unk_70 = 0x168;
        SoundReq(0xa9);
        return;
    }
    if (UpdateGravity(e, 0x2000) != 0) {
        return;
    }
    InitAnimationForceUpdate(e, (e->type - 1) * 10 + 9);
    e->subtimer = 0x5a;
    e->action = 7;
    func_020329c8(e);
}

ARM void func_020317b0(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (V(e)->unk_75 != 0) {
        V(e)->unk_75--;
    }
    if (e->subtimer-- != 0) {
        return;
    }
    func_02032ac4(e);
}

ARM void func_020317ec(Entity *e) {
    UpdateGravity(e, 0x2000);
    if (e->contactFlags & 0x80) {
        switch (e->contactFlags & 0x7f) {
            case 0x10:
                func_02030ae4(e->contactedEntity->type);
            case 4:
            case 8:
            case 0xc:
            case 0x18:
                e->health--;
                e->iframes = 0xd0;
                func_02032e5c(e);
                SoundReq(0x2d);
                break;
        }
        e->contactFlags = 0;
        if (e->health == 0) {
            e->type++;
            func_02081160(e);
            if (data_0212c7c8.unk_6 + 1 == e->type) {
                e->type = 4;
            }
            func_02032b48(e);
            if (e->type < 4) {
                if (e->type == 2) {
                    func_02027fe8(0x13);
                    func_02081088(e, 8);
                    e->spriteSettings.b20 = func_02027ec4(0x15);
                    e->spriteSettings.b16 = e->spriteSettings.b20;
                    e->spriteSettings.b4 = 2;
                    e->hitbox = data_020d0a72;
                } else {
                    func_02027fe8(0x15);
                    func_02081088(e, 9);
                    e->spriteSettings.b20 = func_02027ec4(0x16);
                    e->spriteSettings.b16 = e->spriteSettings.b20;
                    e->spriteSettings.b4 = 0;
                    e->hitbox = data_020d0a52;
                }
                func_02032ac4(e);
                return;
            }
            func_02027fe8(0x16);
            func_02081088(e, 7);
            e->spriteSettings.b20 = func_02027ec4(0x17);
            e->spriteSettings.b16 = e->spriteSettings.b20;
            e->action = 0xf;
            e->unk_3c &= 0x7f;
            e->spriteSettings.b0 = 0;
            e->z.WORD = 0;
            return;
        }
    }
    V(e)->unk_70--;
    if (V(e)->unk_70 != 0) {
        return;
    }
    e->spriteSettings.b16 = e->spriteSettings.b20 - 1;
    e->spriteSettings.b20 = e->spriteSettings.b16;
    func_02032ac4(e);
}

ARM void func_02031a58(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->action = 9;
    InitAnimationForceUpdate(e, 0x1e);
    func_0203263c(e);
    func_020325f8(e);
}

ARM void func_02031a94(Entity *e) {
    e->spriteSettings.b0 = 1;
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->speed = 0x200;
        e->action = 0x10;
        e->timer = 0x20;
        e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, 0x1f8, 0x1f8);
        e->hitbox = data_020d0a4a;
    }
    func_020325f8(e);
}

ARM void func_02031b04(Entity *e) {
    UpdateAnimationSingleFrame(e);
    ProcessMovement(e);
    if (e->timer != 0) {
        e->timer--;
    } else {
        e->action = 0xa;
        e->timer = 0;
    }
    func_020325f8(e);
}

ARM void func_02031b40(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    e->action = 0xb;
    e->timer = 0xf0;
    InitAnimationForceUpdate(e, 0x1f);
    func_0203298c(e);
}

ARM void func_02031b80(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->timer != 0) {
        e->timer--;
        func_020852ec(e);
        if (e->unk_2c & data_020d0a5a[e->direction >> 3]) {
            u8 target = func_02086078(data_0212ceb0[e->subtimer].entity, e);
            if (e->direction != target) {
                e->direction ^= 0x10;
            } else {
                e->direction = (e->direction + 8) & 0x1f;
                if (e->unk_2c & data_020d0a5a[e->direction >> 3]) {
                    e->direction = (e->direction - 0x10) & 0x1f;
                }
            }
        }
    } else {
        e->action = 0xa;
        e->timer = 0xf0;
        InitAnimationForceUpdate(e, 0x20);
    }
    func_020325f8(e);
}

ARM void func_02031c58(Entity *e) {
    if (e->timer-- == 0) {
        e->action = 0xa;
        e->timer = 0xf0;
        InitAnimationForceUpdate(e, 0x20);
    }
    if (e->unk_23 != 0x20) {
        InitAnimationForceUpdate(e, 0x20);
    }
    func_020325f8(e);
}
