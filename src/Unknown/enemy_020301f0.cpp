#include "Unknown/Entity.hpp"
#include "global.h"

extern const EntityFunc data_020d0828[];
extern const EntityFunc data_020d0840[];
extern const u8 data_020d07c4[];
extern const u8 data_020d0798[];
extern const s8 data_020d07a0[];
extern const EntityFunc data_020d089c[];
extern const u8 data_020d0894[];

struct UnkStruct_0212c540 {
    u16 unk_0;
    u16 unk_2;
};
extern UnkStruct_0212c540 data_0212c540;

ARM extern "C" void func_020301f0(Entity *e) {
    func_02084a7c(e, data_020d0828);
}

ARM extern "C" void func_02030204(Entity *e) {
    data_020d0840[e->unk_14](e);
}

ARM extern "C" void func_02030220(Entity *e) {
    switch (e->unk_41 & 0x7f) {
        case 0:
            if (e->unk_14 == 3) {
                e->unk_17 = 1;
            }
            break;
        case 1:
        case 2:
        case 3:
        case 0x16:
        case 0x18:
        case 0x19:
        case 0x1a:
            if (e->unk_14 < 6) {
                e->unk_14 = 6;
                e->unk_10 = 0x18000;
                e->unk_0c = 0xc0;
                e->unk_2b = e->unk_3e;
                e->unk_42 = 0;
                e->unk_3f = 0x2f;
                func_020859e0(e, 9);
            }
            break;
    }
    func_020849f4(e, data_020d0828);
}

ARM extern "C" void func_020302f8(Entity *e) {
    e->unk_14 = 1;
    e->unk_17 = 1;
    e->unk_1c = (e->unk_1c & ~3) | 1;
    e->unk_2e = 5;
    e->unk_48 = data_020d07c4;
    e->unk_2b = func_0208455c() & 0x18;
    func_020859e0(e, e->unk_2a = e->unk_2b >> 3);
}

ARM extern "C" void func_02030354(Entity *e) {
    if (func_02084ac8(e, 0xc) & 0x80) {
        e->unk_14 = 2;
        e->unk_17 = 0x1e;
        e->unk_58 = func_02084f18();
        e->unk_2b = func_0204fdf0(e, e->unk_58);
        func_020859e0(e, 8);
    } else {
        if (--e->unk_17 == 0) {
            e->unk_17 = data_020d0798[func_0208455c() & 3];
            if (func_0208455c() & 0x1f) {
                e->unk_2b = func_0208455c() & 0x18;
            } else {
                e->unk_2b = (func_0204fdf0(e, func_02045eb4()) + 4) & 0x18;
            }
            if ((e->unk_2b >> 3) != e->unk_2a) {
                func_020859e0(e, e->unk_2a = e->unk_2b >> 3);
            }
        }
        if (func_020847a0(e) == 0) {
            e->unk_17 = 1;
        }
    }
    func_02085980(e);
}

ARM extern "C" void func_02030444(Entity *e) {
    func_02085980(e);
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14 = 3;
    e->unk_17 = 0x78;
    e->unk_0c = 0x1c0;
    func_020859e0(e, 8);
}

ARM extern "C" void func_0203048c(Entity *e) {
    if (func_020847c8(e) == 0) {
        e->unk_17 = 1;
    }
    func_02085980(e);
    if (--e->unk_17 != 0) {
        if ((e->unk_17 & 7) == 0) {
            func_02086200(e, func_0204fdf0(e, e->unk_58));
        }
        return;
    }
    e->unk_14 = 4;
    e->unk_17 = 0x10;
    func_020859e0(e, e->unk_2a + 4);
}

ARM extern "C" void func_0203050c(Entity *e) {
    if (--e->unk_17 != 0) {
        return;
    }
    e->unk_14 = 1;
    e->unk_17 = 1;
    e->unk_0c = 0x80;
    func_020859e0(e, e->unk_2a);
}

ARM extern "C" void func_02030544(Entity *e) {
    if (func_020856cc(e, 0x1800) == 0) {
        e->unk_14 = 1;
        e->unk_17 = 1;
    }
}

ARM extern "C" void func_02030568(Entity *e) {
    func_020847c8(e);
    switch (func_02086044(e, 0x1800)) {
        case 0:
            e->unk_14 = 7;
            e->unk_17 = 0x96;
        case 1:
            func_02085f80(0x31);
            break;
    }
}

ARM extern "C" void func_020305b0(Entity *e) {
    if (--e->unk_17 != 0) {
        if (e->unk_17 >= 0x3c) {
            return;
        }
        if ((e->unk_17 & 1) == 0) {
            return;
        }
        e->unk_32 += data_020d07a0[(e->unk_17 >> 1) & 3];
        return;
    }
    e->unk_14 = 5;
    e->unk_10 = 0x10000;
    e->unk_0c = 0x80;
    e->unk_3f = 0x2e;
    func_020859e0(e, e->unk_2a);
    func_02085f80(0x31);
}

ARM extern "C" void func_02030630(Entity *e) {
    if (data_0212c540.unk_2 > 1) {
        func_02084700(e);
    }
    data_020d089c[e->unk_14](e);
}

ARM extern "C" void func_0203066c(Entity *e) {
    e->unk_14 = 1;
    e->unk_1c = (e->unk_1c & ~3) | 1;
    e->unk_2e = 5;
    e->unk_48 = data_020d0894;
    func_020859e0(e, 0);
}

ARM extern "C" void func_020306a8(Entity *e) {
    u32 result = func_02084ac8(e, 0xa);
    if (result & 0x80) {
        e->unk_14 = 2;
        e->unk_0c = 0x40;
        e->unk_2b = result & 0x18;
        func_020859e0(e, 1);
        return;
    }
    if (e->unk_41 < 1 || e->unk_41 > 3) {
        return;
    }
    e->unk_14 = 2;
    e->unk_0c = 0x40;
    e->unk_2b ^= 0x10;
    func_020859e0(e, 1);
}

ARM extern "C" void func_02030728(Entity *e) {
    func_02085980(e);
    if (func_020847a0(e) != 0) {
        if (e->unk_0c < 0x110) {
            e->unk_0c += 8;
        }
        return;
    }
    e->unk_14 = 3;
    func_020859e0(e, 2);
}

ARM extern "C" void func_02030770(Entity *e) {
    func_02085980(e);
    if (e->unk_29 & 0x80) {
        e->unk_14 = 1;
    }
}
