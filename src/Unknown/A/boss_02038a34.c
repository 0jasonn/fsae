#include "Unknown/A/Boss_02038544.h"
#include "global.h"

ARM void func_02038a34(Entity *e) {
    func_020847a0(e);
    if (func_020856cc(e, 0x2000) != 0) {
        return;
    }
    e->unk_14 = 5;
    e->unk_0c -= 0x40;
    e->unk_5e.b0 = 2;
    func_020859e0(e, 4);
}

ARM void func_02038a88(Entity *e) {
    if (e->unk_60 == 0) {
        return;
    }
    Entity *n = e->unk_54;
    if (n == 0) {
        return;
    }
    if (e->unk_0b == 1) {
        e->unk_64[4] = 0;
        n->unk_0b = 0;
    }
}

ARM void func_02038ab4(Entity *e) {
    func_02084a7c(e, data_020d195c);
}

ARM void func_02038ac8(Entity *e) {
    data_020d18bc[e->unk_14](e);
}

ARM void func_02038ae4(Entity *e) {
    if (e->unk_14 == 3) {
        e->unk_14 = 1;
        e->unk_0c = 0x80;
        e->unk_18 = 0x14;
    }
    func_020849f4(e, data_020d195c);
}

ARM void func_02038b1c(Entity *e) {
    e->unk_1c.b0 = 1;
    e->unk_2e = 2;
    e->unk_48 = data_020d18b4;
    func_020859e0(e, 0);
    e->unk_2a = 0;
    e->unk_14++;
}
