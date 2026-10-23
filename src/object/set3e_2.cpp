#include "engine/functions.h"
#include "global.h"
#include "object/set3e.h"

// Set3e actor, second unit (module set3e). Address -> name:
//   0x0205dc1c set3e_move

ARM void set3e_move(Entity *e) {
    u8 code;

    if (e->speed < 0x300) {
        e->speed += 0x10;
    }
    func_020852ec(e);
    code = func_02083cdc(e);
    if (code == 0x22) {
        return;
    }
    if (code == 0x43) {
        EffectSet(e, 0, 0);
        PutObjWork(e);
        return;
    }
    EffectSet(e, 4, 0);
    PutObjWork(e);
}
