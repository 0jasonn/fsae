#include "Unknown/B/Actor_020407c8.hpp"
#include "global.h"

// Non-matching: mwcc assigns the constants 3/0x27/0xf8 to r3/r2/r1 where the original uses ip/r3/r2 (r1 never used).
ARM extern "C" void func_02040d60(Entity *e, Entity *c) {
    c->unk_08 = 3;
    c->unk_09 = 0x27;
    c->unk_3d = 0xf8;
    V(c)->unk_64 = V(e)->unk_64;
    V(c)->unk_70 = V(e)->unk_70;
    V(c)->unk_72 = V(e)->unk_72;
    V(c)->unk_74 = V(e)->unk_74;
    V(c)->unk_76 = V(e)->unk_76;
    V(c)->unk_78 = V(e)->unk_78;
    V(c)->unk_7a = V(e)->unk_7a;
    func_02045b74();
    func_0204c178(4, c);
}
