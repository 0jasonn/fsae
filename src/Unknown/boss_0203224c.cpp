#include "Unknown/Boss_02030a14.hpp"
#include "global.h"

struct Vars_BossCore {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *unk_64;
    /* 68 */ u8 unk_68[0xc];
    /* 74 */ Entity *unk_74;
    /* 78 */ Entity *unk_78;
    /* 7c */ Entity *unk_7c;
};
#define VC(e) VARS(Vars_BossCore, e)

struct Vars_BossPart {
    /* 00 */ u8 unk_00[0x73];
    /* 73 */ u8 unk_73;
    /* 74 */ u8 unk_74;
};
#define VP(e) VARS(Vars_BossPart, e)

extern const u8 data_020d0d40[][4];
extern const u8 data_020d0d80[][4];

ARM extern "C" void func_0203224c(Entity *e) {
    e->unk_14++;
    e->unk_1c.b0 = 1;
    Entity *parent = e->unk_54;
    e->unk_50 = parent->unk_50;
    e->unk_1c.b16 = parent->unk_1c.b16;
    e->unk_1c.b20 = e->unk_1c.b16;
    e->unk_1c.b6 = parent->unk_1c.b6;
    e->unk_20 = parent->unk_20;
    e->unk_30.WORD = parent->unk_30.WORD;
    e->unk_34.WORD = parent->unk_34.WORD;
    if (e->unk_17 == 0) {
        e->unk_3c = 0;
    } else {
        e->unk_2e = 8;
        e->unk_1c.b4 = 3;
        e->unk_5e.b2 = 2;
    }
    e->unk_48 = data_020d0a72;
    func_02032328(e);
}

ARM extern "C" void func_02032328(Entity *e) {
    VH(e)->unk_74 = e->unk_54->unk_30.HALF.HI + data_020d0ab2[VH(e)->unk_72 * 2];
    VH(e)->unk_76 = e->unk_54->unk_34.HALF.HI + data_020d0ab2[VH(e)->unk_72 * 2 + 1];
    e->unk_18 = 0;
    e->unk_0c = 0x300;
    e->unk_10 = 0x30000;
    func_020859e0(e, 0xb);
}

ARM extern "C" void func_02032388(Entity *e) {
    Entity *parent = e->unk_54;
    if (parent->unk_14 == 6 || parent->unk_14 == 2) {
        if (e->unk_17 != 0) {
            parent->unk_30.WORD = e->unk_30.WORD;
            e->unk_54->unk_34.WORD = e->unk_34.WORD;
        }
        func_0204be88(e);
        return;
    }
    func_02085980(e);
    if (e->unk_29 == 0) {
        func_0204fd40(e);
        s16 dx = e->unk_30.HALF.HI - VH(e)->unk_74;
        s16 dy = e->unk_34.HALF.HI - (s16)VH(e)->unk_76;
        if (dx <= 3 && dx >= -3) {
            e->unk_30.HALF.HI = VH(e)->unk_74;
            e->unk_18 |= 1;
        }
        if (dy <= 3 && dy >= -3) {
            e->unk_34.HALF.HI = VH(e)->unk_76;
            e->unk_18 |= 2;
        }
        if (e->unk_18 == 3) {
            e->unk_2b = 0xff;
            if (func_020856cc(e, 0x2000) == 0) {
                e->unk_28 = 1;
                if (e->unk_17 != 0) {
                    Entity *fx = func_02076858(0x60, 0, 0);
                    if (fx != NULL) {
                        fx->unk_1b = 0x81;
                        fx->unk_23 = 0xd;
                        fx->unk_30.HALF.HI = e->unk_30.HALF.HI;
                        fx->unk_34.HALF.HI = e->unk_34.HALF.HI;
                        fx->unk_1c.b16 = e->unk_1c.b16 + 1;
                        fx->unk_1c.b14 = e->unk_1c.b14;
                        fx->unk_1c.b30 = e->unk_1c.b30;
                        fx->unk_1c.b6 = e->unk_1c.b6;
                        fx->unk_20 = e->unk_20;
                        fx->unk_5e.b0 = 0;
                    }
                    func_02076fe0(0xa7);
                }
                V(e->unk_54)->unk_79 |= (u8)(1 << (e->unk_0b & 0xf));
            }
        } else {
            e->unk_2b = func_02086080(e->unk_30.HALF.HI, e->unk_34.HALF.HI, VH(e)->unk_74, (s16)VH(e)->unk_76);
            if (e->unk_10 == 0) {
                e->unk_28 = 2;
            } else {
                func_020856cc(e, 0x1000);
            }
        }
    } else if (e->unk_29 & 0x80) {
        if (V(e->unk_54)->unk_79 == 0) {
            VH(e)->unk_72 = (VH(e)->unk_72 + 1) & 7;
            func_02032328(e);
        }
    }
    e->unk_18 |= func_02032cac(e);
}

ARM extern "C" void func_020325f8(Entity *e) {
    VC(e)->unk_64->unk_21 = e->unk_21 + 0xf;
    VC(e)->unk_74->unk_21 = e->unk_21 + 0x1c;
    VC(e)->unk_78->unk_21 = e->unk_21 + 0x29;
    VC(e)->unk_7c->unk_21 = e->unk_21 + 0x36;
}

ARM extern "C" void func_0203263c(Entity *e) {
    if ((VC(e)->unk_64 = func_0204bd80(0x2a)) != NULL) {
        VC(e)->unk_64->unk_54 = e;
        VC(e)->unk_64->unk_0a = 1;
        VC(e)->unk_64->unk_17 = 0;
        VP(VC(e)->unk_64)->unk_74 = 0xf;
        VC(e)->unk_64->unk_18 = VP(VC(e)->unk_64)->unk_74;
        VC(e)->unk_64->unk_1c.b6 = e->unk_1c.b6;
        VC(e)->unk_64->unk_20 = e->unk_20;
    }
    if ((VC(e)->unk_74 = func_0204bd80(0x2a)) != NULL) {
        VC(e)->unk_74->unk_54 = e;
        VC(e)->unk_74->unk_0a = 1;
        VC(e)->unk_74->unk_17 = 1;
        VP(VC(e)->unk_74)->unk_74 = 0xf;
        VC(e)->unk_74->unk_18 = VP(VC(e)->unk_74)->unk_74;
        VC(e)->unk_74->unk_1c.b6 = e->unk_1c.b6;
        VC(e)->unk_74->unk_20 = e->unk_20;
    }
    if ((VC(e)->unk_78 = func_0204bd80(0x2a)) != NULL) {
        VC(e)->unk_78->unk_54 = e;
        VC(e)->unk_78->unk_0a = 1;
        VC(e)->unk_78->unk_17 = 2;
        VP(VC(e)->unk_78)->unk_74 = 0xf;
        VC(e)->unk_78->unk_18 = VP(VC(e)->unk_78)->unk_74;
        VC(e)->unk_78->unk_1c.b6 = e->unk_1c.b6;
        VC(e)->unk_78->unk_20 = e->unk_20;
    }
    if ((VC(e)->unk_7c = func_0204bd80(0x2a)) != NULL) {
        VC(e)->unk_7c->unk_54 = e;
        VC(e)->unk_7c->unk_0a = 1;
        VC(e)->unk_7c->unk_17 = 3;
        VP(VC(e)->unk_7c)->unk_74 = 0xf;
        VC(e)->unk_7c->unk_18 = VP(VC(e)->unk_7c)->unk_74;
        VC(e)->unk_7c->unk_1c.b6 = e->unk_1c.b6;
        VC(e)->unk_7c->unk_20 = e->unk_20;
    }
    u8 r = func_0208455c() & 0xf;
    VC(e)->unk_64->unk_0b = data_020d0d40[r][0] | 0x80;
    VC(e)->unk_74->unk_0b = data_020d0d40[r][1] | 0x80;
    VC(e)->unk_78->unk_0b = data_020d0d40[r][2] | 0x80;
    VC(e)->unk_7c->unk_0b = data_020d0d40[r][3] | 0x80;
    u8 rnd = func_0208455c() & 3;
    u8 idx = rnd + (data_0212c7c8.unk_0 - 1) * 4;
    VP(VC(e)->unk_64)->unk_73 = data_020d0d80[idx][VC(e)->unk_64->unk_0b & 0xf];
    VP(VC(e)->unk_74)->unk_73 = data_020d0d80[idx][VC(e)->unk_74->unk_0b & 0xf];
    VP(VC(e)->unk_78)->unk_73 = data_020d0d80[idx][VC(e)->unk_78->unk_0b & 0xf];
    VP(VC(e)->unk_7c)->unk_73 = data_020d0d80[idx][VC(e)->unk_7c->unk_0b & 0xf];
    func_02076fe0(0xa3);
}
