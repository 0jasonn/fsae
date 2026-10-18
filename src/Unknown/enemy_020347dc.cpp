#include "Unknown/Player.hpp"
#include "global.h"

struct Vars_020347dc {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *unk_64;
    /* 68 */ u8 unk_68[8];
    /* 70 */ Entity *unk_70;
    /* 74 */ u8 unk_74[8];
    /* 7c */ u16 unk_7c;
    /* 7e */ u8 unk_7e;
    /* 7f */ u8 unk_7f;
};
#define V(e) VARS(Vars_020347dc, e)

struct Vars_Event {
    /* 00 */ u8 unk_00[0x7d];
    /* 7d */ u8 unk_7d;
};
#define VE(e) VARS(Vars_Event, e)

struct UnkStruct_021348c0 {
    s32 unk_0;
    s32 unk_4;
};
extern UnkStruct_021348c0 data_021348c0;

extern const EntityFunc data_020d11e0[];
extern const EntityFunc data_020d11c0[];
extern const u8 data_020f266e[];
extern const u8 data_020f266b[];
extern const u8 data_020f2668[];
extern const u16 data_020f267a[];
extern const u8 data_020d119c[];
extern const s16 data_020d7e58[];
extern const u32 data_020cf9b8[];

extern "C" {
void *func_0208da4c(void);
int func_0208de54(void *a);
u8 *func_02093b5c(void);
int func_02035d50(Entity *e);
void func_0205031c(Entity *e, Entity *other);
void func_02050390(Entity *e, Entity *other, s32 a, s32 b);
void func_020360c0(Entity *e);
void func_02035a8c(Entity *e);
void func_02036064(Entity *e);
void func_02035c3c(Entity *e);
int func_020358c4(Entity *e);
void func_02035f18(Entity *e);
void func_02035c98(Entity *e);
void func_02035ce8(Entity *e);
Entity *func_02045eb4(void);
u8 func_02084fd0(Entity *e, Entity *target);
}

ARM extern "C" void func_020347dc(Entity *e) {
    if (e->unk_0a == 0) {
        data_020d11e0[e->unk_14](e);
        V(e)->unk_7f--;
    } else {
        data_020d11c0[e->unk_14](e);
    }
    if (func_0208de54(func_0208da4c()) != 0) {
        return;
    }
    if (data_021348c0.unk_4 != *func_02093b5c()) {
        data_021348c0.unk_4 = *func_02093b5c();
        data_021348c0.unk_0 = 0xb4;
    }
    if (data_021348c0.unk_0 != 0) {
        data_021348c0.unk_0--;
    }
}

ARM extern "C" void func_02034878(Entity *e) {
    if (func_02035d50(e) == 0) {
        return;
    }
    switch (e->unk_0b) {
        case 0:
            e->unk_14 = 1;
            e->unk_17 = 0x78;
            e->unk_18 = 0x96;
            e->unk_0c = 0x100;
            e->unk_45 = data_020f266e[data_0212c7c8.unk_6 - 1];
            V(e)->unk_7c = 0x10;
            func_020859e0(e, 3);
            break;
        case 1: {
            e->unk_14 = 7;
            e->unk_17 = 0x3c;
            e->unk_45 = data_020f266b[data_0212c7c8.unk_6 - 1];
            V(e)->unk_7c = 0x10;
            func_020859e0(e, 3);
            Entity *fx = func_02076858(0xf, 2, 0x20);
            if (fx != NULL) {
                func_0205031c(e, fx);
            }
            break;
        }
        case 2: {
            e->unk_14 = 0xe;
            e->unk_17 = 0x96;
            e->unk_0c = 0x100;
            e->unk_45 = data_020f2668[data_0212c7c8.unk_6 - 1];
            V(e)->unk_7c = 0x10;
            e->unk_2b = func_0208455c() & 0x1f;
            func_020859e0(e, (e->unk_2a = ((e->unk_2b + 2) >> 2) & 7) + 0x14);
            Entity *fx = func_02076858(0xf, 2, 0x20);
            if (fx != NULL) {
                func_0205031c(e, fx);
            }
            func_02085f80(0x9e);
            break;
        }
    }
    e->unk_1c.b20 = e->unk_54->unk_1c.b16;
    e->unk_1c.b16 = e->unk_1c.b20;
    e->unk_1c.b0 = 1;
    e->unk_48 = data_020d119c;
    V(e)->unk_7f = func_0208455c();
    data_021348c0.unk_0 = 0;
    data_021348c0.unk_4 = 0;
}

ARM extern "C" void func_02034a64(Entity *e) {
    if (data_0212c7c8.unk_5 & 0x80) {
        return;
    }
    if (e->unk_17 != 0) {
        if (--e->unk_17 != 0) {
            return;
        }
        func_020859e0(e, (e->unk_2a = ((e->unk_2b + 0x10) >> 5) & 7) + 0x14);
        func_02085f80(0x9e);
    }
    func_02050390(e->unk_54, e, (s16)((V(e)->unk_7c * data_020d7e58[e->unk_2b]) >> 8) << 16,
                  (s16)(-4 - ((V(e)->unk_7c * data_020d7e58[e->unk_2b + 0x40]) >> 8)) << 16);
    V(e)->unk_7c++;
    if (V(e)->unk_7c >= 0x40) {
        e->unk_14 = 2;
        e->unk_17 = 0x3c;
    }
}

ARM extern "C" void func_02034b44(Entity *e) {
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14 = 3;
    e->unk_17 = 0x5a;
    e->unk_0c = data_020f267a[data_0212c7c8.unk_6 - 1];
    VE(e->unk_54)->unk_7d |= (u8)data_020cf9b8[V(e)->unk_7e];
}

ARM extern "C" void func_02034bb4(Entity *e) {
    func_020360c0(e);
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14 = 4;
    func_02035a8c(e);
    V(e)->unk_70->unk_1c.b20 = e->unk_1c.b20;
    V(e)->unk_70->unk_1c.b16 = V(e)->unk_70->unk_1c.b20;
}

ARM extern "C" void func_02034c2c(Entity *e) {
    func_02036064(e);
    if (V(e)->unk_70 != NULL) {
        func_02085980(V(e)->unk_70);
    }
    func_02085980(e);
    if (!(e->unk_29 & 0x80)) {
        return;
    }
    e->unk_14 = 5;
    e->unk_17 = 0x5a;
    func_02035c3c(e);
}

ARM extern "C" void func_02034c78(Entity *e) {
    if (func_020358c4(e) != 0 && e->unk_45 == 0) {
        func_02035f18(e);
        return;
    }
    if (e->unk_17 == 0) {
        if (e->unk_3d == 0) {
            e->unk_14 = 6;
            func_02035c98(e);
        }
    } else {
        e->unk_17--;
    }
    func_02036064(e);
    if (V(e)->unk_70 != NULL) {
        func_02085980(V(e)->unk_70);
    }
}

ARM extern "C" void func_02034cf4(Entity *e) {
    func_02036064(e);
    if (V(e)->unk_70 != NULL) {
        func_02085980(V(e)->unk_70);
    }
    func_02085980(e);
    if (!(e->unk_29 & 0x80)) {
        return;
    }
    e->unk_14 = 3;
    e->unk_17 = 0x3c;
    func_02035ce8(e);
    func_020859e0(e, (e->unk_2a = ((e->unk_2b + 2) >> 2) & 7) + 0x14);
}

ARM extern "C" void func_02034d64(Entity *e) {
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14 = 8;
    VE(e->unk_54)->unk_7d |= (u8)data_020cf9b8[V(e)->unk_7e];
    func_02085f80(0x9e);
}

ARM extern "C" void func_02034db4(Entity *e) {
    if (e->unk_17 != 0) {
        e->unk_17--;
        return;
    }
    e->unk_14 = 9;
    e->unk_17 = (func_0208455c() & 0x3f) + 0xb4;
    if (data_0212c7c8.unk_0 != 2) {
        e->unk_0c = 0x120;
    } else {
        e->unk_0c = 0x100;
    }
    if (func_0208de54(func_0208da4c()) == 0) {
        if (data_021348c0.unk_0 == 0) {
            V(e)->unk_64 = data_0212ceb0[*func_02093b5c()].unk_28;
        }
        if (V(e)->unk_64 == NULL) {
            V(e)->unk_64 = func_02045eb4();
        }
    } else {
        V(e)->unk_64 = func_02045eb4();
    }
    if (V(e)->unk_64 == NULL) {
        return;
    }
    e->unk_2b = func_02084fd0(e, V(e)->unk_64);
    func_020859e0(e, (e->unk_2a = ((e->unk_2b + 2) >> 2) & 7) + 0x14);
}
