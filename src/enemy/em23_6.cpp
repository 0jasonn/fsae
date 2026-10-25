#include "engine/functions.h"
#include "global.h"
#include "enemy/em23.h"
#include "enemy/em23_6.h"

// Functions in this file: Em23 (0x0203fa4c).

ARM void Em23(Entity *e) {
    if (e->type2 == 0) {
        func_02084700(e);
        em23_stateTable[func_02084a30(e)](e);
        fuwafuwa(e);
        UpdateAnimationSingleFrame(e);
        func_0208ae30(e);
        e->spriteSettings.b30 = 1;
        e->spriteSettings.b14 = 1;
    } else {
        enrinMove(e);
    }
}
