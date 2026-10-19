#include "enemy/actor_020407c8.h"
#include "global.h"

ARM void em26_move(Entity *e) {
    V(e)->unk_7e--;
    if (V(e)->unk_7e == 0) {
        KemuriSet();
        BubbleReset(e);
        PutObjWork(e);
        return;
    }
    func_020847c8(e);
    UpdateAnimationSingleFrame(e);
    if (UpdateGravity(e, 0x1800) == 0) {
        jumpInit(e);
    }
}

ARM void em26_div(Entity *e) {
    Entity *a = GetObjWork();
    if (a == NULL) {
        return;
    }
    Entity *b = GetObjWork2();
    if (b == NULL) {
        return;
    }
    childInit(e, a);
    a->x.HALF.HI -= 4;
    a->parent = b;
    a->direction = (e->unk_3e - 2) & 0x1f;
    childInit(e, b);
    b->x.HALF.HI += 4;
    b->parent = a;
    b->direction = (e->unk_3e + 2) & 0x1f;
    Entity *other = GetSetWork(0xf, 2, 0);
    if (other != NULL) {
        ObjPosCopy(e, other);
    }
    PutObjWork(e);
}
