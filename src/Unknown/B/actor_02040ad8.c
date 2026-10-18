#include "Unknown/B/Actor_020407c8.h"
#include "global.h"

ARM void func_02040ad8(Entity *e) {
    V(e)->unk_7e--;
    if (V(e)->unk_7e == 0) {
        func_020768d8();
        func_02040d00(e);
        func_0204be88(e);
        return;
    }
    func_020847c8(e);
    func_02085980(e);
    if (func_020856cc(e, 0x1800) == 0) {
        func_02040be0(e);
    }
}

ARM void func_02040b3c(Entity *e) {
    Entity *a = func_0204bcc8();
    if (a == NULL) {
        return;
    }
    Entity *b = func_0204bd00();
    if (b == NULL) {
        return;
    }
    func_02040d60(e, a);
    a->unk_30.HALF.HI -= 4;
    a->unk_54 = b;
    a->unk_2b = (e->unk_3e - 2) & 0x1f;
    func_02040d60(e, b);
    b->unk_30.HALF.HI += 4;
    b->unk_54 = a;
    b->unk_2b = (e->unk_3e + 2) & 0x1f;
    Entity *other = func_02076858(0xf, 2, 0);
    if (other != NULL) {
        func_0205031c(e, other);
    }
    func_0204be88(e);
}
