#include "engine/functions.h"
#include "global.h"

// Set4b actor, second unit (module set4b). Address -> name:
//   0x0205e300 set4b_move (original name)
//   (set4b_init at 0x0205e29c is in scratch/agentF/nonmatching)

extern u8 data_0212c824[]; // per parent type: animation step for this actor

ARM void set4b_move(Entity *e) {
    Entity *parent = e->contactedEntity;
    s32 flag = 1;
    s32 step;
    s32 index;

    e->x.HALF.HI = parent->x.HALF.HI;
    e->y.HALF.HI = parent->y.HALF.HI;
    e->z.HALF.HI = parent->z.HALF.HI - 0x12;
    if (parent->unk_23 != 0xa9 && parent->unk_23 != 0xad) {
        flag = 0;
    }
    e->spriteSettings.b0 = !flag;
    step = data_0212c824[e->contactedEntity->type];
    if (e->timer == step) {
        return;
    }
    e->timer = step;
    index = step & 0xff;
    switch (index) {
    case 1:
    case 2:
    case 3:
    case 4:
        InitAnimationForceUpdate(e, index - 1);
        return;
    default:
        PutObjWork(e);
        return;
    }
}
