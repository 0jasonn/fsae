#include "Unknown/A/Boss_02038544.hpp"
#include "global.h"

ARM extern "C" void func_02038c58(Entity *e) {
    if (e->unk_17 != 0) {
        e->unk_17--;
        return;
    }
    func_02085980(e);
    if (func_020847a0(e) != 0) {
        return;
    }
    e->unk_14 = 1;
    e->unk_0c = 0x80;
    e->unk_18 = 0x14;
    func_020859e0(e, e->unk_2a);
}

ARM extern "C" void func_02038cb0(Entity *e) {
    func_02084a7c(e, data_020d1a34);
}

ARM extern "C" void func_02038cc4(Entity *e) {
    data_020d19ec[e->unk_0a][e->unk_14](e);
}
