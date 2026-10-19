#include "enemy/em26.h"
#include "global.h"

ARM void Em26(Entity *e) {
    func_02084700(e);
    Entity *target = func_020849c8(e);
    if (target != NULL) {
        if (!(e->unk_3c & 0x80) && e->timer == 1) {
            BubbleReset(e);
        }
        func_02084ab8(e, target);
        return;
    }
    data_020d31b8[func_02084a30(e)](e);
}

ARM void em26_normal(Entity *e) {
    data_020d31a8[e->action](e);
}

ARM void em26_damage(Entity *e) {
    if (e->health != 0 && e->health != 0xc) {
        e->action = 3;
        e->unk_42 = 0;
    }
    GenericKnockback(e, data_020d31b8);
}

ARM void em26_die(Entity *e) {
    if (GetEnemyWork(0x26) != NULL) {
        BubbleReset(e);
    }
    EmDie(e);
}
