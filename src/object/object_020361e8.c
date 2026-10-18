#include "engine/player.h"
#include "global.h"

typedef struct Vars_02036314 {
    /* 00 */ u8 unk_00[0x6e];
    /* 6e */ u16 unk_6e;
    /* 70 */ u8 unk_70; // mode
    /* 71 */ u8 unk_71;
    /* 72 */ u16 unk_72; // home x
    /* 74 */ s32 unk_74;
    /* 78 */ u8 unk_78;
    /* 79 */ u8 unk_79;
    /* 7a */ u8 unk_7a;
    /* 7b */ u8 unk_7b;
} Vars_02036314;
#define V(e) VARS(Vars_02036314, e)

extern const EntityFunc data_020d1320[];
extern const u8 data_020d1259[];
extern Entity *data_0212c648;
extern s32 data_021348c8;
extern const u16 data_020d1262[];
extern const u32 data_020d126c[];
extern const u32 data_020f2698[];

typedef struct Vars_Flag {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ s32 unk_70;
} Vars_Flag;

void func_020547ec(void);
void ProcessMovement(Entity *e);
Entity *CreateProjectile(int id);
void SoundReq(int sfx);
void func_02026720(void);
void func_020266f8(void);
void func_02036bd0(Entity *e);
void func_02036b2c(Entity *e);
void func_02036c64(Entity *e, u16 x, u16 y);
void func_02045ac0(Entity *e);
u8 CalculateDirectionTo(s16 x, s16 y, s16 tx, s16 ty);
void *func_0208dde0(void *a, u32 *out, u32 b);
void func_020845b0(u32 dest, void *src, u16 size);
u8 func_02085620(u32 a);
int func_02085608(void);
u8 func_02086078(Entity *e, Entity *target);
void *func_0208da4c(void);
int func_0208de54(void *a);
u8 *func_02093b5c(void);

ARM void func_020361e8(Entity *e) {
    data_020d1320[e->action](e);
    if (!(e->contactFlags & 0x80)) {
        return;
    }
    if (e->contactFlags & 0x7f) {
        return;
    }
    if (data_0212ceb0[e->contactedEntity->type].unk_36 & 0x400) {
        return;
    }
    Entity *obj = CreateFx(0x55, 1, 0);
    if (obj == NULL) {
        return;
    }
    obj->child = e->contactedEntity;
    data_0212ceb0[e->contactedEntity->type].unk_36 |= 0x400;
}

ARM void func_02036278(Entity *e) {
    e->unk_50 = 0x4000;
    e->spriteSettings.b0 = 1;
    InitAnimationForceUpdate(e, 0);
    e->unk_5e.b2 = 2;
    e->hitbox = data_020d1259;
    e->direction = 0xff;
    e->unk_6a = 1;
    func_02036b2c(e);
    e->subtimer = 0x3c;
    V(e)->unk_7b = 0x1e;
    e->child = data_0212c648;
    data_0212c648 = e;
    func_020266f8();
    data_021348c8 = 0;
    V(e)->unk_6e = 0;
}

ARM void func_02036314(Entity *e) {
    if (e->type == 0) {
        func_020547ec();
        if (e->subtimer != 0) {
            e->subtimer--;
            return;
        }
    }
    if (e->health == 0) {
        if (data_0212c7c8.unk_6 == e->type) {
            V(e)->unk_79 = 4;
        } else {
            V(e)->unk_79 = e->type + 1;
        }
    } else {
        V(e)->unk_79 = e->type;
    }
    if (V(e)->unk_79 >= 4) {
        V(e)->unk_79 = 4;
    }
    if (e->type >= 4) {
        e->type = 4;
    }
    if (e->zVelocity != 0) {
        UpdateAnimationSingleFrame(e);
        UpdateGravity(e, 0x2000);
        ProcessMovement(e);
        return;
    }
    if (V(e)->unk_78 != 0) {
        if (--V(e)->unk_78 % 4 != 0) {
            return;
        }
        Entity *fx = CreateProjectile(0xf);
        if (fx == NULL) {
            return;
        }
        if (Random() & 1) {
            fx->x.HALF.HI = e->x.HALF.HI + (Random() & 0xf);
        } else {
            fx->x.HALF.HI = e->x.HALF.HI - (Random() & 0xf);
        }
        if (Random() & 1) {
            fx->y.HALF.HI = e->y.HALF.HI + (Random() & 0xf);
        } else {
            fx->y.HALF.HI = e->y.HALF.HI - (Random() & 0xf);
        }
        fx->type2 = 4;
        fx->parent = e;
        if ((V(e)->unk_7a++ & 3) == 0) {
            EnqueueSFX(0xbb);
        }
        return;
    }
    if (e->timer != 0) {
        if (e->timer == 0x5a && e->type != 4) {
            EnqueueSFX(0xbc);
        }
        if (--e->timer & 1) {
            InitAnimationForceUpdate(e, 0);
            return;
        }
        int anim = V(e)->unk_79;
        if (anim == 4) {
            return;
        }
        InitAnimationForceUpdate(e, anim);
        return;
    }
    if (e->type == 0) {
        data_0212c648 = e->child;
        SoundReq(0x19c);
        func_02026720();
    }
    e->health = 1;
    e->type = V(e)->unk_79;
    int next = V(e)->unk_79;
    if (next == 4) {
        InitAnimationForceUpdate(e, 0);
    } else {
        InitAnimationForceUpdate(e, next);
        e->spriteSettings.b4 = 2;
        e->unk_3c |= 0x80;
    }
    func_02036bd0(e);
}

ARM void func_02036580(Entity *e) {
    UpdateAnimationSingleFrame(e);
    UpdateGravity(e, 0x2000);
    switch (V(e)->unk_70) {
        case 4:
            if (e->z.WORD != 0) {
                return;
            }
            e->timer -= 10;
            if (e->timer != 0) {
                e->zVelocity = 0x30000;
                return;
            }
            break;
        case 0:
        case 1:
        case 2:
            e->x.HALF.HI = V(e)->unk_72 + (s8)e->subtimer;
            e->subtimer = -e->subtimer;
            if (--e->timer != 0) {
                return;
            }
            break;
        case 3:
            ProcessMovement(e);
            e->direction = (e->direction + 1) & 0x1f;
            break;
    }
    e->x.HALF.HI = V(e)->unk_72;
    switch (V(e)->unk_70) {
        case 4:
            for (e->timer = data_0212c7c8.unk_0 << 2; e->timer != 0; e->timer--) {
                int x = ((Random() & 0x1f) << 4) + 0x76;
                int y = ((Random() & 0x1f) << 4) + 0xa8;
                func_02036c64(e, x, y);
            }
            func_02036bd0(e);
            return;
        case 0:
            e->direction = Random() & 0x1f;
            e->speed = 0x100;
            e->action = 3;
            e->zVelocity = 0x20000;
            e->timer = 5;
            func_02036c64(e, e->x.HALF.HI, e->y.HALF.HI);
            return;
        case 1:
            e->direction = func_02086078(e, data_0212ceb0[func_02085608()].entity);
            e->timer = e->type + 3;
            e->speed = 0x100;
            e->action = 3;
            e->zVelocity = 0x20000;
            return;
        case 2: {
            Entity *fx = CreateProjectile(0xf);
            if (fx != NULL) {
                fx->x.HALF.HI = e->x.HALF.HI;
                fx->y.HALF.HI = e->y.HALF.HI;
                fx->timer = func_02085608();
                fx->parent = e;
                V(e)->unk_71 = 1;
            }
            func_02036bd0(e);
            return;
        }
        case 3: {
            Entity *fx = CreateProjectile(0xf);
            if (fx != NULL) {
                fx->timer = func_02085608();
                fx->x.HALF.HI = e->x.HALF.HI;
                fx->y.HALF.HI = e->y.HALF.HI;
                fx->type2 = 1;
                fx->parent = e;
            }
            func_02036bd0(e);
            return;
        }
    }
}

ARM void func_020367e0(Entity *e) {
    UpdateAnimationSingleFrame(e);
    func_020852ec(e);
    if (UpdateGravity(e, 0x2000) != 0) {
        return;
    }
    if (e->type < 4) {
        EnqueueSFX(0xa7);
    }
    if (--e->timer != 0) {
        if (e->type == 4) {
            EnqueueSFX(0x31);
        }
        e->zVelocity = 0x20000;
        if (V(e)->unk_70 == 0) {
            e->direction = Random() & 0x1f;
        } else if (func_0208de54(func_0208da4c()) != 0) {
            e->direction = func_02086078(e, data_0212ceb0[func_02085608()].entity);
        } else {
            e->direction = func_02086078(e, data_0212ceb0[*func_02093b5c()].entity);
        }
        func_02036c64(e, e->x.HALF.HI, e->y.HALF.HI);
        return;
    }
    func_02036bd0(e);
}

ARM void func_020368d8(Entity *e) {
    if (e->type == 4 && data_021348c8 != 0) {
        e->action = 6;
        return;
    }
    e->spriteSettings.b0 ^= 1;
    e->unk_3c &= 0x7f;
    if (e->subtimer != 0) {
        if (V(e)->unk_74-- != 0) {
            return;
        }
        V(e)->unk_74 = 5;
        if (e->timer != 0) {
            Entity *fx = CreateProjectile(0xf);
            if (fx != NULL) {
                fx->x.HALF.HI = e->x.HALF.HI;
                fx->y.HALF.HI = e->y.HALF.HI;
                fx->z.HALF.HI = e->z.HALF.HI;
                fx->type = e->type;
                fx->type2 = 3;
                fx->parent = e;
                if (e->timer == e->subtimer) {
                    e->child = fx;
                    fx->health = 0x20;
                    VARS(Vars_Flag, fx)->unk_70 = 1;
                }
            }
            e->timer--;
            return;
        }
        e->action++;
        V(e)->unk_74 = data_020d1262[e->type - 1];
        if (e->type == 4 && data_021348c8 == 0) {
            V(e)->unk_74 = 0x258;
        }
        e->spriteSettings.b0 = 0;
        if (e->type == 4) {
            data_021348c8++;
        }
        return;
    }
    e->subtimer = (Random() & 7) + 1;
    V(e)->unk_74 = 5;
}

ARM void func_02036a58(Entity *e) {
    Entity *target = e->child;
    e->x.HALF.HI = target->x.HALF.HI;
    e->y.HALF.HI = target->y.HALF.HI;
    if (target->health == 0) {
        V(e)->unk_74 = 0;
        e->health = 0;
        EnqueueSFX(0xa3);
    }
    if (V(e)->unk_74-- != 0) {
        return;
    }
    if (e->child->health != 0) {
        data_021348c8 = 0;
    }
    e->spriteSettings.b0 ^= 1;
    InitAnimationForceUpdate(e, 0);
    func_02036b2c(e);
    e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, 0x1f8, 0x1f8);
}

ARM void func_02036b14(Entity *e) {
    func_02045ac0(e);
    e->type = 5;
}

ARM void func_02036b2c(Entity *e) {
    if (e->health == 0) {
        u8 level = e->type;
        if (level < 3 && level != 0) {
            u32 size;
            void *data = func_0208dde0(func_0208da4c(), &size, data_020d126c[level - 1]);
            func_020845b0(0x6403000, data, size);
        }
    }
    e->zVelocity = 0x30000;
    e->action = 1;
    e->timer = 0x5a;
    V(e)->unk_78 = 0x78;
    e->unk_2e = 2;
    e->spriteSettings.b4 = 1;
    V(e)->unk_7a = 0;
}

ARM void func_02036bd0(Entity *e) {
    if (V(e)->unk_70 != 2 && V(e)->unk_71 == 0) {
        V(e)->unk_70 = 2;
    } else {
        u8 mode;
        do {
            mode = func_02085620(data_020f2698[e->type - 1]);
        } while (V(e)->unk_70 == mode || (mode == 2 && V(e)->unk_71 != 0));
        V(e)->unk_70 = mode;
    }
    e->timer = 0x1e;
    e->subtimer = 2;
    e->direction = 8;
    e->speed = 0x200;
    e->action = 2;
    V(e)->unk_72 = e->x.HALF.HI;
}

ARM void func_02036c64(Entity *e, u16 x, u16 y) {
    if (Random() & 1) {
        return;
    }
    Entity *fx = CreateProjectile(0xf);
    if (fx != NULL) {
        fx->x.HALF.HI = x;
        fx->y.HALF.HI = y;
        fx->type2 = 2;
        fx->parent = e;
    }
}
