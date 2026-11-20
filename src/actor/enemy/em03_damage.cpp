#include "engine/functions.h"
#include "actor/enemy/em03.h"
#include "global.h"

// em03_damage (0x020385cc): hit by something. A hit with contact flags 0x80 (the partner grabbing it) latches onto the
// attacker: it records the attacker's table entry, starts the carried action (6) and keeps the attacker as child.
// Any other hit goes through the normal knockback.
void em03_damage(Entity *e) {
    Entity *attacker;

    if (e->health == 0) {
        aibou_check(e);
    }
    if (e->contactFlags == 0x80) {
        attacker = e->contactedEntity;
        e->unk_5c = data_020d1820[attacker->type];
        e->action = 6;
        e->timer = 0xf0;
        e->unk_2e = 0;
        e->z.HALF.HI = 0;
        e->child = attacker;
        if (V(e)->unk_6c != 0) {
            V(e)->unk_6c++;
        }
        InitAnimationForceUpdate(e, 0);
    } else {
        GenericKnockback(e, em03_noPartnerActions);
    }
}
