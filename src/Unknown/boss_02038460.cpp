#include "Unknown/Boss_02036ca4.hpp"
#include "global.h"

ARM extern "C" void func_02038460(Entity *e) {
    V(e)->unk_74 = data_020d1474[func_0208455c() & 3];
    V(e)->unk_78 = *V(e)->unk_74++;
    V(e)->unk_7a = *V(e)->unk_74++;
    e->unk_2b = *V(e)->unk_74++;
    V(e)->unk_7e = 0x80;
}

ARM extern "C" int func_020384b8(Entity *e) {
    u8 hp = e->unk_45;
    u8 difficulty = data_0212c7c8.unk_3;
    int result = 0;
    if (((const u8 *)data_020d1432)[difficulty * 2] > hp) {
        result = 1;
        if (((const u8 *)data_020d1432)[difficulty * 2 + 1] > hp) {
            result = 2;
        }
    }
    return result;
}

ARM extern "C" void func_020384f8(void) {
    for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
        data_0212ceb0[i].unk_14 = 1;
    }
    func_020547ec();
}
