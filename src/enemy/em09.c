#include "enemy/em09.h"
#include "global.h"

// Function names (dsd -> name), also in scratch/agentA/renames.txt:
// tenka tenka, searchCandle searchCandle, purupuru purupuru,
// piyoriSet piyoriSet, Em09 Em09, em09_normal em09_normal,
// em09_damage em09_damage, Boss_Release Boss_Release (tail-calls func_02084788),
// type2Move type2Move, em09_init em09_init, em09_wait em09_wait,
// em09_appear em09_appear, em09_move em09_move

ARM void tenka(Entity *e) {
    e->action = 4;
    e->iframes = 0xfc;
    VBD(e)->dying = 1;
    e->unk_3f = 0x11;
    e->zVelocity = 0x20000;
    e->unk_5c = 0x21ff;
    VBD(e)->dyingTimer = 0xf0;
    em08_seqSet(e, 2);
    EnqueueSFX(0x2a);
}

ARM void searchCandle(Entity *e) {
    int a;
    int b;
    if (VBD(e)->dying != 0) {
        return;
    }
    if (e->unk_2c & 0xe) {
        a = func_02083c74(e, 2, -6);
        b = func_02083c74(e, -2, -6);
        if (a == 0x10e || b == 0x10e) {
            tenka(e);
            return;
        }
    } else if (e->unk_2c & 0xe0) {
        a = func_02083c74(e, 2, 6);
        b = func_02083c74(e, -2, 6);
        if (a == 0x10e || b == 0x10e) {
            tenka(e);
            return;
        }
    }
    if (e->unk_2c & 0xe000) {
        a = func_02083c74(e, 8, 2);
        b = func_02083c74(e, 8, -2);
        if (a == 0x10e || b == 0x10e) {
            tenka(e);
        }
        return;
    }
    if (e->unk_2c & 0xe00) {
        a = func_02083c74(e, -8, 2);
        b = func_02083c74(e, -8, -2);
        if (a == 0x10e || b == 0x10e) {
            tenka(e);
        }
    }
}

ARM int purupuru(Entity *e) {
    VBL(e)->launchTimer--;
    if (VBL(e)->launchTimer == 0) {
        if (e->action == 2 && data_0212ceb0[e->type2].unk_02 != 0) {
            VBL(e)->launchTimer = 4;
        } else {
            e->action = 1;
            e->timer = 1;
            e->unk_1a = 0;
            e->iframes = 0xfc;
            e->unk_46 = 0xc;
            e->unk_3f = 0x10;
            e->unk_5c = 0x31ff;
            em08_seqSet(e, 0);
            e->unk_2e = 2;
            return 0;
        }
    } else {
        if (VBL(e)->launchTimer == 0x3c) {
            e->unk_1a = 2;
        }
        if (VBL(e)->launchTimer < 0x3c && (VBL(e)->launchTimer & 1) != 0) {
            e->x.HALF.HI += data_020d1cbc[(VBL(e)->launchTimer & 6) >> 1];
        }
    }
    return 1;
}

ARM void piyoriSet(Entity *e) {
    e->action = 3;
    e->unk_46 = 3;
    e->unk_3f = 0x47;
    e->unk_5c = 0x31ff;
    em08_seqSet(e, 4);
    e->unk_2e = 2;
}

ARM void Em09(Entity *e) {
    Entity *target;
    u8 index;
    if (e->type2 == 0) {
        func_02084700(e);
        target = func_020849c8(e);
        if (target != NULL) {
            if (e->action == 4) {
                kuttsukiReset(e);
            }
            func_02084ab8(e, target);
        } else {
            index = func_02084a30(e);
            data_020d1e14[index](e);
        }
    } else {
        type2Move(e);
    }
}

ARM void em09_normal(Entity *e) {
    data_020d1e2c[e->action](e);
}

ARM void em09_damage(Entity *e) {
    if (e->unk_3f == 0x14) {
        e->unk_3f = 0x13;
        e->hitbox = data_020d1db4;
        e->unk_3c &= 0x7f;
        e->unk_20 = VBT(e)->unk_7e;
        e->spriteSettings.b20 = VBT(e)->unk_7d;
        e->spriteSettings.b16 = e->spriteSettings.b20;
        e->spriteSettings.b6 = (VBT(e)->unk_7e & 0xff00) >> 8;
        e->unk_1b = 0x2c;
        e->action++;
        InitAnimationForceUpdate(e, 2);
        e->parent->spriteSettings.b0 = 1;
        InitAnimationForceUpdate(e->parent, 5);
        KemuriSet(e);
        if (e->contactedEntity->unk_08 == 8 || e->contactedEntity->unk_08 == 1) {
            e->child = data_0212ceb0[e->contactedEntity->type].entity;
        } else {
            e->child = EmGetAimPl();
        }
        return;
    }
    if (e->action == 4) {
        kuttsukiReset(e);
    }
    if (e->contactedEntity->unk_08 == 1) {
        if ((data_0212ceb0[e->contactedEntity->type].unk_36 & 2) == 0) {
            if (e->action == 2) {
                InitAnimationForceUpdate(e, 0);
                InitAnimationForceUpdate(e->parent, 3);
            }
            e->child = e->contactedEntity;
            e->child->unk_3c &= 0x7f;
            VBT(e)->unk_78 = e->child->unk_2e;
            e->unk_5c = data_020d1dac[e->child->type];
            e->action = 4;
            e->subtimer = 0;
            VBT(e)->unk_7c = 0x2d;
        } else {
            e->child = EmGetAimPl();
        }
    } else if (e->contactedEntity->unk_08 == 8) {
        e->child = data_0212ceb0[e->contactedEntity->type].entity;
    } else {
        e->child = EmGetAimPl();
    }
    e->direction = GetFacingDirection(e, e->child);
}

ARM void Boss_Release(Entity *e) {
    func_02084788(e);
}

ARM void type2Move(Entity *e) {
    Entity *parent = e->parent;
    e->x.HALF.HI = parent->x.HALF.HI;
    e->y.HALF.HI = parent->y.HALF.HI + 1;
    e->z.HALF.HI = parent->z.HALF.HI - 1;
    e->spriteSettings.b30 = parent->spriteSettings.b30;
    e->spriteSettings.b14 = parent->spriteSettings.b14;
    data_020d1da4[e->action](e);
}

ARM void em09_init(Entity *e) {
    Entity *child;
    Tbl3 table;
    child = GetEnemyWork(9);
    if (child == NULL) {
        return;
    }
    e->parent = child;
    child->parent = e;
    child->type = e->type;
    child->type2 = 1;
    VBT(e)->unk_7d = e->spriteSettings.b16;
    e->spriteSettings.b20 = data_020d1d90[e->type];
    e->spriteSettings.b16 = e->spriteSettings.b20;
    if (*((u8 *)&data_0212c7c8 + 0x8e) == 2) {
        table = *(Tbl3 *)data_020d1d8c;
        e->spriteSettings.b20 = table.v[e->type];
        e->spriteSettings.b16 = e->spriteSettings.b20;
    }
    e->unk_2e = 2;
    e->unk_3c |= 0x80;
    e->hitbox = data_020d1d9b;
    e->spriteSettings.b0 = 1;
    VBT(e)->unk_7e = e->unk_20 | (e->spriteSettings.b6 << 8);
    e->unk_20 = 0x28;
    e->spriteSettings.b6 = 3;
    e->action++;
    e->timer = 0x78;
    InitAnimationForceUpdate(e, 0);
}

ARM void em09_wait(Entity *e) {
    seqMove(e);
    if ((e->frame & 0x80) != 0) {
        InitAnimationForceUpdate(e, 0);
        InitAnimationForceUpdate(e->parent, 3);
        e->unk_28 = (Random() & 0xf0) + 1;
    }
}

ARM void em09_appear(Entity *e) {
    seqMove(e);
    if ((e->frame & 0x80) != 0) {
        e->action++;
        e->timer = 8;
        e->animationState = 0;
        {
            int dir = func_02084fd0(e, e->child);
            e->direction = dir;
            e->animationState = (dir & 0xff) >> 4;
        }
        InitAnimationForceUpdate(e, e->animationState);
        InitAnimationForceUpdate(e->parent, e->animationState + 3);
    } else if (e->frame == 1) {
        e->frame = 0;
        e->unk_3c |= 0x80;
    }
}

ARM void em09_move(Entity *e) {
    if (--e->timer == 0) {
        e->timer = 8;
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
            e->child = data_0212ceb0[*Knife_Single_SinglePlay_GetInstance()].entity;
        }
        e->direction = func_02084fd0(e, e->child);
        em09_seqSet(e);
    }
    func_020847a0(e);
    seqMove(e);
}
