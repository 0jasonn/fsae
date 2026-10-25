#include "engine/functions.h"
#include "global.h"
#include "enemy/kamen.h"

// Functions in this file: kamen_move (0x0203ed14), kamen_tenmetsu (0x0203ed44).

ARM void kamen_move(Entity *e) {
    MoveDir(e);
    if (func_02086044(e, 0x1800) == 0) {
        e->action = 2;
        e->timer = 0x1e;
    }
}

ARM void kamen_tenmetsu(Entity *e) {
    e->spriteSettings.b0 ^= 1;
    e->timer--;
    if (e->timer == 0) {
        PutObjWork(e);
    }
}
