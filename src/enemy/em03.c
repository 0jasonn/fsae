#include "enemy/em03.h"
#include "global.h"

ARM void Em03(Entity *e) {
    func_02084700(e);
    int r = func_020849c8(e);
    if (r != 0) {
        if (!(e->unk_3c & 0x80) && e->timer == 1) {
            aibou_check(e);
        }
        func_02084ab8(e, r);
    } else {
        data_020d1868[func_02084a30(e)](e);
    }
}

ARM void em03_normal(Entity *e) {
    data_020d1880[e->action](e);
}
