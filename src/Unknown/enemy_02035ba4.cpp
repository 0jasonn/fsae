#include "Unknown/Enemy_020347dc.hpp"
#include "global.h"

ARM extern "C" void func_02035ba4(Entity *e) {
    if (V(e)->unk_70 == NULL) {
        return;
    }
    if (func_0208de54(func_0208da4c()) == 0) {
        return;
    }
    V(e)->unk_70->unk_1c.b20 = data_020d119f[e->unk_1c.b16][func_0208455c() % (data_0212c7c8.unk_0 - 1)];
    V(e)->unk_70->unk_1c.b16 = V(e)->unk_70->unk_1c.b20;
}

ARM extern "C" void func_02035c3c(Entity *e) {
    Entity *other = V(e)->unk_70;
    if (other == NULL) {
        return;
    }
    e->unk_3f = 0x3f;
    e->unk_48 = data_020d11a4;
    other->unk_3c |= 0x80;
    func_020859e0(V(e)->unk_70, 8);
    V(e)->unk_70->unk_28 += func_0208455c() & 7;
}

ARM extern "C" void func_02035c98(Entity *e) {
    Entity *other = V(e)->unk_70;
    e->unk_3f = 0x40;
    e->unk_48 = data_020d119c;
    if (other != NULL) {
        other->unk_3c &= 0x7f;
        func_020859e0(V(e)->unk_70, 7);
    }
    func_020859e0(e, 6);
}

ARM extern "C" void func_02035ce8(Entity *e) {
    V(e)->unk_6e &= 0x3f;
    e->unk_1c.b20 = e->unk_54->unk_1c.b16;
    e->unk_1c.b16 = e->unk_1c.b20;
    if (V(e)->unk_70 != NULL) {
        V(e)->unk_70->unk_1c.b0 = 0;
    }
    func_020859e0(e, 3);
}
