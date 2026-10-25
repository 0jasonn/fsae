#include "engine/functions.h"
#include "global.h"
// func_020847c8 and func_02086044 come from engine/functions.h

// Functions in this file: em20_hanekaeri (0x0203eba4).

ARM void em20_hanekaeri(Entity *e) {
    func_020847c8(e);
    if (func_02086044(e, 0x1800) == 0) {
        e->action = 1;
        e->timer = 0x1e;
    }
}
