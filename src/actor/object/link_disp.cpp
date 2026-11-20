#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"


// link_disp (0x02072684): updates the demo Link's sprite from the motion id of its player: bit 2 of the sprite word
// is set while the animation state is above 4 (facing), the low byte of the motion id (plus half the animation state
// below 0xa8) and the high byte select the frame; the animation is only restarted when they change.
void link_disp(Entity *e) {
    PlayerData *player = &playerWork[e->type];
    u16 motion = player->motionId;
    u8 low = motion;
    u8 high = motion >> 8;
    *(u32 *)&e->spriteSettings = (*(u32 *)&e->spriteSettings & ~4) | ((((u32)(e->animationState > 4)) << 31) >> 29);
    if (low < 0xa8) {
        low += e->animationState / 2u;
    }
    if (high == e->unk_1b && low == e->unk_23) {
        return;
    }
    e->unk_1b = high;
    func_020859a0(e, low, high);
}
