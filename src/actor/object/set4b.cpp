#include "engine/functions.h"
#include "global.h"

// Set4b actor (module set4b). Address -> name:
//   0x0205e280 Set4b (provisional name for the dispatcher, renamed from Set4b)
//   (set4b_init at 0x0205e29c is in scratch/agentF/nonmatching)
//   (set4b_move at 0x0205e300 is in the next unit)

extern const EntityFunc data_02115898[]; // state table indexed by e->action

void Set4b(Entity *e) {
    data_02115898[e->action](e);
}

// Set4b actor (module set4b), third unit: set4b_init (0x0205e29c), between Set4b and its state functions.

extern u8 data_0212c824[]; // timer value per type of the touching entity

// Advances to the next state, copies the timer from the table entry of the entity that touched the object and starts
// the animation.
void set4b_init(Entity *e) {
    e->action++;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b14 = 0;
    e->unk_5e.b0 = 3;
    e->spriteSettings.b30 = 1;
    e->timer = data_0212c824[e->contactedEntity->type];
    InitAnimationForceUpdate(e, e->timer - 1);
}

// Set4b actor, second unit (module set4b). Address -> name:
//   0x0205e300 set4b_move (original name)
//   (set4b_init at 0x0205e29c is in scratch/agentF/nonmatching)

extern u8 data_0212c824[]; // per parent type: animation step for this actor

void set4b_move(Entity *e) {
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
