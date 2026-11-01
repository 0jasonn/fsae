#include "engine/functions.h"
#include "actor/enemy/em26.h"
#include "global.h"

void Em27(Entity *e) {
    func_02084700(e);
    em27_mainTable[func_02084a30(e)](e);
}

void em27_normal(Entity *e) {
    em27_normalTable[e->action](e);
}

void func_02040e18(Entity *e) {
    GenericKnockback(e, em27_mainTable);
}

void em27_die(Entity *e) {
    cbubbleReset(e);
    EmDie(e);
}
