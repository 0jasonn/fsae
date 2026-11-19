#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em2a.h"
#include "actor/enemy/em2a_api.h"

extern const u8 *em2a_landTimerTables[]; // em2a_landTimerTables: per type table of the four landing subtimers

// em2a_move2land (0x0203120c): once the jump animation reports its frame, picks a random side and a subtimer from the
// type's table, starts the landing and plays the sound of the form (the shadow form hides instead).
void em2a_move2land(Entity *e) {
    const u8 *table;

    UpdateAnimationSingleFrame(e);
    if (e->frame == 0) {
        return;
    }
    e->action = 4;
    e->type2 = Random() & 1;
    if (e->type2 != 0) {
        e->direction = 0x10;
    } else {
        e->direction = 0;
    }
    e->timer = 1;
    V(e)->extraHop = 1;
    table = em2a_landTimerTables[e->type - 1];
    e->subtimer = table[Random() & 3];
    e->speed = 0x100;
    e->zVelocity = 0x30000;
    InitAnimationForceUpdate(e, (u8)((e->type - 1) * 0xa + 1));
    if (e->type == 2) {
        V(e)->shadowLandMask = 0;
        e->statusFlags &= 0x7f;
        e->spriteSettings.b0 = 0;
        shadowSet(e);
        return;
    }
    if (e->type == 3) {
        V(e)->flashPlayer = func_02085608();
        SoundReq(0xa1);
    }
    SoundReq(0x31);
}
