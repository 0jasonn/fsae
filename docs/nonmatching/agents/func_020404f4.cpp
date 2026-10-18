#include "Unknown/B/Actor_0204001c.hpp"
#include "global.h"

// Non-matching: the compiler keeps the constant 5 in r4 (push {r4, lr}) where the original keeps r1/r2 for the anim temp; register allocation differs.
ARM extern "C" void func_020404f4(Entity *e) {
    if (--e->unk_17 != 0) {
        return;
    }
    int anim = (e->unk_2a & 3) + 8;
    e->unk_14 = 5;
    e->unk_17 = 0x80;
    e->unk_18 = 0x10;
    e->unk_0c = 0x100;
    e->unk_2a = anim;
    func_020859e0(e, anim);
}
