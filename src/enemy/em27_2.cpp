#include "engine/functions.h"
#include "enemy/em26.h"
#include "global.h"

ARM void em27_move(Entity *e) {
    func_020847dc(e);
    UpdateAnimationSingleFrame(e);
    V(e)->lifeTimer--;
    if (V(e)->lifeTimer == 0) {
        cbubbleReset(e);
        PutObjWork(e);
        return;
    }
    if (V(e)->lifeTimer >= 0x2d) {
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
    EnemyFunctionHandler(e, em27_handlerTable);
}
