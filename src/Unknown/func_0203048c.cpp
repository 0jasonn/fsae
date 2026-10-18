#include "Unknown/Entity.hpp"
#include "global.h"

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
