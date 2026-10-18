#include "Unknown/Object_02033708.hpp"
#include "global.h"

ARM extern "C" void func_02033708(Entity *e) {
    if (e->unk_14 != 0 && V(e)->unk_7c->unk_45 == 0) {
        func_0204be88(e);
        return;
    }
    data_020d101c[e->unk_14](e);
}
