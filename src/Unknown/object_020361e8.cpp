#include "Unknown/Player.hpp"
#include "global.h"

struct Vars_02036314 {
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
};
#define V(e) VARS(Vars_02036314, e)

extern const EntityFunc data_020d1320[];
extern const u8 data_020d1259[];
extern Entity *data_0212c648;
extern s32 data_021348c8;
extern const u16 data_020d1262[];

struct Vars_Flag {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ s32 unk_70;
};

extern "C" {
void func_020547ec(void);
void func_0204fd40(Entity *e);
Entity *func_0204bdb8(int id);
void func_02076fe0(int sfx);
void func_02026720(void);
void func_020266f8(void);
void func_02036bd0(Entity *e);
void func_02036b2c(Entity *e);
void func_02036c64(Entity *e, u16 x, u16 y);
int func_02085608(void);
u8 func_02086078(Entity *e, Entity *target);
void *func_0208da4c(void);
int func_0208de54(void *a);
u8 *func_02093b5c(void);
}

ARM extern "C" void func_020361e8(Entity *e) {
    data_020d1320[e->unk_14](e);
    if (!(e->unk_41 & 0x80)) {
        return;
    }
    if (e->unk_41 & 0x7f) {
        return;
    }
    if (data_0212ceb0[e->unk_4c->unk_0a].unk_36 & 0x400) {
        return;
    }
    Entity *obj = func_02076858(0x55, 1, 0);
    if (obj == NULL) {
        return;
    }
    obj->unk_58 = e->unk_4c;
    data_0212ceb0[e->unk_4c->unk_0a].unk_36 |= 0x400;
}

ARM extern "C" void func_02036278(Entity *e) {
    e->unk_50 = 0x4000;
    e->unk_1c.b0 = 1;
    func_020859e0(e, 0);
    e->unk_5e.b2 = 2;
    e->unk_48 = data_020d1259;
    e->unk_2b = 0xff;
    e->unk_6a = 1;
    func_02036b2c(e);
    e->unk_18 = 0x3c;
    V(e)->unk_7b = 0x1e;
    e->unk_58 = data_0212c648;
    data_0212c648 = e;
    func_020266f8();
    data_021348c8 = 0;
    V(e)->unk_6e = 0;
}

ARM extern "C" void func_02036314(Entity *e) {
    if (e->unk_0a == 0) {
        func_020547ec();
        if (e->unk_18 != 0) {
            e->unk_18--;
            return;
        }
    }
    if (e->unk_45 == 0) {
        if (data_0212c7c8.unk_6 == e->unk_0a) {
            V(e)->unk_79 = 4;
        } else {
            V(e)->unk_79 = e->unk_0a + 1;
        }
    } else {
        V(e)->unk_79 = e->unk_0a;
    }
    if (V(e)->unk_79 >= 4) {
        V(e)->unk_79 = 4;
    }
    if (e->unk_0a >= 4) {
        e->unk_0a = 4;
    }
    if (e->unk_10 != 0) {
        func_02085980(e);
        func_020856cc(e, 0x2000);
        func_0204fd40(e);
        return;
    }
    if (V(e)->unk_78 != 0) {
        if (--V(e)->unk_78 % 4 != 0) {
            return;
        }
        Entity *fx = func_0204bdb8(0xf);
        if (fx == NULL) {
            return;
        }
        if (func_0208455c() & 1) {
            fx->unk_30.HALF.HI = e->unk_30.HALF.HI + (func_0208455c() & 0xf);
        } else {
            fx->unk_30.HALF.HI = e->unk_30.HALF.HI - (func_0208455c() & 0xf);
        }
        if (func_0208455c() & 1) {
            fx->unk_34.HALF.HI = e->unk_34.HALF.HI + (func_0208455c() & 0xf);
        } else {
            fx->unk_34.HALF.HI = e->unk_34.HALF.HI - (func_0208455c() & 0xf);
        }
        fx->unk_0b = 4;
        fx->unk_54 = e;
        if ((V(e)->unk_7a++ & 3) == 0) {
            func_02085f80(0xbb);
        }
        return;
    }
    if (e->unk_17 != 0) {
        if (e->unk_17 == 0x5a && e->unk_0a != 4) {
            func_02085f80(0xbc);
        }
        if (--e->unk_17 & 1) {
            func_020859e0(e, 0);
            return;
        }
        int anim = V(e)->unk_79;
        if (anim == 4) {
            return;
        }
        func_020859e0(e, anim);
        return;
    }
    if (e->unk_0a == 0) {
        data_0212c648 = e->unk_58;
        func_02076fe0(0x19c);
        func_02026720();
    }
    e->unk_45 = 1;
    e->unk_0a = V(e)->unk_79;
    int next = V(e)->unk_79;
    if (next == 4) {
        func_020859e0(e, 0);
    } else {
        func_020859e0(e, next);
        e->unk_1c.b4 = 2;
        e->unk_3c |= 0x80;
    }
    func_02036bd0(e);
}

ARM extern "C" void func_02036580(Entity *e) {
    func_02085980(e);
    func_020856cc(e, 0x2000);
    switch (V(e)->unk_70) {
        case 4:
            if (e->unk_38.WORD != 0) {
                return;
            }
            e->unk_17 -= 10;
            if (e->unk_17 != 0) {
                e->unk_10 = 0x30000;
                return;
            }
            break;
        case 0:
        case 1:
        case 2:
            e->unk_30.HALF.HI = V(e)->unk_72 + (s8)e->unk_18;
            e->unk_18 = -e->unk_18;
            if (--e->unk_17 != 0) {
                return;
            }
            break;
        case 3:
            func_0204fd40(e);
            e->unk_2b = (e->unk_2b + 1) & 0x1f;
            break;
    }
    e->unk_30.HALF.HI = V(e)->unk_72;
    switch (V(e)->unk_70) {
        case 4:
            for (e->unk_17 = data_0212c7c8.unk_0 << 2; e->unk_17 != 0; e->unk_17--) {
                int x = ((func_0208455c() & 0x1f) << 4) + 0x76;
                int y = ((func_0208455c() & 0x1f) << 4) + 0xa8;
                func_02036c64(e, x, y);
            }
            func_02036bd0(e);
            return;
        case 0:
            e->unk_2b = func_0208455c() & 0x1f;
            e->unk_0c = 0x100;
            e->unk_14 = 3;
            e->unk_10 = 0x20000;
            e->unk_17 = 5;
            func_02036c64(e, e->unk_30.HALF.HI, e->unk_34.HALF.HI);
            return;
        case 1:
            e->unk_2b = func_02086078(e, data_0212ceb0[func_02085608()].unk_28);
            e->unk_17 = e->unk_0a + 3;
            e->unk_0c = 0x100;
            e->unk_14 = 3;
            e->unk_10 = 0x20000;
            return;
        case 2: {
            Entity *fx = func_0204bdb8(0xf);
            if (fx != NULL) {
                fx->unk_30.HALF.HI = e->unk_30.HALF.HI;
                fx->unk_34.HALF.HI = e->unk_34.HALF.HI;
                fx->unk_17 = func_02085608();
                fx->unk_54 = e;
                V(e)->unk_71 = 1;
            }
            func_02036bd0(e);
            return;
        }
        case 3: {
            Entity *fx = func_0204bdb8(0xf);
            if (fx != NULL) {
                fx->unk_17 = func_02085608();
                fx->unk_30.HALF.HI = e->unk_30.HALF.HI;
                fx->unk_34.HALF.HI = e->unk_34.HALF.HI;
                fx->unk_0b = 1;
                fx->unk_54 = e;
            }
            func_02036bd0(e);
            return;
        }
    }
}

ARM extern "C" void func_020367e0(Entity *e) {
    func_02085980(e);
    func_020852ec(e);
    if (func_020856cc(e, 0x2000) != 0) {
        return;
    }
    if (e->unk_0a < 4) {
        func_02085f80(0xa7);
    }
    if (--e->unk_17 != 0) {
        if (e->unk_0a == 4) {
            func_02085f80(0x31);
        }
        e->unk_10 = 0x20000;
        if (V(e)->unk_70 == 0) {
            e->unk_2b = func_0208455c() & 0x1f;
        } else if (func_0208de54(func_0208da4c()) != 0) {
            e->unk_2b = func_02086078(e, data_0212ceb0[func_02085608()].unk_28);
        } else {
            e->unk_2b = func_02086078(e, data_0212ceb0[*func_02093b5c()].unk_28);
        }
        func_02036c64(e, e->unk_30.HALF.HI, e->unk_34.HALF.HI);
        return;
    }
    func_02036bd0(e);
}

ARM extern "C" void func_020368d8(Entity *e) {
    if (e->unk_0a == 4 && data_021348c8 != 0) {
        e->unk_14 = 6;
        return;
    }
    e->unk_1c.b0 ^= 1;
    e->unk_3c &= 0x7f;
    if (e->unk_18 != 0) {
        if (V(e)->unk_74-- != 0) {
            return;
        }
        V(e)->unk_74 = 5;
        if (e->unk_17 != 0) {
            Entity *fx = func_0204bdb8(0xf);
            if (fx != NULL) {
                fx->unk_30.HALF.HI = e->unk_30.HALF.HI;
                fx->unk_34.HALF.HI = e->unk_34.HALF.HI;
                fx->unk_38.HALF.HI = e->unk_38.HALF.HI;
                fx->unk_0a = e->unk_0a;
                fx->unk_0b = 3;
                fx->unk_54 = e;
                if (e->unk_17 == e->unk_18) {
                    e->unk_58 = fx;
                    fx->unk_45 = 0x20;
                    VARS(Vars_Flag, fx)->unk_70 = 1;
                }
            }
            e->unk_17--;
            return;
        }
        e->unk_14++;
        V(e)->unk_74 = data_020d1262[e->unk_0a - 1];
        if (e->unk_0a == 4 && data_021348c8 == 0) {
            V(e)->unk_74 = 0x258;
        }
        e->unk_1c.b0 = 0;
        if (e->unk_0a == 4) {
            data_021348c8++;
        }
        return;
    }
    e->unk_18 = (func_0208455c() & 7) + 1;
    V(e)->unk_74 = 5;
}
