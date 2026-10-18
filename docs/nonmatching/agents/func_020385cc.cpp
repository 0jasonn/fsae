#include "Unknown/A/Boss_02038544.hpp"
#include "global.h"

// Nonmatching: remaining diff is register/literal scheduling around the t/w locals and a reused zero for the func_020859e0 call (0x020385f0-0x0203864c).
ARM extern "C" void func_020385cc(Entity *e) {
    if (e->unk_45 == 0) {
        func_02038a88(e);
    }
    if (e->unk_41 == 0x80) {
        Entity *t = e->unk_4c;
        u16 v = V(e)->unk_6c;
        u16 w = data_020d1820[t->unk_0a];
        if (v != 0) {
            V(e)->unk_6c = v + 1;
        }
        e->unk_2e = 0;
        e->unk_38.HALF.HI = 0;
        e->unk_5c = w;
        e->unk_14 = 6;
        e->unk_17 = 0xf0;
        e->unk_58 = t;
        func_020859e0(e, 0);
        return;
    }
    func_020849f4(e, data_020d1868);
}
