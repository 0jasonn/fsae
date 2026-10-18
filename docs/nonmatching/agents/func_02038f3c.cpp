#include "Unknown/A/Boss_02038544.hpp"
#include "global.h"

// Nonmatching: only the placement of the 0xff mask differs (original stores unk_2b before masking the value passed on).
ARM extern "C" void func_02038f3c(Entity *e) {
    Entity *target = 0;
    if (e->unk_18 != 0) {
        e->unk_18--;
    } else {
        target = func_02084f98(e, 0x40, 0x30);
    }
    if (target != 0) {
        e->unk_14 = 4;
        int k = func_0204fdf0(e, target);
        e->unk_2b = k;
        e->unk_10 = 0x1c000;
        e->unk_0c = 0x180;
        e->unk_3c |= 0x10;
        e->unk_3f = 6;
        u8 v = func_02045a8c(k);
        if (v != 0xff) {
            e->unk_2a = v;
        }
        func_020859e0(e, e->unk_2a + 4);
        func_02085f80(0x31);
        return;
    }
    if (--e->unk_17 == 0) {
        e->unk_17 = (func_0208455c() & 0x1c) + 0x1e;
        func_02039278(e);
    }
    func_020847a0(e);
    func_02085980(e);
}
