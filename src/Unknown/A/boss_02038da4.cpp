#include "Unknown/A/Boss_02038544.hpp"
#include "global.h"

ARM extern "C" void func_02038da4(Entity *e) {
    func_02084f54(e);
    if (e->unk_43 == 0) {
        e->unk_3f = V(e)->unk_7c;
    }
}

ARM extern "C" void func_02038dc4(Entity *e) {
    if (e->unk_0a != 0) {
        e->unk_3f = 9;
    }
    e->unk_1c.b0 = 1;
    e->unk_2e = 6;
    V(e)->unk_7d = e->unk_45;
    e->unk_48 = data_020d19b8;
    if (e->unk_0a == 3) {
        e->unk_18 = (func_0208455c() & 0x7f) + 0x40;
    }
    e->unk_14++;
    e->unk_17 = 1;
    e->unk_2a = 0;
    func_020859e0(e, 0);
    func_02039278(e);
}

ARM extern "C" void func_02038e54(Entity *e) {
    if (--e->unk_17 == 0) {
        e->unk_17 = (func_0208455c() & 0x1c) + 0x1e;
        func_02039278(e);
    }
    func_020847a0(e);
    func_02085980(e);
}

ARM extern "C" void func_02038e9c(Entity *e) {
    func_020847c8(e);
    func_02085980(e);
    if (func_020856cc(e, 0x1100) != 0) {
        return;
    }
    e->unk_14++;
    func_020859e0(e, e->unk_2a + 6);
}
