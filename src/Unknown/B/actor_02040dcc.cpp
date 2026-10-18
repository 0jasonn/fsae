#include "Unknown/B/Actor_020407c8.hpp"
#include "global.h"

ARM extern "C" void func_02040dcc(Entity *e) {
    func_02084700(e);
    data_020d322c[func_02084a30(e)](e);
}

ARM extern "C" void func_02040dfc(Entity *e) {
    data_020d321c[e->unk_14](e);
}

ARM extern "C" void func_02040e18(Entity *e) {
    func_020849f4(e, data_020d322c);
}

ARM extern "C" void func_02040e2c(Entity *e) {
    func_02040f00(e);
    func_02045ac0(e);
}
