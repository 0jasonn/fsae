#include "engine/functions.h"
#include "global.h"

// Cercle movers (module cercle). Address -> name (original names):
//   0x02035ff8 cercleMoveC

// cercleMoveC (0x02035ff8): turns to face the parent, sets the animation from the facing direction,
// then steps twice (direction is advanced by 8 in between).
ARM void cercleMoveC(Entity *e) {
    int facing = GetFacingDirection(e->parent, e);
    u8 anim = ((facing & 0xff) + 2) >> 2 & 7;
    e->direction = facing;
    if (e->animationState != anim) {
        e->animationState = anim;
        InitAnimationForceUpdate(e, anim + 0x14);
    }
    MoveDir(e);
    e->direction = (e->direction + 8) & 0x1f;
    MoveDir(e);
}
