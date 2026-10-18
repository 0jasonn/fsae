// Nonmatching: second-half register allocation (14 lines differ: y1/n loaded into swapped registers).
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

ARM extern "C" BOOL func_020506d8(Entity *e) {
    u8 cur = V76(e)->unk_76;
    u8 lim = V76(e)->unk_77;
    s32 n;
    s16 x0;
    s16 y0;
    s32 r;
    if (cur >= lim) {
        e->unk_30.HALF.HI = V76(e)->unk_7c;
        e->unk_34.HALF.HI = V76(e)->unk_7e;
        return TRUE;
    }
    x0 = V76(e)->unk_78;
    n = cur + 1;
    r = ((((s16)V76(e)->unk_7c - x0) * (n & 0xff)) << 8);
    V76(e)->unk_76 = n;
    r = func_0200d948(r, V76(e)->unk_77);
    y0 = V76(e)->unk_7a;
    e->unk_30.HALF.HI = x0 + ((r << 8) >> 16);
    r = func_0200d948((((s16)V76(e)->unk_7e - y0) * V76(e)->unk_76) << 8, V76(e)->unk_77);
    e->unk_34.HALF.HI = y0 + ((r << 8) >> 16);
    return FALSE;
}
