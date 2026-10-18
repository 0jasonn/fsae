#include "Unknown/Boss_02030a14.h"
#include "global.h"

ARM void func_02030a14(Entity *e) {
    s8 count = 0;
    Entity *a = CreateEnemy(3);
    if (a != NULL) {
        count++;
        a->iframes = 0xf0;
    }
    Entity *b = CreateEnemy(3);
    if (b != NULL) {
        b->x.HALF.HI -= 6;
        b->iframes = 0xf0;
        count++;
    }
    func_02045c20(e, a, b);
    if (count == 2) {
        a->parent = b;
        b->parent = a;
    }
    Entity *counter = V(e)->unk_60;
    if (counter != NULL) {
        VARS(Vars_Counter, counter)->unk_62 += count;
    }
    Entity *fx = CreateFx(0xf, 2, 0);
    if (fx != NULL) {
        fx->x.HALF.HI = e->x.HALF.HI - 4;
        fx->y.HALF.HI = e->y.HALF.HI;
        fx->unk_50 = e->unk_50;
    }
    DeleteEntity(e);
}

ARM void func_02030ae4(int index) {
    data_0212ceb0[index].unk_0c = 6;
    data_0212ceb0[index].unk_38 = 1;
    PlayerData *other = NULL;
    if (data_0212ceb0[index].unk_1e & 0x80) {
        other = V(data_0212ceb0[index].entity)->unk_64;
    } else if (data_0212ceb0[index].unk_1e & 0x20) {
        other = (PlayerData *)V(data_0212ceb0[index].entity)->unk_60;
    }
    if (other != NULL && other->unk_0c != 6 && other->entity->action != 6) {
        other->unk_0c = 6;
        other->unk_38 = 1;
    }
}

ARM void func_02030b70(Entity *e) {
    if (e->type2 & 0x80) {
        func_02031cb0(e);
        return;
    }
    if (e->type2 & 0x40) {
        data_020d0a7c[e->action](e);
        if (e->timer == 0) {
            return;
        }
        if (e->z.WORD != 0) {
            return;
        }
        if (!(e->contactFlags & 0x80)) {
            return;
        }
        if ((e->contactFlags & 0x7f) != 0x10) {
            return;
        }
        Entity *hitter = e->contactedEntity;
        data_0212ceb0[hitter->type].unk_0c = 6;
        data_0212ceb0[hitter->type].unk_38 = 1;
        e->iframes = 0xfe;
        if (hitter->animationState != 2) {
            return;
        }
        e->parent->x.WORD = e->x.WORD;
        e->parent->y.WORD = e->y.WORD;
        e->parent->z.WORD = 0;
        e->parent->unk_3c |= 0x80;
        e->parent->spriteSettings.b0 = 1;
        e->parent->speed = 0x200;
        e->parent->zVelocity = 0x18000;
        e->parent->direction = 8;
        InitAnimationForceUpdate(e->parent, 0xe);
        e->parent->action = 6;
        V(e->parent)->unk_74 = 0;
        V(e->parent)->unk_75 = 0x1e;
        func_02032b78(e->parent);
        SoundReq(0xa6);
        SoundReq(0xa3);
        DeleteEntity(e);
        return;
    }
    if (e->type >= 4) {
        if (e->health == 0) {
            func_02045ac0(e);
            e->type = 5;
            return;
        }
    } else {
        if (V(e)->unk_7c != 0) {
            V(e)->unk_7c--;
        }
        if (e->action != 8 && e->z.WORD == 0 && e->type != 0 && (e->contactFlags & 0x80) && (e->contactFlags & 0x7f) != 0) {
            if ((e->contactFlags & 0x7f) == 0x10) {
                Entity *hitter = e->contactedEntity;
                data_0212ceb0[hitter->type].unk_0c = 6;
                data_0212ceb0[hitter->type].unk_38 = 1;
                e->iframes = 0xfe;
                if (hitter->animationState == 2) {
                    e->spriteSettings.b0 = 1;
                    e->speed = 0x200;
                    e->zVelocity = 0x18000;
                    e->direction = 8;
                    InitAnimationForceUpdate(e, (e->type - 1) * 10 + 4);
                    if (V(e)->unk_75 != 0) {
                        V(e)->unk_74++;
                    } else {
                        V(e)->unk_74 = 0;
                    }
                    V(e)->unk_75 = 0x1e;
                    func_02032b78(e);
                    e->action = 6;
                    SoundReq(0xa6);
                }
                if (e->type == 3 && e->action != 2 && e->action != 6 && e->action != 7) {
                    SoundReq(0xa3);
                }
            } else {
                e->iframes = 0xd8;
                InitAnimationForceUpdate(e, (e->type - 1) * 10 + 5);
                V(e)->unk_72 = e->action;
                e->action = 5;
            }
        }
    }
    data_020d0dc0[e->action](e);
}

ARM void func_02030e90(Entity *e) {
    Entity *child = CreateFx(0x65, 0, 0);
    if (child != NULL) {
        child->parent = e;
    }
    e->spriteSettings.b16++;
    e->spriteSettings.b20 = e->spriteSettings.b16;
    e->action = 1;
    e->spriteSettings.b0 = 1;
    InitAnimationForceUpdate(e, 6);
    e->timer = data_0212c7c8.unk_0 * 3;
    e->subtimer = 0xb4;
    V(e)->unk_7c = 0x2a30;
    e->speed = 0x300;
    e->unk_2e = 8;
    e->spriteSettings.b4 = 3;
    e->unk_5e.b2 = 2;
    e->hitbox = data_020d0a62;
    e->unk_6a = 1;
    e->unk_3f = 0x48;
    e->child = data_0212c648;
    data_0212c648 = e;
    func_020266f8();
}

ARM void func_02030f8c(Entity *e) {
    if (e->subtimer != 0) {
        if (e->subtimer == 0x3c) {
            data_0212c648 = e->child;
        } else if (e->subtimer == 0x1e) {
            func_02026720();
        }
        func_020547ec();
        e->subtimer--;
    }
    if (!(e->contactFlags & 0x80)) {
        return;
    }
    switch (e->contactFlags & 0x7f) {
        case 0x10:
            func_02030ae4(e->contactedEntity->type);
        case 4:
        case 8:
        case 0xc:
            break;
        default:
            return;
    }
    e->iframes = 0xe8;
    if (--e->timer == 0) {
        e->spriteSettings.b16 = e->spriteSettings.b20 - 1;
        e->spriteSettings.b20 = e->spriteSettings.b16;
        func_02032ac4(e);
    }
    func_02032e5c(e);
}

ARM void func_02031084(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 0) {
        return;
    }
    if (e->frame & 0x40) {
        SoundReq(0xa8);
    }
    ProcessMovement(e);
    s16 dx = e->x.HALF.HI - 0x1f8;
    s16 dy = e->y.HALF.HI - 0x1f8;
    if (dx <= 3 && dx >= -3) {
        e->x.HALF.HI = 0x1f8;
        e->subtimer |= 1;
    }
    if (dy <= 3 && dy >= -3) {
        e->y.HALF.HI = 0x1f8;
        e->subtimer |= 2;
    }
    if (e->subtimer == 3) {
        if (e->timer != 0) {
            e->timer--;
            e->direction = 0xff;
            e->zVelocity = 0;
            return;
        }
        if (UpdateGravity(e, 0x2000) != 0) {
            return;
        }
        e->action++;
        if (e->type != 0) {
            CreateFx(0x61, 0, 0);
        } else {
            e->type = 1;
            func_02032b48(e);
            SoundReq(0x19c);
        }
        InitAnimationForceUpdate(e, (e->type - 1) * 10 + 8);
        func_020329c8(e);
        func_0205747c(0x10, 3);
        return;
    }
    e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, 0x1f8, 0x1f8);
    if (e->zVelocity == 0) {
        return;
    }
    UpdateGravity(e, 0x1000);
}
