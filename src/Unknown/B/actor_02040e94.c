#include "Unknown/B/Actor_020407c8.h"
#include "global.h"

ARM void func_02040e94(Entity *e) {
    func_020847dc(e);
    UpdateAnimationSingleFrame(e);
    V(e)->unk_7e--;
    if (V(e)->unk_7e == 0) {
        func_02040f00(e);
        DeleteEntity(e);
        return;
    }
    if (V(e)->unk_7e >= 0x2d) {
        return;
    }
    e->spriteSettings.b0 ^= 1;
}

ARM void func_02040f00(Entity *e) {
    if (e->parent != NULL) {
        e->parent->parent = NULL;
        return;
    }
    func_02040d00(e);
}

ARM void func_02040f20(Entity *e) {
    EnemyFunctionHandler(e, data_020d3334);
}
