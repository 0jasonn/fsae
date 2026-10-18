#include "Unknown/Entity.hpp"
#include "global.h"

extern const s8 data_020d07a0[];

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
