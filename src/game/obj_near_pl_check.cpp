#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "game/obj_near_pl_check.h"

// ObjNearPlCheck (0x0205076c): index of the player whose entity overlaps e (box width x height) and has the smallest
// distance value (sum of the negated coordinate differences, compared as u16), or 0xff when no player overlaps.
int ObjNearPlCheck(Entity *e, int width, int height) {
    u32 nearestDist;
    u8 i;
    u8 nearest;
    nearest = 0xff;
    nearestDist = 0xffff;
    for (i = 0; i < gameState.playerCount; i++) {
        if (func_02085a88(e, playerWork[i].entity, width, height)) {
            s16 diffY = playerWork[i].entity->y.HALF.HI - e->y.HALF.HI;
            s16 diffX = playerWork[i].entity->x.HALF.HI - e->x.HALF.HI;
            u16 dist = (s16)(-diffX) + (s16)(-diffY);
            if (nearestDist > dist) {
                nearestDist = dist;
                nearest = i;
            }
        }
    }
    return nearest;
}
