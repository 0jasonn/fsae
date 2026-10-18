#include "Unknown/Player.hpp"
#include "global.h"

struct Vars_PathMover {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ const u16 *unk_70; // current path command
    /* 74 */ const u16 *unk_74; // path start
    /* 78 */ u16 unk_78; // target x
    /* 7a */ u16 unk_7a; // target y
    /* 7c */ s16 unk_7c; // start x
    /* 7e */ s16 unk_7e; // start y
};
#define V(e) VARS(Vars_PathMover, e)

struct UnkStruct_0212c540 {
    u16 unk_0;
    u16 unk_2;
};
extern UnkStruct_0212c540 data_0212c540;
extern const EntityFunc data_020d0e8c[];
extern const EntityFunc data_020d0e94[];
extern const u8 data_020cfdd4[];

extern "C" {
void func_0204fd40(Entity *e);
const u16 *func_0204d634(u8 a, u8 b);
void func_02033174(Entity *e);
}

ARM extern "C" void func_02032edc(Entity *e) {
    if (data_0212c540.unk_2 > 1) {
        func_02084700(e);
    }
    data_020d0e8c[e->unk_14](e);
}

ARM extern "C" void func_02032f18(Entity *e) {
    e->unk_18 = func_0208455c();
    e->unk_2e = 6;
    e->unk_48 = data_020cfdd4;
    V(e)->unk_7c = e->unk_30.HALF.HI;
    V(e)->unk_7e = e->unk_34.HALF.HI;
    V(e)->unk_74 = V(e)->unk_70 = func_0204d634(e->unk_52, e->unk_0b);
    func_02033174(e);
    func_020859e0(e, 0);
    e->unk_14 = 1;
    e->unk_1c.b0 = 1;
}

ARM extern "C" void func_02032f90(Entity *e) {
    data_020d0e94[e->unk_15](e);
}

ARM extern "C" void func_02032fac(Entity *e) {
    func_0204fd40(e);
    if (V(e)->unk_7a < e->unk_34.HALF.HI) {
        return;
    }
    e->unk_34.HALF.HI = V(e)->unk_7a;
    func_02033174(e);
}

ARM extern "C" void func_02032fd8(Entity *e) {
    func_0204fd40(e);
    if (V(e)->unk_7a < e->unk_34.HALF.HI) {
        return;
    }
    if (V(e)->unk_78 > e->unk_30.HALF.HI) {
        return;
    }
    e->unk_30.HALF.HI = V(e)->unk_78;
    e->unk_34.HALF.HI = V(e)->unk_7a;
    func_02033174(e);
}

ARM extern "C" void func_02033018(Entity *e) {
    func_0204fd40(e);
    if (V(e)->unk_78 > e->unk_30.HALF.HI) {
        return;
    }
    e->unk_30.HALF.HI = V(e)->unk_78;
    func_02033174(e);
}

ARM extern "C" void func_02033044(Entity *e) {
    func_0204fd40(e);
    if (V(e)->unk_7a > e->unk_34.HALF.HI || V(e)->unk_78 > e->unk_30.HALF.HI) {
        return;
    }
    e->unk_30.HALF.HI = V(e)->unk_78;
    e->unk_34.HALF.HI = V(e)->unk_7a;
    func_02033174(e);
}

ARM extern "C" void func_02033080(Entity *e) {
    func_0204fd40(e);
    if (V(e)->unk_7a > e->unk_34.HALF.HI) {
        return;
    }
    e->unk_34.HALF.HI = V(e)->unk_7a;
    func_02033174(e);
}

ARM extern "C" void func_020330ac(Entity *e) {
    func_0204fd40(e);
    if (V(e)->unk_7a > e->unk_34.HALF.HI) {
        return;
    }
    if (V(e)->unk_78 < e->unk_30.HALF.HI) {
        return;
    }
    e->unk_30.HALF.HI = V(e)->unk_78;
    e->unk_34.HALF.HI = V(e)->unk_7a;
    func_02033174(e);
}

ARM extern "C" void func_020330ec(Entity *e) {
    func_0204fd40(e);
    if (V(e)->unk_78 < e->unk_30.HALF.HI) {
        return;
    }
    e->unk_30.HALF.HI = V(e)->unk_78;
    func_02033174(e);
}

ARM extern "C" void func_02033118(Entity *e) {
    func_0204fd40(e);
    if (V(e)->unk_7a < e->unk_34.HALF.HI || V(e)->unk_78 < e->unk_30.HALF.HI) {
        return;
    }
    e->unk_30.HALF.HI = V(e)->unk_78;
    e->unk_34.HALF.HI = V(e)->unk_7a;
    func_02033174(e);
}

ARM extern "C" void func_02033154(Entity *e) {
    if (--e->unk_17 != 0) {
        return;
    }
    func_02033174(e);
}

ARM extern "C" void func_02033174(Entity *e) {
    if (V(e)->unk_70[0] == 0xffff) {
        V(e)->unk_70 = V(e)->unk_74;
    }
    const u16 *cmd = V(e)->unk_70;
    u16 op = cmd[0];
    if (op & 0x8000) {
        e->unk_15 = 8;
        e->unk_17 = cmd[1];
    } else {
        e->unk_2b = op;
        e->unk_15 = (op & 0xff) >> 2;
        switch (e->unk_15) {
            case 1:
                V(e)->unk_78 = e->unk_30.HALF.HI + cmd[1];
            case 0:
                V(e)->unk_7a = e->unk_34.HALF.HI - cmd[1];
                break;
            case 3:
                V(e)->unk_7a = e->unk_34.HALF.HI + cmd[1];
            case 2:
                V(e)->unk_78 = e->unk_30.HALF.HI + cmd[1];
                break;
            case 5:
                V(e)->unk_78 = e->unk_30.HALF.HI - cmd[1];
            case 4:
                V(e)->unk_7a = e->unk_34.HALF.HI + cmd[1];
                break;
            case 7:
                V(e)->unk_7a = e->unk_34.HALF.HI - cmd[1];
            case 6:
                V(e)->unk_78 = e->unk_30.HALF.HI - cmd[1];
                break;
        }
        if (cmd[2] != 0) {
            e->unk_0c = cmd[2];
        }
    }
    V(e)->unk_70 += 4;
}
