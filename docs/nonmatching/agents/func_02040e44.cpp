#include "Unknown/B/Actor_020407c8.hpp"
#include "global.h"

// Non-matching: mwcc hoists the data_020d3224 load and the 3 constant differently (ldr r3 before orr lr in the original).
ARM extern "C" void func_02040e44(Entity *e) {
    e->unk_14 = 1;
    e->unk_2e = 3;
    e->unk_1c.b0 = 1;
    e->unk_1c.b4 = 1;
    e->unk_38.HALF.HI = e->unk_2e - 5;
    e->unk_48 = data_020d3224;
    V(e)->unk_7e = 0x12c;
    func_020859e0(e, 1);
}

