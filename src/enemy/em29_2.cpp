#include "engine/functions.h"
#include "enemy/em28.h"
#include "global.h"

// em29_kakudai (0x0204198c): steps the scroll position and clamps it to the type's limits.
ARM void em29_kakudai(Entity *e) {
    V(e)->subPosX -= 0x18;
    V(e)->subPosY -= 0x10;
    u16 limitX = data_020d347a[e->type * 2];
    u8 clampedX = 0;
    if (V(e)->subPosX <= limitX) {
        V(e)->subPosX = limitX;
        clampedX = 1;
    }
    u16 limitY = data_020d347a[e->type * 2 + 1];
    if (V(e)->subPosY <= limitY) {
        V(e)->subPosY = limitY;
        if (clampedX) {
            e->action = 2;
        }
    }
    data_0212c574[0] = V(e)->subPosX;
    data_0212c574[1] = V(e)->subPosY;
    data_0212c574[2] = 0;
    ObjAffineSet2((const KnifeObjAffineSrcData *)data_0212c574, e);
    UpdateAnimationSingleFrame(e);
}
