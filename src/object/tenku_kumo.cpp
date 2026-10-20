#include "engine/functions.h"
#include "global.h"
#include "object/tenku_kumo.h"

// tenku_kumo family (module tenku_kumo), 0x0206d704 .. 0x0206d7dc.
// Address -> name: 0x0206d704 tenku_kumo, 0x0206d720 tenku_kumo_init, 0x0206d7a0 tenku_kumo_move

ARM void tenku_kumo(Entity *e) {
    tenkuKumoTable[e->action](e);
}

ARM void tenku_kumo_init(Entity *e) {
    int nextAction = e->action + 1;
    u32 settings = *(u32 *)&e->spriteSettings;

    settings = (settings & ~3) | 1;
    settings = (settings & ~0xc000) | 0x8000;
    settings = (settings & ~0xc0000000) | 0x80000000;
    settings = (settings & ~0xf0000) | 0x50000;
    *(u32 *)&e->spriteSettings = settings;
    if (e->type != 4) {
        *(u32 *)&e->spriteSettings = (settings & ~0xc00) | 0x400;
    }
    e->action = nextAction;
    set_pos(e);
    e->x.HALF.HI += *(s16 *)(data_021349c0 + 0x26);
    InitAnimationForceUpdate(e, e->type);
}

ARM void tenku_kumo_move(Entity *e) {
    set_pos(e);
    e->x.HALF.HI += *(s16 *)(data_021349c0 + 0x26);
    if (ZeldaFadeFlagGet() == 0) {
        *(u32 *)&e->spriteSettings &= ~0xc00;
    }
}
