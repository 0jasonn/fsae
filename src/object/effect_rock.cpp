#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"
#include "object/effectdecls.h"

// effect_rock family (module effect_rock), 0x0206e5fc .. 0x0206e618 (dispatcher) and 0x0206e618 .. 0x0206e688 (init).
// Address -> name: 0x0206e5fc effect_rock, 0x0206e618 effect_rock_init, 0x0206e688 effect_rock_move

// Action table of effect_rock, effectRockTable
extern const EntityFunc effectRockTable[];

ARM void effect_rock(Entity *e) {
    effectRockTable[e->action](e);
}

ARM void effect_rock_init(Entity *e) {
    u8 action = e->action;

    e->action = action + 1;
    e->spriteSettings.b14 = 3;
    e->spriteSettings.b30 = 1;
    e->timer = 0;
    e->subtimer = 0;
    effectPhaseTable[e->type2] = e->timer - 10;
    e->x.HALF.HI = 0xe0;
    e->y.HALF.HI = 0x40;
    if (e->type2 == 7) {
        e->x.HALF.HI = 0xff;
    }
    InitAnimationForceUpdate(e, e->type);
}
