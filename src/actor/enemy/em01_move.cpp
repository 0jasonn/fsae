#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em01_move.h"

// Functions in this file: em01_move (0x0202ea2c).

void em01_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        if ((e->timer & 0xf) == 0) {
            u8 turn = em01_turnAmountTable[Random() & 3];
            e->direction = (e->direction + turn) & 0x1f;
            if (turn != 0) {
                dirSeqSet(e);
            }
        }
        if (func_020847f8(e) != 0) {
            dirSeqSet(e);
        }
    } else {
        e->timer = 0x3c;
        e->action++;
    }
}
