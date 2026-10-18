#include "enemy/actor_0204112c.h"
#include "global.h"

// Enemy_ScrollTowardLimit (0x0204198c): steps the scroll position and clamps it to the type's limits.
ARM void Enemy_ScrollTowardLimit(Entity *e) {
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
    func_0205063c(data_0212c574, e);
    UpdateAnimationSingleFrame(e);
}
