#include "Unknown/A/Boss_02038544.hpp"
#include "global.h"

// Nonmatching: only register assignment differs in the L_02038d18 block (constant 0 and unk_14 value swap r1/r2).
ARM extern "C" void func_02038ce8(Entity *e) {
    if (e->unk_43 != 0) {
        if (e->unk_14 == 2 || (e->unk_0a != 3 && e->unk_14 == 4)) {
            e->unk_17 = 0;
            e->unk_14++;
        }
        V(e)->unk_7c = e->unk_3f;
        e->unk_3f = 6;
    }
    if (e->unk_15 == 0xff) {
        u8 anim = e->unk_2a + 4;
        e->unk_14 = 2;
        e->unk_15 = 0;
        e->unk_10 = 0x18000;
        e->unk_0c = 0x100;
        e->unk_2b = e->unk_3e;
        e->unk_3f = 6;
        func_020859e0(e, anim);
        func_02085f80(0x31);
    } else {
        func_020849f4(e, data_020d1a34);
    }
}
