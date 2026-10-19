#include "enemy/actor_020407c8.h"
#include "global.h"

ARM void em27_move(Entity *e) {
    func_020847dc(e);
    UpdateAnimationSingleFrame(e);
    V(e)->unk_7e--;
    if (V(e)->unk_7e == 0) {
        cbubbleReset(e);
        PutObjWork(e);
        return;
    }
    if (V(e)->unk_7e >= 0x2d) {
        return;
    }
    e->spriteSettings.b0 ^= 1;
}

ARM void cbubbleReset(Entity *e) {
    if (e->parent != NULL) {
        e->parent->parent = NULL;
        return;
    }
    BubbleReset(e);
}

ARM void func_02040f20(Entity *e) {
    EnemyFunctionHandler(e, data_020d3334);
}
