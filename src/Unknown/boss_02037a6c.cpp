#include "Unknown/Boss_02036ca4.hpp"
#include "global.h"

ARM extern "C" void func_02037a6c(Entity *e) {
    func_02085980(e);
    if (--e->unk_17 != 0) {
        return;
    }
    if (--e->unk_18 != 0) {
        e->unk_14 = 0x17;
        e->unk_17 = 0x3c;
    } else {
        e->unk_14 = 0xd;
        e->unk_17 = 0x3c;
        e->unk_0c = 0x100;
        func_020859e0(e, 0);
    }
    e->unk_1c.b30 = 2;
    e->unk_1c.b14 = e->unk_1c.b30;
}

ARM extern "C" void func_02037af8(Entity *e) {
    func_02085980(e);
    if (--e->unk_17 == 0) {
        e->unk_14 = 0x1f;
        e->unk_0c = 0x100;
    }
}

ARM extern "C" void func_02037b28(Entity *e) {
    func_02085980(e);
    if ((u16)(e->unk_30.HALF.HI - 0x1f7) <= 2 && (u16)(e->unk_34.HALF.HI - 0x1f7) <= 2) {
        e->unk_14 = 0x20;
        e->unk_17 = 0x3c;
        e->unk_30.HALF.HI = 0x1f8;
        e->unk_34.HALF.HI = 0x1f8;
        return;
    }
    e->unk_2b = func_02086080(e->unk_30.HALF.HI, e->unk_34.HALF.HI, 0x1f8, 0x1f8);
    if ((data_0212c5bc & 7) == 0) {
        func_02076a50(e, 1, 1, 0x14);
    }
    func_0204fd40(e);
    func_02060a70(e);
}

ARM extern "C" void func_02037bd8(Entity *e) {
    func_02085980(e);
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14 = 0x21;
    e->unk_17 = 0xd2;
    V(e)->unk_6e = data_020d1440[func_0208455c() & 7];
}
