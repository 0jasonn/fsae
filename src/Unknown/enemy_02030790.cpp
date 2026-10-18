#include "Unknown/Entity.hpp"
#include "global.h"

struct Vars_02030790 {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u8 unk_7c;
};

extern const EntityFunc data_020d08e4[];
extern const EntityFunc data_020d08fc[];
extern const u8 data_020d08cc[];

ARM extern "C" void func_02030790(Entity *e) {
    func_02084a7c(e, data_020d08e4);
}

ARM extern "C" void func_020307a4(Entity *e) {
    data_020d08fc[e->unk_14](e);
}

ARM extern "C" void func_020307c0(Entity *e) {
    if (e->unk_45 != 0 && VARS(Vars_02030790, e)->unk_7c != e->unk_45) {
        e->unk_14 = 6;
        return;
    }
    func_020849f4(e, data_020d08e4);
}

ARM extern "C" void func_020307f0(Entity *e) {
    e->unk_1c.b0 = 1;
    e->unk_2e = 2;
    e->unk_48 = data_020d08cc;
    func_020859e0(e, 0);
    e->unk_14++;
    e->unk_17 = (func_0208455c() + 0x1e) & 0x3c;
    VARS(Vars_02030790, e)->unk_7c = e->unk_45;
}

ARM extern "C" void func_0203084c(Entity *e) {
    func_02085980(e);
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14++;
    e->unk_17 = 0x48;
    e->unk_2b = func_0208455c() & 0x18;
    func_020859e0(e, (e->unk_2b >> 3) + 1);
}

ARM extern "C" void func_020308a4(Entity *e) {
    if (--e->unk_17 != 0) {
        if (e->unk_29 == 0) {
            func_020852ec(e);
        }
        func_02085980(e);
        return;
    }
    if (func_0208455c() & 7) {
        e->unk_14--;
        e->unk_17 = (func_0208455c() + 0x1e) & 0x3c;
        func_020859e0(e, 0);
        return;
    }
    e->unk_14++;
    func_020859e0(e, 5);
}

ARM extern "C" void func_02030930(Entity *e) {
    func_02085980(e);
    if (e->unk_29 == 0) {
        return;
    }
    if (e->unk_29 == 1) {
        e->unk_3c &= 0x7f;
        return;
    }
    e->unk_14++;
    e->unk_17 = 0x78;
    e->unk_1c.b0 = 0;
}

ARM extern "C" void func_02030980(Entity *e) {
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14++;
    e->unk_1c.b0 = 1;
    func_020859e0(e, 6);
}

ARM extern "C" void func_020309c0(Entity *e) {
    func_02085980(e);
    if (e->unk_29 == 0) {
        return;
    }
    if (e->unk_29 == 1) {
        e->unk_3c |= 0x80;
        return;
    }
    e->unk_14 = 1;
    e->unk_17 = (func_0208455c() + 0x1e) & 0x3c;
    func_020859e0(e, 0);
}
