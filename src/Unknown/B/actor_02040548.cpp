#include "Unknown/B/Actor_0204001c.hpp"
#include "global.h"

ARM extern "C" void func_02040548(Entity *e) {
    func_02085980(e);
    if (V(e)->unk_64->unk_45 == 0) {
        e->unk_17 = 1;
    }
    u8 v = ((func_02084fd0(e, V(e)->unk_64) + 4) & 0x18) >> 3;
    if ((e->unk_2a & 3) != v) {
        e->unk_17 = 1;
    }
    func_02040674(e);
    if ((u16)(e->unk_30.HALF.HI - V(e)->unk_7c + 2) > 4 || (u16)(e->unk_34.HALF.HI - V(e)->unk_7e + 2) > 4) {
        e->unk_2b = func_02086080(e->unk_30.HALF.HI, e->unk_34.HALF.HI, V(e)->unk_7c, V(e)->unk_7e);
        func_020847a0(e);
    }
    if (e->unk_18 != 0) {
        e->unk_18--;
    }
    if (e->unk_18 == 0 && (e->unk_29 & 1)) {
        if (func_02040708(e)) {
            func_02040744(e);
        }
    }
    if (e->unk_58 != NULL) {
        func_02040790(e);
    }
    if (--e->unk_17 == 0) {
        func_020402e0(e);
    }
}

ARM extern "C" void func_02040674(Entity *e) {
    switch (e->unk_2a & 3) {
        case 0:
            V(e)->unk_7c = V(e)->unk_64->unk_30.HALF.HI;
            V(e)->unk_7e = V(e)->unk_64->unk_34.HALF.HI + 0x38;
            break;
        case 1:
            V(e)->unk_7c = V(e)->unk_64->unk_30.HALF.HI - 0x38;
            V(e)->unk_7e = V(e)->unk_64->unk_34.HALF.HI;
            break;
        case 2:
            V(e)->unk_7c = V(e)->unk_64->unk_30.HALF.HI;
            V(e)->unk_7e = V(e)->unk_64->unk_34.HALF.HI - 0x38;
            break;
        case 3:
            V(e)->unk_7c = V(e)->unk_64->unk_30.HALF.HI + 0x38;
            V(e)->unk_7e = V(e)->unk_64->unk_34.HALF.HI;
            break;
    }
}

ARM extern "C" BOOL func_02040708(Entity *e) {
    int r = func_02084ac0(e, 0xc, V(e)->unk_64);
    if (r & 0x80) {
        if ((e->unk_2a & 3) == ((r & 0x18) >> 3)) {
            return TRUE;
        }
    }
    return FALSE;
}

ARM extern "C" void func_02040744(Entity *e) {
    Entity *child = func_0204bdb8(8);
    if (child == NULL) {
        return;
    }
    child->unk_2b = (e->unk_2a & 3) << 3;
    child->unk_5e.b0 = 3;
    child->unk_54 = e;
    e->unk_29 = 0;
    e->unk_58 = child;
}

ARM extern "C" void func_02040790(Entity *e) {
    const s8 *p = data_020d2e3c + ((e->unk_2a & 3) * 2);
    func_02050390(e, e->unk_58, (s32)p[0] << 16, (s32)p[1] << 16);
}
