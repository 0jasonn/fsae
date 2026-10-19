#include "engine/functions.h"
#include "enemy/em28.h"
#include "global.h"

// em29_kakudai (0x0204198c): steps the scroll position and clamps it to the type's limits.
ARM void em29_kakudai(Entity *e) {
    V(e)->subPosX -= 0x18;
    V(e)->subPosY -= 0x10;
    u16 limitX = em29_scrollLimitsOut[e->type * 2];
    u8 clampedX = 0;
    if (V(e)->subPosX <= limitX) {
        V(e)->subPosX = limitX;
        clampedX = 1;
    }
    u16 limitY = em29_scrollLimitsOut[e->type * 2 + 1];
    if (V(e)->subPosY <= limitY) {
        V(e)->subPosY = limitY;
        if (clampedX) {
            e->action = 2;
        }
    }
    scrollArgs[0] = V(e)->subPosX;
    scrollArgs[1] = V(e)->subPosY;
    scrollArgs[2] = 0;
    ObjAffineSet2((const KnifeObjAffineSrcData *)scrollArgs, e);
    UpdateAnimationSingleFrame(e);
}
