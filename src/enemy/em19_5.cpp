#include "engine/functions.h"
#include "global.h"
#include "enemy/em19.h"
#include "enemy/em19_4.h"

// Functions in this file: em19_move2 (0x0203e410).

ARM void em19_move2(Entity *e) {
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
    if ((e->direction & 8) != 0) {
        if ((e->x.HALF.HI & 0xf) == 8) {
            setActionAnim3(e);
        }
        return;
    }
    if ((e->y.HALF.HI & 0xf) == 8) {
        setActionAnim3(e);
    }
}
