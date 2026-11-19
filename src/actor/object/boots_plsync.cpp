// boots_plsync (0x020246b4): copies the template's sprite flip to the boots, inverted when bit 1 of animationState is set.
#include "engine/functions.h"
#include "global.h"
#include "engine/decls_a.h"

extern const s8 data_020ce52c[];
extern const s8 data_020ce51c[];

void boots_plsync(Entity *e, Entity *tmpl) {
    s8 *hitbox;
    u8 anim;
    int index;

    e->animationState = tmpl->animationState & 0xe;
    if (e->animationState & 2) e->spriteSettings.flipX = tmpl->spriteSettings.flipX ^ 1; else e->spriteSettings.flipX = tmpl->spriteSettings.flipX;
    if (tmpl->unk_23 >= 0x9c && tmpl->unk_23 < 0xa0) {
        e->unk_21 = tmpl->unk_21 - 8;
    } else {
        e->unk_21 = 0xff;
    }
    ((s8 *)e->hitbox)[0] = data_020ce52c[(e->animationState >> 1) * 4];
    ((s8 *)e->hitbox)[1] = data_020ce52c[(e->animationState >> 1) * 4 + 1];
    ((s8 *)e->hitbox)[6] = data_020ce52c[(e->animationState >> 1) * 4 + 2];
    ((s8 *)e->hitbox)[7] = data_020ce52c[(e->animationState >> 1) * 4 + 3];
    anim = e->animationState & 0xe;
    func_0208a224(e, 0, data_020ce51c[anim], data_020ce51c[anim + 1]);
}
