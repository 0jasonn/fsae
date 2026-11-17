#include "engine/functions.h"
#include "engine/player.h"
#include "game/joycdir.h"
#include "global.h"

// JoyCdirSet (0x02050200): turns the direction bits of the owning player's input (playerWork[e->type].unk_0d,
// 0xff = none) into e->animationState and sets bit 2 of the sprite word when the direction is past 4. Returns the
// new (or kept) animation state.
u8 JoyCdirSet(Entity *e) {
    u8 input = playerWork[e->type].unk_0d;
    if (input == 0xff) {
        return e->animationState;
    }
    u8 dir = (input & 0x1c) >> 2;
    if (dir & 1) {
        if (((dir + 1 - e->animationState) & 4) == 0) {
            return e->animationState;
        }
    }
    u32 flag = dir > 4;
    *(u32 *)&e->spriteSettings = (*(u32 *)&e->spriteSettings & ~4) | (flag << 31 >> 29);
    return e->animationState = dir & 6;
}
