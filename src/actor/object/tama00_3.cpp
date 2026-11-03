#include "engine/functions.h"

// Tama00 projectile, init. Address -> name:
//   0x0207c834 tama00_init (original name)

extern const u8 data_020dc968[]; // hitbox of the tama00 actor

// Starts the actor: next action, one step up, animation from the direction.
void tama00_init(Entity *e) {
    u32 settings;
    u32 newSettings;
    u8 anim;
    u8 action;
    s16 z;
    settings = *(u32 *)&e->spriteSettings;
    settings = (settings & ~3) | 1;
    anim = e->direction;
    action = e->action;
    e->action = action + 1;
    newSettings = (settings & ~0x30) | 0x10;
    z = e->z.HALF.HI;
    e->z.HALF.HI = z - 2;
    e->unk_2e = 2;
    e->unk_23 = 0;
    *(u32 *)&e->spriteSettings = newSettings;
    e->hitbox = data_020dc968;
    anim = (u8)(anim >> 4);
    InitAnimationForceUpdate(e, anim);
}
