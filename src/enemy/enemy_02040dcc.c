#include "enemy/actor_020407c8.h"
#include "global.h"

ARM void func_02040dcc(Entity *e) {
    func_02084700(e);
    data_020d322c[func_02084a30(e)](e);
}

ARM void func_02040dfc(Entity *e) {
    data_020d321c[e->action](e);
}

ARM void func_02040e18(Entity *e) {
    GenericKnockback(e, data_020d322c);
}

ARM void func_02040e2c(Entity *e) {
    func_02040f00(e);
    func_02045ac0(e);
}
