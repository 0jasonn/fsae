#include "Unknown/B/Actor_020407c8.h"
#include "global.h"

ARM void func_020407c8(Entity *e) {
    func_02084700(e);
    Entity *target = func_020849c8(e);
    if (target != NULL) {
        if (!(e->unk_3c & 0x80) && e->timer == 1) {
            func_02040d00(e);
        }
        func_02084ab8(e, target);
        return;
    }
    data_020d31b8[func_02084a30(e)](e);
}

ARM void func_02040834(Entity *e) {
    data_020d31a8[e->action](e);
}

ARM void func_02040850(Entity *e) {
    if (e->health != 0 && e->health != 0xc) {
        e->action = 3;
        e->unk_42 = 0;
    }
    GenericKnockback(e, data_020d31b8);
}

ARM void func_02040880(Entity *e) {
    if (CreateEnemy(0x26) != NULL) {
        func_02040d00(e);
    }
    func_02045ac0(e);
}
