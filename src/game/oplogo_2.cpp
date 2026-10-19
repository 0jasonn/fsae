#include "engine/functions.h"
#include "global.h"

// Opening logo objects, continued from 0x02068314 (oplogo_2 unit; panel_nop is a no-op state).
extern EntityFunc oplogo_panelTable[];
extern EntityFunc oplogo_youTable[];
extern u8 data_0212c5ac;

ARM void oplogo_shadow_move(Entity *e) {
    s32 target;
    MoveDir(e);
    target = (e->type2 + 1) * 0x1a + 0x50;
    if (e->x.HALF.HI < target) {
        e->x.HALF.HI = target;
    }
    if (data_0212c5ac == 0) {
        return;
    }
    PutObjWork(e);
}

ARM void oplogo_panel(Entity *e) {
    oplogo_panelTable[e->action](e);
}

ARM void panel_init(Entity *e) {
    u8 action = e->action;
    e->action = action + 1;
    *(u32 *)&e->spriteSettings |= 0x2000;
    e->spriteSettings.b0 = 2;
    e->spriteSettings.b14 = 0;
    e->spriteSettings.b30 = 0;
    e->direction = 0x1d;
    e->speed = 0x100;
    e->x.HALF.HI = 8;
    e->y.HALF.HI = 0x10;
    InitAnimationForceUpdate(e, (u8)(e->type2 + 4));
}

ARM void panel_wait(Entity *e) {
    MoveDir(e);
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        PutObjWork(e);
    }
}

ARM void panel_nop(Entity *e) {
}

ARM void oplogo_you(Entity *e) {
    oplogo_youTable[e->action](e);
}
