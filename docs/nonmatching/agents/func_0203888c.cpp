#include "Unknown/A/Boss_02038544.hpp"
#include "global.h"

// Nonmatching: remaining diff is register allocation and load order in the three blocks after 0x020388e4 (t->unk_14 test, 0x94-stride byte tables, else branch).
ARM extern "C" void func_0203888c(Entity *e) {
    if (V(e)->unk_6c != 0) {
        V(e)->unk_6c++;
    }
    e->unk_17--;
    if (data_0212c58c[e->unk_0a] & 0xcf3) {
        if (e->unk_17 < 8) {
            e->unk_17 = 0;
        } else {
            e->unk_17 -= 8;
        }
    }
    Entity *t = e->unk_58;
    if (t->unk_14 != 2 && t->unk_14 != 0xf && e->unk_17 != 0) {
        data_0212ceca[t->unk_0a * 0x94] |= 0x80;
        data_0212cee4[t->unk_0a * 0x94] = 1;
        func_0205031c(t, e);
        e->unk_5e.b0 = 3;
        e->unk_30.HALF.HI += data_020d1844[(data_0212c5bc & 0x1c) >> 1];
        e->unk_34.HALF.HI += data_020d1844[((data_0212c5bc & 0x1c) >> 1) + 1];
        return;
    }
    if (data_0212ceb2[e->unk_0b * 0x94] != 0) {
        return;
    }
    e->unk_14++;
    e->unk_2e = 2;
    e->unk_2b = ((t->unk_2a & 6) ^ 4) << 2;
    e->unk_0c += 0x40;
    e->unk_10 = 0x1c000;
    e->unk_3d = 0xdc;
    e->unk_5c = 0x21ff;
    data_0212ceca[t->unk_0a * 0x94] = 0;
}
