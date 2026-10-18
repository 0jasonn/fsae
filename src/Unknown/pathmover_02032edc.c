#include "Unknown/Player.h"
#include "global.h"

typedef struct Vars_PathMover {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ const u16 *unk_70; // current path command
    /* 74 */ const u16 *unk_74; // path start
    /* 78 */ u16 unk_78; // target x
    /* 7a */ u16 unk_7a; // target y
    /* 7c */ s16 unk_7c; // start x
    /* 7e */ s16 unk_7e; // start y
} Vars_PathMover;
#define V(e) VARS(Vars_PathMover, e)

typedef struct UnkStruct_0212c540 {
    u16 unk_0;
    u16 unk_2;
} UnkStruct_0212c540;
extern UnkStruct_0212c540 data_0212c540;
extern const EntityFunc data_020d0e8c[];
extern const EntityFunc data_020d0e94[];
extern const u8 data_020cfdd4[];

void ProcessMovement(Entity *e);
const u16 *func_0204d634(u8 a, u8 b);
void func_02033174(Entity *e);

ARM void func_02032edc(Entity *e) {
    if (data_0212c540.unk_2 > 1) {
        func_02084700(e);
    }
    data_020d0e8c[e->action](e);
}

ARM void func_02032f18(Entity *e) {
    e->subtimer = Random();
    e->unk_2e = 6;
    e->hitbox = data_020cfdd4;
    V(e)->unk_7c = e->x.HALF.HI;
    V(e)->unk_7e = e->y.HALF.HI;
    V(e)->unk_74 = V(e)->unk_70 = func_0204d634(e->unk_52, e->type2);
    func_02033174(e);
    InitAnimationForceUpdate(e, 0);
    e->action = 1;
    e->spriteSettings.b0 = 1;
}

ARM void func_02032f90(Entity *e) {
    data_020d0e94[e->subAction](e);
}

ARM void func_02032fac(Entity *e) {
    ProcessMovement(e);
    if (V(e)->unk_7a < e->y.HALF.HI) {
        return;
    }
    e->y.HALF.HI = V(e)->unk_7a;
    func_02033174(e);
}

ARM void func_02032fd8(Entity *e) {
    ProcessMovement(e);
    if (V(e)->unk_7a < e->y.HALF.HI) {
        return;
    }
    if (V(e)->unk_78 > e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = V(e)->unk_78;
    e->y.HALF.HI = V(e)->unk_7a;
    func_02033174(e);
}

ARM void func_02033018(Entity *e) {
    ProcessMovement(e);
    if (V(e)->unk_78 > e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = V(e)->unk_78;
    func_02033174(e);
}

ARM void func_02033044(Entity *e) {
    ProcessMovement(e);
    if (V(e)->unk_7a > e->y.HALF.HI || V(e)->unk_78 > e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = V(e)->unk_78;
    e->y.HALF.HI = V(e)->unk_7a;
    func_02033174(e);
}

ARM void func_02033080(Entity *e) {
    ProcessMovement(e);
    if (V(e)->unk_7a > e->y.HALF.HI) {
        return;
    }
    e->y.HALF.HI = V(e)->unk_7a;
    func_02033174(e);
}

ARM void func_020330ac(Entity *e) {
    ProcessMovement(e);
    if (V(e)->unk_7a > e->y.HALF.HI) {
        return;
    }
    if (V(e)->unk_78 < e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = V(e)->unk_78;
    e->y.HALF.HI = V(e)->unk_7a;
    func_02033174(e);
}

ARM void func_020330ec(Entity *e) {
    ProcessMovement(e);
    if (V(e)->unk_78 < e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = V(e)->unk_78;
    func_02033174(e);
}

ARM void func_02033118(Entity *e) {
    ProcessMovement(e);
    if (V(e)->unk_7a < e->y.HALF.HI || V(e)->unk_78 < e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = V(e)->unk_78;
    e->y.HALF.HI = V(e)->unk_7a;
    func_02033174(e);
}

ARM void func_02033154(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    func_02033174(e);
}

ARM void func_02033174(Entity *e) {
    if (V(e)->unk_70[0] == 0xffff) {
        V(e)->unk_70 = V(e)->unk_74;
    }
    const u16 *cmd = V(e)->unk_70;
    u16 op = cmd[0];
    if (op & 0x8000) {
        e->subAction = 8;
        e->timer = cmd[1];
    } else {
        e->direction = op;
        e->subAction = (op & 0xff) >> 2;
        switch (e->subAction) {
            case 1:
                V(e)->unk_78 = e->x.HALF.HI + cmd[1];
            case 0:
                V(e)->unk_7a = e->y.HALF.HI - cmd[1];
                break;
            case 3:
                V(e)->unk_7a = e->y.HALF.HI + cmd[1];
            case 2:
                V(e)->unk_78 = e->x.HALF.HI + cmd[1];
                break;
            case 5:
                V(e)->unk_78 = e->x.HALF.HI - cmd[1];
            case 4:
                V(e)->unk_7a = e->y.HALF.HI + cmd[1];
                break;
            case 7:
                V(e)->unk_7a = e->y.HALF.HI - cmd[1];
            case 6:
                V(e)->unk_78 = e->x.HALF.HI - cmd[1];
                break;
        }
        if (cmd[2] != 0) {
            e->speed = cmd[2];
        }
    }
    V(e)->unk_70 += 4;
}
