#include "Unknown/A/Boss_02038544.hpp"
#include "global.h"

// Nonmatching: only register assignment differs (r3/r2/x locals and the three constant stores, 0x02038be0-0x02038c10).
ARM extern "C" void func_02038bbc(Entity *e) {
    if (e->unk_18 == 0) {
        u32 r = func_02084ac8(e, 0xc);
        if (r & 0x80) {
            int r3 = r & 0x18;
            int r2 = r3 >> 3;
            u8 x = r2;
            e->unk_14 = 3;
            e->unk_17 = 0x10;
            e->unk_0c = 0x1a0;
            e->unk_2b = r3;
            e->unk_2a = r2;
            func_020859e0(e, x + 4);
            return;
        }
    } else {
        e->unk_18--;
    }
    if (e->unk_17 == 0) {
        e->unk_14 = 1;
        return;
    }
    e->unk_17--;
    func_020847a0(e);
    func_02085980(e);
}
