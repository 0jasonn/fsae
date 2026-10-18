#include "Unknown/B/Actor_020407c8.hpp"
#include "global.h"

ARM extern "C" void func_02040e94(Entity *e) {
    func_020847dc(e);
    func_02085980(e);
    V(e)->unk_7e--;
    if (V(e)->unk_7e == 0) {
        func_02040f00(e);
        func_0204be88(e);
        return;
    }
    if (V(e)->unk_7e >= 0x2d) {
        return;
    }
    e->unk_1c.b0 ^= 1;
}

ARM extern "C" void func_02040f00(Entity *e) {
    if (e->unk_54 != NULL) {
        e->unk_54->unk_54 = NULL;
        return;
    }
    func_02040d00(e);
}

ARM extern "C" void func_02040f20(Entity *e) {
    func_02084a7c(e, data_020d3334);
}
