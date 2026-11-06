#include "engine/functions.h"
#include "global.h"
#include "actor/object/gufu_vars.h"

// Gufu body movement (module gufu, third unit). Address -> name:
//   0x0207481c gufu_body_move (original name; switch on the result state byte at effectState + 0x0e)

extern u8 effectState[];           // result state block, see enemy/ending.h
extern Entity *mapState;        // the body entity the scene points at

void gufu_body_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    switch (effectState[0x0e]) {
    case 0:
        break;
    case 1:
        mapState = e;
        e->direction = 0x10;
        e->speed = 0x80;
        MoveDir(e);
        if (e->y.HALF.HI <= 0xa0) {
            return;
        }
        effectState[0] = effectState[0] + 1;
        effectState[0x0e] = 0;
        return;
    case 2:
        if (e->frame != 1) {
            return;
        }
        InitAnimationForceUpdate(e, 2);
        effectState[0x0e] = 0;
        return;
    case 3:
        if (e->frame == 1) {
            InitAnimationForceUpdate(e, 3);
            return;
        }
        if (!(e->frame & 0x80)) {
            return;
        }
        InitAnimationForceUpdate(e, 1);
        effectState[0x0e] = 0;
        return;
    case 4: {
        Vars_GufuBody *v;

        UpdateAnimationSingleFrame(e);
        v = VARS(Vars_GufuBody, e);
        v->angle = 0xc0;
        v->radiusX = 0x10;
        v->radiusY = 4;
        e->action = e->action + 1;
        e->timer = 0x80;
        return;
    }
    }
}
