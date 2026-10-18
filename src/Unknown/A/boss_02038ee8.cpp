#include "Unknown/A/Boss_02038544.hpp"
#include "global.h"

ARM extern "C" void func_02038ee8(Entity *e) {
    func_02085980(e);
    if ((e->unk_29 & 0x80) == 0) {
        return;
    }
    e->unk_14 = 1;
    e->unk_17 = 1;
    e->unk_2a = 0;
    e->unk_0c = 0x80;
    e->unk_3c &= 0xef;
    e->unk_3f = 9;
    func_020859e0(e, 0);
}
