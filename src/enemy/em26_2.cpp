#include "engine/functions.h"
#include "enemy/em26.h"
#include "global.h"

ARM void em26_move(Entity *e) {
    V(e)->lifeTimer--;
    if (V(e)->lifeTimer == 0) {
        KemuriSet(e);
        BubbleReset(e);
        PutObjWork(e);
        return;
    }
    func_020847c8(e);
    UpdateAnimationSingleFrame(e);
    if (UpdateGravity(e, 0x1800) == 0) {
        jumpInit(e);
    }
}

ARM void em26_div(Entity *e) {
    Entity *leftPart = GetObjWork();
    if (leftPart == NULL) {
        return;
    }
    Entity *rightPart = GetObjWork2(leftPart);
    if (rightPart == NULL) {
        return;
    }
    childInit(e, leftPart);
    leftPart->x.HALF.HI -= 4;
    leftPart->parent = rightPart;
    leftPart->direction = (e->baseDirection - 2) & 0x1f;
    childInit(e, rightPart);
    rightPart->x.HALF.HI += 4;
    rightPart->parent = leftPart;
    rightPart->direction = (e->baseDirection + 2) & 0x1f;
    Entity *anchor = GetSetWork(0xf, 2, 0);
    if (anchor != NULL) {
        ObjPosCopy(e, anchor);
    }
    PutObjWork(e);
}
