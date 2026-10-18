#include "Unknown/A/Boss_02038544.hpp"
#include "global.h"

ARM extern "C" void func_02038660(Entity *e) {
    e->unk_2e = 2;
    e->unk_1c.b0 = 1;
    e->unk_1c.b4 = 1;
    e->unk_48 = data_020d1828;
    e->unk_14++;
    e->unk_17 = (func_0208455c() & 0x38) + 0x14;
    V(e)->unk_64 = func_02045eb4();
    e->unk_2b = func_0204fdf0(e, V(e)->unk_64);
    func_020859e0(e, 0);
}

ARM extern "C" void func_020386d8(Entity *e) {
    if (func_020856cc(e, 0x2000) != 0) {
        return;
    }
    func_02085980(e);
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14++;
    func_020859e0(e, 1);
}

ARM extern "C" void func_02038728(Entity *e) {
    func_02085980(e);
    if (e->unk_29 != 0x80) {
        return;
    }
    e->unk_14++;
    e->unk_10 = 0x18000;
    func_020859e0(e, 2);
    if (func_0208de54(func_0208da4c()) == 0) {
        u8 p = *func_02093b5c();
        V(e)->unk_64 = data_0212ceb0[p].unk_28;
    }
    e->unk_2b = func_02084fd0(e, V(e)->unk_64);
    func_02083c84(e);
    e->unk_15 = 0;
}

ARM extern "C" void func_020387b4(Entity *e) {
    func_020847a0(e);
    func_020856cc(e, 0x2000);
    if (e->unk_15 == 0) {
        e->unk_15++;
        func_02085f80(0x31);
    }
    if (e->unk_10 < 0) {
        e->unk_14++;
        func_020859e0(e, 3);
    }
}

ARM extern "C" void func_02038810(Entity *e) {
    func_020847a0(e);
    if (func_020856cc(e, 0x2000) != 0) {
        return;
    }
    e->unk_14++;
    func_020859e0(e, 4);
}

ARM extern "C" void func_0203884c(Entity *e) {
    func_02085980(e);
    if (e->unk_29 != 0x80) {
        return;
    }
    e->unk_14 = 1;
    e->unk_17 = (func_0208455c() & 0x38) + 0x14;
    func_020859e0(e, 0);
}
