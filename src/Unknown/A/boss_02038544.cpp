#include "Unknown/A/Boss_02038544.hpp"
#include "global.h"

ARM extern "C" void func_02038544(Entity *e) {
    func_02084700(e);
    int r = func_020849c8(e);
    if (r != 0) {
        if (!(e->unk_3c & 0x80) && e->unk_17 == 1) {
            func_02038a88(e);
        }
        func_02084ab8(e, r);
    } else {
        data_020d1868[func_02084a30(e)](e);
    }
}

ARM extern "C" void func_020385b0(Entity *e) {
    data_020d1880[e->unk_14](e);
}
