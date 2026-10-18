#include "engine/player.h"
#include "global.h"

typedef struct Vars_02033290 {
    /* 00 */ u8 unk_00[0x6e];
    /* 6e */ u16 unk_6e;
    /* 70 */ u8 unk_70[0xc];
    /* 7c */ u8 unk_7c;
    /* 7d */ u8 unk_7d;
} Vars_02033290;
#define V(e) VARS(Vars_02033290, e)

extern const EntityFunc data_020d1004[];
extern const EntityFunc data_020d0ff0[];
extern const EntityFunc data_020d1050[];
extern const u8 data_020d0efa[];
extern Entity *data_0212c648;
extern u8 data_0212c504;
extern s32 data_021348b4;

void func_020547ec(void);
int func_02034124(Entity *e);
void func_020266f8(void);
void func_02026720(void);
void SoundReq(int sfx);
void *func_0208da4c(void);
int func_0208de54(void *a);
u8 *func_02093b5c(void);
int func_0203432c(Entity *e);
int func_02034508(Entity *e);
void func_02049f38(int a);

ARM void func_02033290(Entity *e) {
    EnemyFunctionHandler(e, data_020d1004);
    if (!(e->contactFlags & 0x80)) {
        return;
    }
    if ((e->contactFlags & 0x7f) != 0x10) {
        return;
    }
    data_0212ceb0[e->contactedEntity->type].unk_0c = 6;
    data_0212ceb0[e->contactedEntity->type].unk_38 = 1;
}

ARM void func_020332f8(Entity *e) {
    data_020d0ff0[e->type](e);
}

ARM void func_02033314(Entity *e) {
    GenericKnockback(e, data_020d1004);
}

ARM void func_02033328(Entity *e) {
    data_020d1050[e->action](e);
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 1)) {
        return;
    }
    e->frame = 0;
    e->unk_28 += Random() & 0x38;
}

ARM void func_02033378(Entity *e) {
    func_020547ec();
    if (func_02034124(e) == 0) {
        return;
    }
    e->action = 1;
    e->timer = 0x1e;
    e->spriteSettings.b0 = 1;
    e->hitbox = data_020d0efa;
    e->unk_6a = 1;
    e->unk_5e.b0 = 0;
    InitAnimationForceUpdate(e, 0);
    data_0212c648 = e;
    func_020266f8();
}

ARM void func_020333f0(Entity *e) {
    func_020547ec();
    if (V(e)->unk_7d != 7) {
        return;
    }
    if (--e->timer != 0) {
        return;
    }
    e->action = 2;
    e->timer = 0xb4;
    V(e)->unk_6e = 0x4b0;
    SoundReq(0x19c);
    if (func_0208de54(func_0208da4c()) != 0) {
        data_0212c648 = data_0212ceb0[data_0212c504].entity;
    } else {
        data_0212c648 = data_0212ceb0[*func_02093b5c()].entity;
    }
    func_02026720();
}

ARM void func_020334a4(Entity *e) {
    if (V(e)->unk_7c == 0) {
        if (e->timer != 0) {
            if (--e->timer == 0x5a) {
                InitAnimationForceUpdate(e, 0x1d);
            }
            return;
        }
        if (data_0212c7c8.unk_6 != 1) {
            if (func_0203432c(e) == 0) {
                return;
            }
            e->action = 3;
            e->timer = 0x3c;
            e->y.WORD++;
            V(e)->unk_6e = 0xe10;
            data_021348b4 = 0;
        } else {
            if (func_02034508(e) == 0) {
                return;
            }
            e->action = 5;
            e->y.WORD++;
            V(e)->unk_6e = 0x4b0;
        }
        return;
    }
    V(e)->unk_6e--;
    if (V(e)->unk_6e != 0) {
        return;
    }
    V(e)->unk_6e = 0x4b0;
    func_02049f38(0x3f3);
}

ARM void func_02033594(Entity *e) {
    if (V(e)->unk_7d == 3) {
        e->action = 4;
        e->timer = 0xb4;
    }
}

ARM void func_020335b0(Entity *e) {
    if (V(e)->unk_7c == 0) {
        if (e->timer != 0) {
            if (--e->timer == 0x5a) {
                InitAnimationForceUpdate(e, 0x1d);
            }
            return;
        }
        if (func_02034508(e) == 0) {
            return;
        }
        e->action = 5;
        e->y.WORD++;
        V(e)->unk_6e = 0x4b0;
        return;
    }
    V(e)->unk_6e--;
    if (V(e)->unk_6e != 0) {
        return;
    }
    V(e)->unk_6e = 0xe10;
    if (data_021348b4 == 0) {
        func_02049f38(0x3f5);
        return;
    }
    if (func_0208de54(func_0208da4c()) == 0) {
        return;
    }
    func_02049f38(0x3f4);
}

ARM void func_0203367c(Entity *e) {
    if (V(e)->unk_7d == 1) {
        e->action = 6;
    }
}

ARM void func_02033690(Entity *e) {
    if (V(e)->unk_7c == 0) {
        e->action = 7;
        e->timer = 0x96;
        return;
    }
    V(e)->unk_6e--;
    if (V(e)->unk_6e != 0) {
        return;
    }
    V(e)->unk_6e = 0xe10;
    func_02049f38(0x3f6);
}

ARM void func_020336e0(Entity *e) {
    if (--e->timer == 0) {
        e->health = 0;
        e->unk_3c &= 0x7f;
    }
}
