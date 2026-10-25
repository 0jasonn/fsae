#include "engine/functions.h"
#include "global.h"
#include "enemy/em18_2.h"

// Functions in this file: em18_die (0x0203dc98), em18_encntdie (0x0203dcb0), em18_type0 (0x0203dcc8).

ARM void em18_die(Entity *e) {
    delprtInfo(e);
    EmDie(e);
}

ARM void em18_encntdie(Entity *e) {
    delprtInfo(e);
    func_02084a20(e);
}

ARM void em18_type0(Entity *e) {
    em18_type0Table[e->action](e);
}
