#include "Unknown/Boss_02036ca4.hpp"
#include "global.h"

ARM extern "C" BOOL func_0203808c(Entity *e) {
    Entity *a;
    Entity *b;
    if ((a = func_0204bcc8()) != NULL && (b = func_0204bd00()) != NULL) {
        a->unk_08 = 3;
        b->unk_08 = 3;
        a->unk_09 = 0x30;
        b->unk_09 = 0x30;
        a->unk_0b = 0;
        b->unk_0b = 1;
        a->unk_2b = 0xa0;
        b->unk_2b = 0x60;
        a->unk_54 = e;
        b->unk_54 = e;
        a->unk_58 = b;
        b->unk_58 = a;
        func_0205031c(e, a);
        func_0205031c(e, b);
        func_0204c178(4, a);
        func_0204c178(4, b);
        return TRUE;
    }
    return FALSE;
}

ARM extern "C" void func_02038138(Entity *e) {
    e->unk_14 = 0xf;
    V(e)->unk_71 = data_020f26a8[V(e)->unk_71][func_0208455c() & 7];
    if (V(e)->unk_71 == 0xff) {
        V(e)->unk_71 = func_0208455c() & 1;
    }
    V(e)->unk_70 = data_020cf9b8[V(e)->unk_71];
}

ARM extern "C" void func_02038194(Entity *e) {
    V(e)->unk_74 = data_020d1464[func_0208455c() & 3];
    V(e)->unk_78 = *V(e)->unk_74++;
    V(e)->unk_7a = *V(e)->unk_74++;
    e->unk_2b = *V(e)->unk_74++;
    V(e)->unk_7e = 0x80;
}

ARM extern "C" int func_020381ec(Entity *e) {
    if (V(e)->unk_7e != 0) {
        V(e)->unk_7e--;
    }
    if (!(data_020d1450[V(e)->unk_7e >> 4] & data_0212c5bc)) {
        func_02086200(e, func_02086080(e->unk_30.HALF.HI, e->unk_34.HALF.HI, (s16)V(e)->unk_78, (s16)V(e)->unk_7a));
    }
    func_0204fd40(e);
    func_02060a70(e);
    if ((u16)(V(e)->unk_78 - e->unk_30.HALF.HI + 2) <= 4 && (u16)(V(e)->unk_7a - e->unk_34.HALF.HI + 2) <= 4) {
        if (*V(e)->unk_74 == 0xffff) {
            return 0;
        }
        V(e)->unk_78 = *V(e)->unk_74++;
        V(e)->unk_7a = *V(e)->unk_74++;
        e->unk_2b = *V(e)->unk_74++;
        V(e)->unk_7e = 0x80;
        return 2;
    }
    return 1;
}
