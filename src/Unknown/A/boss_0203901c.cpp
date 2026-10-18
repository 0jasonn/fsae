#include "Unknown/A/Boss_02038544.hpp"
#include "global.h"

ARM extern "C" void func_0203901c(Entity *e) {
    func_020847c8(e);
    func_020856cc(e, 0x1400);
    func_02085980(e);
    if ((e->unk_29 & 0x80) == 0) {
        return;
    }
    e->unk_14++;
    e->unk_17 = 0xc;
    func_020859e0(e, e->unk_2a + 8);
}
