#include "engine/functions.h"
#include "object/parasw_2.h"
#include "global.h"

// Parasw actor, second unit (module parasw). Address -> name:
//   0x02059294 ps00_start (original name)
//   0x020592e0 ps00_wait (original name)
//   0x02059320 ps00_check (original name)
//   0x02059398 ps00_end (original name)
//   0x02059410 parasw_01 (original name)
//   0x0205942c ps01_end (original name)
//   0x020594a4 parasw_02 (original name)
//   0x020594c0 ps02_init (original name)
//   0x020594e0 ps02_start (original name)
//   0x0205952c ps02_wait (original name)
//   0x0205956c ps02_check (original name)
//   0x020595e4 ps02_end (original name)
//   0x0205965c parasw_typeDispatch (provisional, parasw_typeActions[e->type](e))

ARM void ps00_start(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    if (check_flag(em12_typeMasks[e->areaIndex], 0, 3)) {
        e->action++;
    }
}

ARM void ps00_wait(Entity *e) {
    if (check_next(em12_typeMasks[e->areaIndex], e->subtimer, 3)) {
        e->timer = 0x14;
        e->action++;
    }
}

ARM void ps00_check(Entity *e) {
    e->timer--;
    if (e->timer == 0) {
        e->action = 0;
        SoundReq(0x40);
        return;
    }
    if (!check_flag(em12_typeMasks[e->areaIndex], e->subtimer, 3)) {
        return;
    }
    e->action++;
    e->subtimer += 3;
    SoundReq(8);
}

ARM void ps00_end(Entity *e) {
    e->timer--;
    if (e->timer == 0) {
        e->action = 0;
        SoundReq(0x40);
        return;
    }
    if (!check_flag(em12_typeMasks[e->areaIndex], 0xc, 3)) {
        return;
    }
    em12_typeMasks[e->areaIndex] |= 0x8000;
    SoundReq(0x10);
    PutObjWork(e);
}

ARM void parasw_01(Entity *e) {
    parasw01_actions[e->action](e);
}

ARM void ps01_end(Entity *e) {
    e->timer--;
    if (e->timer == 0) {
        e->action = 0;
        SoundReq(0x40);
        return;
    }
    if (!check_flag(em12_typeMasks[e->areaIndex], 9, 3)) {
        return;
    }
    em12_typeMasks[e->areaIndex] |= 0x1000;
    SoundReq(0x10);
    PutObjWork(e);
}

ARM void parasw_02(Entity *e) {
    parasw02_actions[e->action](e);
}

ARM void ps02_init(Entity *e) {
    e->timer = 0x14;
    e->subtimer = 2;
    e->action++;
}

ARM void ps02_start(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    if (check_flag(em12_typeMasks[e->areaIndex], 0, 2)) {
        e->action++;
    }
}

ARM void ps02_wait(Entity *e) {
    if (check_next(em12_typeMasks[e->areaIndex], e->subtimer, 2)) {
        e->timer = 0x14;
        e->action++;
    }
}

ARM void ps02_check(Entity *e) {
    e->timer--;
    if (e->timer == 0) {
        e->action = 0;
        SoundReq(0x40);
        return;
    }
    if (!check_flag(em12_typeMasks[e->areaIndex], e->subtimer, 2)) {
        return;
    }
    e->action++;
    e->subtimer += 2;
    SoundReq(8);
}

ARM void ps02_end(Entity *e) {
    e->timer--;
    if (e->timer == 0) {
        e->action = 0;
        SoundReq(0x40);
        return;
    }
    if (!check_flag(em12_typeMasks[e->areaIndex], 8, 2)) {
        return;
    }
    em12_typeMasks[e->areaIndex] |= 0x400;
    SoundReq(0x10);
    PutObjWork(e);
}

ARM void parasw_typeDispatch(Entity *e) {
    parasw_typeActions[e->type](e);
}
