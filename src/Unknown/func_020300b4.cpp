#include "Unknown/Entity.hpp"
#include "global.h"

ARM extern "C" void func_020300b4(Entity *e, int dir) {
    if ((e->unk_2a & 0xe) == dir) {
        if ((e->unk_2b & 0xf) == 0 || (e->unk_2a & 1) == (e->unk_2b >> 4)) {
            return;
        }
        func_020859e0(e, e->unk_2a = dir + (e->unk_2b >> 4));
        return;
    }
    func_020859e0(e, e->unk_2a = dir + (e->unk_2a & 1));
}
