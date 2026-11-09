#include "engine/functions.h"
#include "engine/player.h"
#include "game/agent_a.h"

// areacheck2 (0x0202caa0): 0 while the single-player Link is inside the 0x30 x 0x24 box
// centred on the entity, 1 otherwise.
int areacheck2(Entity *e) {
    u8 index = *Knife_Single_SinglePlay_GetInstance();
    Entity *target = playerWork[index].entity;

    if ((u32)(target->x.HALF.HI - e->x.HALF.HI + 0x18) <= 0x30 &&
        (u32)(target->y.HALF.HI - e->y.HALF.HI + 0x12) <= 0x24) {
        return FALSE;
    }
    return TRUE;
}
