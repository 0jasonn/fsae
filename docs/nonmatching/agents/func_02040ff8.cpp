#include "Unknown/B/Actor_020407c8.hpp"
#include "global.h"

// Non-matching: the original shares one smulbb table index and table load after the if/else; mwcc emits a predicated else and a plain mul.
ARM extern "C" void func_02040ff8(Entity *e) {
    if (e->unk_4c->unk_0a < 3) {
        u8 idx;
        if (func_0208de54(func_0208da4c()) == 0) {
            idx = *func_02093b5c();
        } else {
            idx = e->unk_4c->unk_0a;
        }
        V(e)->unk_64 = data_0212ceb0[idx].unk_28;
    }
    func_020849f4(e, data_020d3334);
}
