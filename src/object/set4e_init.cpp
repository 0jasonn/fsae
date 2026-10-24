#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Set4e actor, init (module set4e). Address -> name:
//   0x0205e63c set4e_init (name from symbols.txt)
//   (Set4e dispatcher is in set4e_1.cpp, set4e_move at 0x0205e714 is in set4e_2.cpp)

ARM void set4e_init(Entity *e) {
    e->layer = 0x8000;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b30 = 1;
    e->action = e->action + 1;

    switch (func_02083c84(e)) {
    case 0xcd:
        e->x.HALF.HI += 0x10;
        e->y.HALF.HI += 0x10;
        break;
    case 0xce:
        e->y.HALF.HI += 0x10;
        break;
    case 0xcf:
        e->x.HALF.HI += 0x10;
        break;
    case 0xd0:
        break;
    default:
        PutObjWork(e);
        return;
    }
    e->x.HALF.HI = e->x.HALF.HI & ~0xf;
    e->y.HALF.HI = e->y.HALF.HI & ~0xf;
    InitAnimationForceUpdate(e, 0);
    kanaamiRew(e, 0xd1);
    set4e_move(e);
}
