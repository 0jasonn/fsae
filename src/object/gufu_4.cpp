#include "engine/functions.h"
#include "global.h"
#include "object/d_decls.h"
#include "engine/player.h"
#include "object/gufu_vars.h"

// Gufu body rotation (module gufu, fourth unit). Address -> name:
//   0x02074934 gufu_body_kaiten (original name; subAction 0..5 steps the rotation, see below)
//   0x02074aa4 gufu_body_left (original name)
//   0x02074b0c gufu_body_right (original name)

extern const s16 trigTable[]; // trigTable, 256 entries of sin, cos is 0x40 entries later
extern u8 data_021349c0[];    // result state block, see enemy/ending.h
extern u8 messageRequest[];   // flag block, see engine/misc_d.h

ARM void gufu_body_kaiten(Entity *e) {
    Vars_GufuBody *v = VARS(Vars_GufuBody, e);

    UpdateAnimationSingleFrame(e);
    e->x.HALF.HI = ((trigTable[v->angle + 0x40] * v->radiusX) >> 8) + 0x80;
    e->y.HALF.HI = ((trigTable[v->angle] * v->radiusY) >> 8) + 0xac;
    switch (e->subAction) {
    case 0:
        v->angle -= 2;
        if (--e->timer == 0) {
            e->timer = 0x40;
            e->subAction++;
        }
        return;
    case 1:
        v->angle -= 4;
        if (--e->timer == 0) {
            e->timer = 0x20;
            e->subAction++;
        }
        return;
    case 2:
    case 3:
    case 4:
        v->angle -= 8;
        e->timer--;
        if (e->timer != 0) {
            return;
        }
        e->timer = 0x20;
        e->subAction++;
        v->radiusX++;
        v->radiusY++;
        return;
    case 5:
        v->angle -= 8;
        e->timer--;
        if (e->timer != 0) {
            return;
        }
        e->action++;
        e->subAction = 0;
        e->direction = 0x17;
        e->speed = 0x800;
        SoundReq(0x1fb);
        DemoLinkWalkSet(0, 8, 0);
        return;
    }
}

ARM void gufu_body_left(Entity *e) {
    UpdateAnimationSingleFrame(e);
    MoveDir(e);
    if (e->x.HALF.HI >= -0x40) {
        return;
    }
    e->action++;
    data_0212ceb0[0].entity->animationState = 6;
    DemoLinkWalkSet(0, 0x10, 0);
    data_021349c0[0] = data_021349c0[0] + 1;
}

ARM void gufu_body_right(Entity *e) {
    u16 pos[2];

    UpdateAnimationSingleFrame(e);
    if (data_021349c0[0x0e] < 5) {
        return;
    }
    switch (e->subAction) {
    case 0:
        pos[0] = data_0212ceb0[0].entity->x.HALF.HI;
        pos[1] = data_0212ceb0[0].entity->y.HALF.HI;
        ObjAnimMoveSet(e, pos, 0x1e);
        SoundReq(0x1fb);
        e->subAction++;
        return;
    case 1:
        if (ObjAnimMoveLine(e) == 0) {
            return;
        }
        pos[0] = 0x12c;
        pos[1] = data_0212ceb0[0].entity->y.HALF.HI - 0x20;
        ObjAnimMoveSet(e, pos, 0x1e);
        data_0212ceb0[0].state = 9;
        MessageRequest(7);
        messageRequest[3] = (messageRequest[3] & ~0x1f) | 1;
        messageRequest[4] = (messageRequest[4] & ~0x1f) | 0x10;
        SoundReq(0x202);
        e->subAction++;
        return;
    case 2:
        if (ObjAnimMoveLine(e) == 0) {
            return;
        }
        data_021349c0[0]++;
        PutObjWork(e);
        return;
    }
}
