#include "Unknown/B/Actor_020407c8.hpp"
#include "global.h"

ARM extern "C" void func_02041064(Entity *e) {
    Entity *c = func_0204bdf0(9);
    if (c == NULL) {
        return;
    }
    c->unk_54 = e;
    e->unk_58 = c;
    e->unk_14 = 1;
    e->unk_1c.b0 = 1;
    e->unk_2e = 5;
    e->unk_3c |= 0x80;
    e->unk_48 = data_020d32d4;
    e->unk_17 = 0x64;
    data_021348cc.unk_0 = 0;
    data_021348cc.unk_4 = 0;
    func_020859e0(e, 0);
}

ARM extern "C" void func_020410e4(Entity *e) {
    e->unk_14 = 2;
    e->unk_17 = 0x3c;
    e->unk_6c[8] = 0x3c;
    e->unk_18 = 4;
    e->unk_2b = func_0208455c() & 0x18;
    e->unk_2a = e->unk_2b >> 3;
    func_020859e0(e, e->unk_2a);
}
