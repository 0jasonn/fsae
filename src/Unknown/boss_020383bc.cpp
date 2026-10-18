#include "Unknown/Boss_02036ca4.hpp"
#include "global.h"

ARM extern "C" void func_020383bc(Entity *e) {
    V(e)->unk_74 = data_020d1448[func_0208455c() & 1];
    V(e)->unk_78 = *V(e)->unk_74++;
    V(e)->unk_7a = *V(e)->unk_74++;
    e->unk_2b = *V(e)->unk_74++;
    V(e)->unk_7e = 0x80;
}

