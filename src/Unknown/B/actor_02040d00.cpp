#include "Unknown/B/Actor_020407c8.hpp"
#include "global.h"

ARM extern "C" void func_02040d00(Entity *e) {
    Entity *c = func_0204bd80(0x26);
    if (c == NULL) {
        return;
    }
    c->unk_30.HALF.HI = V(e)->unk_70;
    c->unk_34.HALF.HI = V(e)->unk_72;
    c->unk_52 = e->unk_52;
    V(c)->unk_74 = V(e)->unk_74;
    V(c)->unk_76 = V(e)->unk_76;
    V(c)->unk_78 = V(e)->unk_78;
    V(c)->unk_7a = V(e)->unk_7a;
    V(c)->unk_7c = 0x258;
    func_0208ae30(c);
}
