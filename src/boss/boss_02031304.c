#include "boss/boss_02030a14.h"
#include "global.h"

ARM void em2a_move(Entity *e) {
    flashcheck(e);
    if (e->type == 2 && V(e)->unk_79 != 0xf) {
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (e->frame == 0) {
        MoveDir(e);
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
            jumpefectSet(e);
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
    if ((e->timer = move3search(e)) == 0xff) {
        bigjumpinit(e);
        return;
    }
    e->subtimer = data_020d0a42[Random() & 7];
    move3Init(e);
}

ARM void em2a_move3(Entity *e) {
    flashcheck(e);
    if (e->type == 2 && V(e)->unk_79 != 0xf) {
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (V(e)->unk_70 != 0) {
        V(e)->unk_70--;
    }
    if (e->frame == 0) {
        MoveDir(e);
        if (UpdateGravity(e, 0x2000) == 0) {
            e->unk_28 = 1;
            jumpefectSet(e);
        } else if (e->zVelocity == 0) {
            e->unk_28 = 1;
        }
    } else if (e->frame & 0x80) {
        if (V(e)->unk_70 != 0) {
            if (e->type == 2) {
                V(e)->unk_79 = 0;
            }
            move3Init(e);
        } else if (--e->subtimer != 0) {
            e->action = 0xd;
            V(e)->unk_70 = 0xb4;
            InitAnimationForceUpdate(e, (e->type - 1) * 10);
        } else {
            bigjumpinit(e);
        }
    }
    em2a_areaCheck(e);
}

ARM void em2a_move3wait(Entity *e) {
    flashcheck(e);
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
    if ((e->timer = move3search(e)) == 0xff) {
        bigjumpinit(e);
        return;
    }
    if (e->type == 2) {
        V(e)->unk_79 = 0;
    }
    move3Init(e);
}

ARM void em2a_boyon(Entity *e) {
    flashcheck(e);
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->action = V(e)->unk_72;
    }
}

ARM void em2a_buttobi(Entity *e) {
    UpdateAnimationSingleFrame(e);
    MoveDir(e);
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
    jumpefectSet(e);
}

ARM void em2a_buttobiwait(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (V(e)->unk_75 != 0) {
        V(e)->unk_75--;
    }
    if (e->subtimer-- != 0) {
        return;
    }
    bigjumpinit(e);
}

ARM void em2a_ice(Entity *e) {
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
                efectset(e);
                SoundReq(0x2d);
                break;
        }
        e->contactFlags = 0;
        if (e->health == 0) {
            e->type++;
            PutVGroup(e);
            if (data_0212c7c8.unk_6 + 1 == e->type) {
                e->type = 4;
            }
            lifeset(e);
            if (e->type < 4) {
                if (e->type == 2) {
                    PutObjColor(0x13);
                    GetVGroup(e, 8);
                    e->spriteSettings.b20 = GetObjColor(0x15);
                    e->spriteSettings.b16 = e->spriteSettings.b20;
                    e->spriteSettings.b4 = 2;
                    e->hitbox = data_020d0a72;
                } else {
                    PutObjColor(0x15);
                    GetVGroup(e, 9);
                    e->spriteSettings.b20 = GetObjColor(0x16);
                    e->spriteSettings.b16 = e->spriteSettings.b20;
                    e->spriteSettings.b4 = 0;
                    e->hitbox = data_020d0a52;
                }
                bigjumpinit(e);
                return;
            }
            PutObjColor(0x16);
            GetVGroup(e, 7);
            e->spriteSettings.b20 = GetObjColor(0x17);
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
    bigjumpinit(e);
}

ARM void em2a_coreapperwait(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->action = 9;
    InitAnimationForceUpdate(e, 0x1e);
    coreSet(e);
    coreSync(e);
}

ARM void em2a_coreapper(Entity *e) {
    e->spriteSettings.b0 = 1;
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->speed = 0x200;
        e->action = 0x10;
        e->timer = 0x20;
        e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, 0x1f8, 0x1f8);
        e->hitbox = data_020d0a4a;
    }
    coreSync(e);
}

ARM void em2a_coredemomove(Entity *e) {
    UpdateAnimationSingleFrame(e);
    MoveDir(e);
    if (e->timer != 0) {
        e->timer--;
    } else {
        e->action = 0xa;
        e->timer = 0;
    }
    coreSync(e);
}

ARM void em2a_corewait(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    e->action = 0xb;
    e->timer = 0xf0;
    InitAnimationForceUpdate(e, 0x1f);
    nearplcheck(e);
}

ARM void em2a_coremove(Entity *e) {
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
    coreSync(e);
}

ARM void em2a_biribiri(Entity *e) {
    if (e->timer-- == 0) {
        e->action = 0xa;
        e->timer = 0xf0;
        InitAnimationForceUpdate(e, 0x20);
    }
    if (e->unk_23 != 0x20) {
        InitAnimationForceUpdate(e, 0x20);
    }
    coreSync(e);
}
