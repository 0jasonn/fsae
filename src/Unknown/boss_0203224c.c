#include "Unknown/Boss_02030a14.h"
#include "global.h"

typedef struct Vars_BossCore {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *unk_64;
    /* 68 */ u8 unk_68[0xc];
    /* 74 */ Entity *unk_74;
    /* 78 */ Entity *unk_78;
    /* 7c */ Entity *unk_7c;
} Vars_BossCore;
#define VC(e) VARS(Vars_BossCore, e)

typedef struct Vars_BossPart {
    /* 00 */ u8 unk_00[0x72];
    /* 72 */ u8 unk_72;
    /* 73 */ u8 unk_73;
    /* 74 */ u8 unk_74;
} Vars_BossPart;
#define VP(e) VARS(Vars_BossPart, e)

extern const u8 *const data_020f2658[];
int func_0205076c(Entity *e, int a, int b);
extern const u8 data_020d0c84[][6];
void CopyPosition(Entity *e, Entity *other);
extern const u16 data_020d0ac2[];
extern u8 data_0212c504;
Entity *func_020769d4(Entity *e, u8 id);
void *func_0208da4c(void);
int func_0208de54(void *a);
u8 *func_02093b5c(void);


extern const u8 data_020d0d40[][4];
extern const u8 data_020d0d80[][4];

ARM void func_0203224c(Entity *e) {
    e->action++;
    e->spriteSettings.b0 = 1;
    Entity *parent = e->parent;
    e->unk_50 = parent->unk_50;
    e->spriteSettings.b16 = parent->spriteSettings.b16;
    e->spriteSettings.b20 = e->spriteSettings.b16;
    e->spriteSettings.b6 = parent->spriteSettings.b6;
    e->unk_20 = parent->unk_20;
    e->x.WORD = parent->x.WORD;
    e->y.WORD = parent->y.WORD;
    if (e->timer == 0) {
        e->unk_3c = 0;
    } else {
        e->unk_2e = 8;
        e->spriteSettings.b4 = 3;
        e->unk_5e.b2 = 2;
    }
    e->hitbox = data_020d0a72;
    func_02032328(e);
}

ARM void func_02032328(Entity *e) {
    VH(e)->unk_74 = e->parent->x.HALF.HI + data_020d0ab2[VH(e)->unk_72 * 2];
    VH(e)->unk_76 = e->parent->y.HALF.HI + data_020d0ab2[VH(e)->unk_72 * 2 + 1];
    e->subtimer = 0;
    e->speed = 0x300;
    e->zVelocity = 0x30000;
    InitAnimationForceUpdate(e, 0xb);
}

ARM void func_02032388(Entity *e) {
    Entity *parent = e->parent;
    if (parent->action == 6 || parent->action == 2) {
        if (e->timer != 0) {
            parent->x.WORD = e->x.WORD;
            e->parent->y.WORD = e->y.WORD;
        }
        DeleteEntity(e);
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (e->frame == 0) {
        ProcessMovement(e);
        s16 dx = e->x.HALF.HI - VH(e)->unk_74;
        s16 dy = e->y.HALF.HI - (s16)VH(e)->unk_76;
        if (dx <= 3 && dx >= -3) {
            e->x.HALF.HI = VH(e)->unk_74;
            e->subtimer |= 1;
        }
        if (dy <= 3 && dy >= -3) {
            e->y.HALF.HI = VH(e)->unk_76;
            e->subtimer |= 2;
        }
        if (e->subtimer == 3) {
            e->direction = 0xff;
            if (UpdateGravity(e, 0x2000) == 0) {
                e->unk_28 = 1;
                if (e->timer != 0) {
                    Entity *fx = CreateFx(0x60, 0, 0);
                    if (fx != NULL) {
                        fx->unk_1b = 0x81;
                        fx->unk_23 = 0xd;
                        fx->x.HALF.HI = e->x.HALF.HI;
                        fx->y.HALF.HI = e->y.HALF.HI;
                        fx->spriteSettings.b16 = e->spriteSettings.b16 + 1;
                        fx->spriteSettings.b14 = e->spriteSettings.b14;
                        fx->spriteSettings.b30 = e->spriteSettings.b30;
                        fx->spriteSettings.b6 = e->spriteSettings.b6;
                        fx->unk_20 = e->unk_20;
                        fx->unk_5e.b0 = 0;
                    }
                    SoundReq(0xa7);
                }
                V(e->parent)->unk_79 |= (u8)(1 << (e->type2 & 0xf));
            }
        } else {
            e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, VH(e)->unk_74, (s16)VH(e)->unk_76);
            if (e->zVelocity == 0) {
                e->unk_28 = 2;
            } else {
                UpdateGravity(e, 0x1000);
            }
        }
    } else if (e->frame & 0x80) {
        if (V(e->parent)->unk_79 == 0) {
            VH(e)->unk_72 = (VH(e)->unk_72 + 1) & 7;
            func_02032328(e);
        }
    }
    e->subtimer |= func_02032cac(e);
}

ARM void func_020325f8(Entity *e) {
    VC(e)->unk_64->unk_21 = e->unk_21 + 0xf;
    VC(e)->unk_74->unk_21 = e->unk_21 + 0x1c;
    VC(e)->unk_78->unk_21 = e->unk_21 + 0x29;
    VC(e)->unk_7c->unk_21 = e->unk_21 + 0x36;
}

ARM void func_0203263c(Entity *e) {
    if ((VC(e)->unk_64 = CreateEnemy(0x2a)) != NULL) {
        VC(e)->unk_64->parent = e;
        VC(e)->unk_64->type = 1;
        VC(e)->unk_64->timer = 0;
        VP(VC(e)->unk_64)->unk_74 = 0xf;
        VC(e)->unk_64->subtimer = VP(VC(e)->unk_64)->unk_74;
        VC(e)->unk_64->spriteSettings.b6 = e->spriteSettings.b6;
        VC(e)->unk_64->unk_20 = e->unk_20;
    }
    if ((VC(e)->unk_74 = CreateEnemy(0x2a)) != NULL) {
        VC(e)->unk_74->parent = e;
        VC(e)->unk_74->type = 1;
        VC(e)->unk_74->timer = 1;
        VP(VC(e)->unk_74)->unk_74 = 0xf;
        VC(e)->unk_74->subtimer = VP(VC(e)->unk_74)->unk_74;
        VC(e)->unk_74->spriteSettings.b6 = e->spriteSettings.b6;
        VC(e)->unk_74->unk_20 = e->unk_20;
    }
    if ((VC(e)->unk_78 = CreateEnemy(0x2a)) != NULL) {
        VC(e)->unk_78->parent = e;
        VC(e)->unk_78->type = 1;
        VC(e)->unk_78->timer = 2;
        VP(VC(e)->unk_78)->unk_74 = 0xf;
        VC(e)->unk_78->subtimer = VP(VC(e)->unk_78)->unk_74;
        VC(e)->unk_78->spriteSettings.b6 = e->spriteSettings.b6;
        VC(e)->unk_78->unk_20 = e->unk_20;
    }
    if ((VC(e)->unk_7c = CreateEnemy(0x2a)) != NULL) {
        VC(e)->unk_7c->parent = e;
        VC(e)->unk_7c->type = 1;
        VC(e)->unk_7c->timer = 3;
        VP(VC(e)->unk_7c)->unk_74 = 0xf;
        VC(e)->unk_7c->subtimer = VP(VC(e)->unk_7c)->unk_74;
        VC(e)->unk_7c->spriteSettings.b6 = e->spriteSettings.b6;
        VC(e)->unk_7c->unk_20 = e->unk_20;
    }
    u8 r = Random() & 0xf;
    VC(e)->unk_64->type2 = data_020d0d40[r][0] | 0x80;
    VC(e)->unk_74->type2 = data_020d0d40[r][1] | 0x80;
    VC(e)->unk_78->type2 = data_020d0d40[r][2] | 0x80;
    VC(e)->unk_7c->type2 = data_020d0d40[r][3] | 0x80;
    u8 rnd = Random() & 3;
    u8 idx = rnd + (data_0212c7c8.unk_0 - 1) * 4;
    VP(VC(e)->unk_64)->unk_73 = data_020d0d80[idx][VC(e)->unk_64->type2 & 0xf];
    VP(VC(e)->unk_74)->unk_73 = data_020d0d80[idx][VC(e)->unk_74->type2 & 0xf];
    VP(VC(e)->unk_78)->unk_73 = data_020d0d80[idx][VC(e)->unk_78->type2 & 0xf];
    VP(VC(e)->unk_7c)->unk_73 = data_020d0d80[idx][VC(e)->unk_7c->type2 & 0xf];
    SoundReq(0xa3);
}

ARM void func_02032910(Entity *e) {
    u8 i;
    u8 pick = Random() & 3;
    u8 flip = Random() & 1;
    for (i = 0; i < 4; i++) {
        Entity *part = CreateEnemy(0x2a);
        if (part != NULL) {
            part->type = 1;
            part->type2 = i | 0x40;
            VP(part)->unk_72 = flip + i * 2;
            part->parent = e;
            if (i == pick) {
                part->timer = 0xff;
            } else {
                part->timer = 0;
            }
        }
    }
    SoundReq(0xa1);
}

ARM void func_0203298c(Entity *e) {
    int target = func_0205076c(e, 0, 0);
    e->subtimer = target;
    e->direction = func_02086078(data_0212ceb0[target].entity, e);
}

ARM void func_020329c8(Entity *e) {
    if (e->type == 2 && e->spriteSettings.b0 == 0) {
        return;
    }
    Entity *fx = CreateFx(0x60, 0, 0);
    if (fx != NULL) {
        fx->unk_1b = 0x81;
        fx->unk_23 = (e->type - 1) * 10 + 3;
        fx->x.HALF.HI = e->x.HALF.HI;
        fx->y.HALF.HI = e->y.HALF.HI;
        fx->spriteSettings.b16 = e->spriteSettings.b16 + 1;
        fx->spriteSettings.b14 = e->spriteSettings.b14;
        fx->spriteSettings.b30 = e->spriteSettings.b30;
        fx->spriteSettings.b6 = e->spriteSettings.b6;
        fx->unk_20 = e->unk_20;
        fx->unk_5e.b0 = 0;
    }
    SoundReq(0xa7);
}

ARM void func_02032ac4(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_3f = 0x3d;
    e->unk_3c |= 0x80;
    V(e)->unk_75 = 0;
    e->speed = 0x300;
    e->zVelocity = 0x30000;
    e->action = 2;
    e->timer = 0x20;
    e->subtimer = 0;
    if (e->type > 1) {
        InitAnimationForceUpdate(e, (e->type - 1) * 10 + 2);
    } else {
        InitAnimationForceUpdate(e, 2);
    }
}

ARM void func_02032b48(Entity *e) {
    e->health = data_020f2658[data_0212c7c8.unk_0 - 1][e->type - 1];
}

ARM void func_02032b78(Entity *e) {
    if (V(e)->unk_7c == 0) {
        return;
    }
    if (V(e)->unk_74 >= 5) {
        V(e)->unk_74 = 4;
    }
    for (u8 i = 0; data_020d0c84[V(e)->unk_74][i] != 0xff; i++) {
        Entity *debris = func_020769d4(e, data_020d0c84[V(e)->unk_74][i]);
        if (debris != NULL) {
            debris->x.HALF.HI -= 8;
            debris->z.HALF.HI = -0x10;
            debris->direction = ((Random() & 7) + 0x14) | 0x80;
            debris->type2 = 1;
        }
    }
}

ARM void func_02032c2c(Entity *e) {
    V(e)->unk_70 = data_020d0ac2[Random() & 7];
    e->direction = func_02086078(e, data_0212ceb0[e->timer].entity) & 0x18;
    e->speed = 0x100;
    e->zVelocity = 0x20000;
    InitAnimationForceUpdate(e, (e->type - 1) * 10 + 1);
}

ARM u8 func_02032cac(Entity *e) {
    u8 result = 0;
    if (e->x.HALF.HI < 0x198) {
        e->x.HALF.HI = 0x198;
        result = 1;
    } else if (e->x.HALF.HI > 0x250) {
        if (!(e->type2 & 0x40) && e->z.WORD == 0) {
            func_02032ac4(e);
        }
        if (e->x.HALF.HI > 0x298) {
            e->x.HALF.HI = 0x298;
            result = 1;
        }
    }
    if (e->y.HALF.HI < 0x1a8) {
        e->y.HALF.HI = 0x1a8;
        result |= 2;
    } else if (e->y.HALF.HI > 0x248) {
        e->y.HALF.HI = 0x248;
        result |= 2;
    }
    return result;
}

ARM u8 func_02032d34(Entity *e) {
    u8 i;
    u8 best;
    u16 bestDist = 0xffff;
    best = 0xff;
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        if (e->timer != i) {
            Entity *player = data_0212ceb0[i].entity;
            if (player->x.HALF.HI < 0x250) {
                s16 dx = player->x.HALF.HI - e->x.HALF.HI;
                s16 dy = player->y.HALF.HI - e->y.HALF.HI;
                dx = -dx;
                dy = -dy;
                if (best == 0xff) {
                    bestDist = dy + dx;
                    best = i;
                } else if (bestDist > (u16)(dy + dx)) {
                    bestDist = dy + dx;
                    best = i;
                }
            }
        }
    }
    return best;
}

ARM void func_02032e04(Entity *e) {
    if (e->type != 3) {
        return;
    }
    u8 player = data_0212c504;
    if (func_0208de54(func_0208da4c()) == 0) {
        player = *func_02093b5c();
    }
    if (player == V(e)->unk_78) {
        e->spriteSettings.b0 = 1;
    } else {
        e->spriteSettings.b0 = 0;
    }
}

ARM void func_02032e5c(Entity *e) {
    for (u8 i = 0; i < 4; i++) {
        Entity *fx = CreateFx(0xf, 0xd, 0x20);
        if (fx != NULL) {
            CopyPosition(e, fx);
            fx->y.HALF.HI -= 0x10;
            fx->speed = (Random() & 0x1f) << 8;
            fx->direction = Random() & 0x1f;
            ProcessMovement(fx);
        }
    }
}
