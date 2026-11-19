#include "engine/functions.h"
#include "actor/enemy/em28_dir.h"
#include "global.h"

// bgcheck (0x02041498): 1 when both probe points on the leading edge of the hitbox, for the given direction
// (direction >> 3 selects up, right, down or left), are free of walls.
int bgcheck(Entity *e, u8 direction) {
    const u8 *box;
    u16 x1;
    u16 y1;
    u16 x2;
    u16 y2;
    switch (direction >> 3) {
        case 0:
            box = (const u8 *)e->hitbox;
            x1 = e->x.HALF.HI + box[4];
            x2 = e->x.HALF.HI - box[4];
            y1 = y2 = e->y.HALF.HI - box[5];
            break;
        case 1:
            box = (const u8 *)e->hitbox;
            x1 = x2 = e->x.HALF.HI + box[2];
            y1 = e->y.HALF.HI - box[3];
            y2 = e->y.HALF.HI + box[3];
            break;
        case 2:
            box = (const u8 *)e->hitbox;
            x1 = e->x.HALF.HI + box[4];
            x2 = e->x.HALF.HI - box[4];
            y1 = y2 = e->y.HALF.HI + box[5];
            break;
        case 3:
            box = (const u8 *)e->hitbox;
            x1 = x2 = e->x.HALF.HI - box[2];
            y1 = e->y.HALF.HI - box[3];
            y2 = e->y.HALF.HI + box[3];
            break;
    }
    if (func_02083d4c(((x1 - mapState.originX) >> 4) | (((y1 - mapState.originY) >> 4) << 6), e->layer) != 0 ||
        func_02083d4c(((x2 - mapState.originX) >> 4) | (((y2 - mapState.originY) >> 4) << 6), e->layer) != 0) {
        return 0;
    }
    return 1;
}

// getDushDir (0x020415f4): the dash direction check of em28. Returns 1 when the target stands within 0x14 pixels;
// otherwise it tracks the target's direction (re-aiming every 8 frames, or finishing a turn that is blocked or done).
int getDushDir(Entity *e) {
    u8 facing;
    u8 dir;
    if ((playerKeysPrev[V(e)->target->type] & 0x1000) != 0 || V(e)->target->health == 0) {
        em28_getdir(e);
        return 0;
    }
    if ((u16)(e->x.HALF.HI - V(e)->target->x.HALF.HI + 0x14) <= 0x28 && (u16)(e->y.HALF.HI - V(e)->target->y.HALF.HI + 0x14) <= 0x28) {
        return 1;
    }
    if (V(e)->turnActive != 0) {
        facing = GetFacingDirection(e, V(e)->target);
        if (((V(e)->turnStartDir - facing + 8) & 0x1f) > 0x10) {
            V(e)->turnActive = 0;
            V(e)->retargetDelay = 8;
            dir = (facing + 4) & 0x18;
            e->direction = dir;
            InitAnimationForceUpdate(e, e->animationState = dir >> 3);
        } else if (bgcheck(e, V(e)->turnStartDir) != 0) {
            V(e)->turnActive = 0;
            V(e)->retargetDelay = 8;
            dir = V(e)->turnStartDir;
            e->direction = dir;
            InitAnimationForceUpdate(e, e->animationState = dir >> 3);
        } else {
            V(e)->turnTimeout--;
            if (V(e)->turnTimeout == 0) {
                e->action = 1;
            }
        }
    } else if (V(e)->retargetDelay != 0) {
        V(e)->retargetDelay--;
    } else {
        V(e)->retargetDelay = 8;
        dir = (GetFacingDirection(e, V(e)->target) + 4) & 0x18;
        e->direction = dir;
        if (dir >> 3 != e->animationState) {
            InitAnimationForceUpdate(e, e->animationState = dir >> 3);
        }
    }
    return 0;
}
