// Nonmatching: loads of p[0], x, y, p[1] are ordered differently (5 lines differ, register choice).
#include "Unknown/D/Common_D.hpp"
#include "Unknown/Player.hpp"
#include "global.h"

extern "C" {
void func_02083000(Entity *a, u8 *base);
}
extern u8 data_0212dd90[];

struct Vars_D_76 {
    /* 00 */ u8 unk_00[0x76];
    /* 76 */ u8 unk_76;
    /* 77 */ u8 unk_77;
    /* 78 */ s16 unk_78;
    /* 7a */ s16 unk_7a;
    /* 7c */ s16 unk_7c;
    /* 7e */ s16 unk_7e;
};
#define V76(e) VARS(Vars_D_76, e)

ARM extern "C" void func_0205063c(Entity *a, Entity *e) {
    u8 *base = data_0212dd90 + (e->unk_1c.b24 >> 1) * 0x20;
    u8 *q;
    u8 *d;
    func_02083000(a, base);
    base = data_0212dd90 + (e->unk_1c.b24 >> 1) * 0x20;
    q = base + 6;
    d = q + 0x400;
    *(u16 *)d = *(u16 *)(base + 6);
    *(u16 *)(d + 8) = *(u16 *)(q + 8);
    *(u16 *)(d + 0x10) = *(u16 *)(q + 0x10);
    *(u16 *)(d + 0x18) = *(u16 *)(q + 0x18);
}

ARM extern "C" void func_0205069c(Entity *e, u16 *p, s32 flag) {
    u16 a = p[0];
    s16 y = e->unk_34.HALF.HI;
    s16 x = e->unk_30.HALF.HI;
    u16 b = p[1];
    if (flag == 0) {
        flag = 1;
    }
    V76(e)->unk_76 = 0;
    V76(e)->unk_77 = flag;
    V76(e)->unk_78 = x;
    V76(e)->unk_7a = y;
    V76(e)->unk_7c = a;
    V76(e)->unk_7e = b;
}

