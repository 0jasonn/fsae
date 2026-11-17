#include "engine/functions.h"
#include "global.h"
#include "actor/object/set41.h"

// set41_init (0x0206c3b4): type holds the kind (bits 0..2, 0 = visible from the start) and unk_16 (bits 3..7).
// counter starts at the timer and gets +0x1f4 when the timer is in set41Timers (offline play only).
void set41_init(Entity *e) {
    Vars_Set41 *v = VARS(Vars_Set41, e);
    Set41TimerList list;
    u32 i;

    e->unk_16 = (e->type >> 3) & 0x1f;
    e->type &= 7;
    if (e->type & 7) {
        e->action = 1;
    } else {
        e->spriteSettings.b0 = 1;
        func_02085fac(e);
        e->action = 3;
    }
    e->spriteSettings.b4 = 1;
    e->unk_2e = 4;
    e->z.HALF.HI -= 1;
    e->hitbox = set41Hitbox;
    v->typeBits = ParseTypeBits(e->type2);
    v->counter = e->timer;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        list = set41Timers;
        for (i = 0; i < 12; i++) {
            if (list.values[i] == e->timer) {
                v->counter += 0x1f4;
                break;
            }
        }
    }
    InitAnimationForceUpdate(e, 0);
}
