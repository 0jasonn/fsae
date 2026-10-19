#include "engine/functions.h"
#include "enemy/em03.h"
#include "global.h"

ARM void Em03(Entity *e) {
    func_02084700(e);
    Entity *partner = func_020849c8(e);
    if (partner != 0) {
        if (!(e->unk_3c & 0x80) && e->timer == 1) {
            aibou_check(e);
        }
        func_02084ab8(e, partner);
    } else {
        em03_noPartnerActions[func_02084a30(e)](e);
    }
}

ARM void em03_normal(Entity *e) {
    em03_normalActions[e->action](e);
}
