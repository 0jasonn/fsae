#include "enemy/actor_020407c8.h"
#include "global.h"

ARM void func_02040ad8(Entity *e) {
    V(e)->unk_7e--;
    if (V(e)->unk_7e == 0) {
        func_020768d8();
        func_02040d00(e);
        DeleteEntity(e);
        return;
    }
    func_020847c8(e);
    UpdateAnimationSingleFrame(e);
    if (UpdateGravity(e, 0x1800) == 0) {
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
    a->x.HALF.HI -= 4;
    a->parent = b;
    a->direction = (e->unk_3e - 2) & 0x1f;
    func_02040d60(e, b);
    b->x.HALF.HI += 4;
    b->parent = a;
    b->direction = (e->unk_3e + 2) & 0x1f;
    Entity *other = CreateFx(0xf, 2, 0);
    if (other != NULL) {
        CopyPosition(e, other);
    }
    DeleteEntity(e);
}
