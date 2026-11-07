#include "engine/functions.h"
#include "global.h"
#include "actor/object/protos.h"

// Set4a actor (module set4a). Address -> name:
//   0x0205e18c Set4a (original name), 0x0205e1a8 set4a_init
//   (set4a_init at 0x0205e1a8 is in scratch/agentF/nonmatching; set4a_move at 0x0205e204 is in the next unit)

extern const EntityFunc data_020d8d08[]; // state table indexed by e->action

void Set4a(Entity *e) {
    data_020d8d08[e->action](e);
}

// Set4a actor (module set4a), third unit: set4a_init (0x0205e1a8), between Set4a and set4a_move.

// Sets the state to 1, derives the facing frame from the direction and starts the animation.
void set4a_init(Entity *e) {
    e->action = 1;
    e->animationState = e->direction >> 2;
    InitAnimationForceUpdate(e, e->animationState >> 1);
    e->unk_5e.b0 = 3;
    e->spriteSettings.b0 = 1;
    func_02085f98(e, 0x89);
}

// Set4a actor, second unit (module set4a). Address -> name:
//   0x0205e204 set4a_move (original name)
//   (set4a_init at 0x0205e1a8 is in scratch/agentF/nonmatching)

extern const s8 data_020d8d00[]; // (dx, dy) pairs for the four directions, indexed by animation state
extern u16 frameCounter;

void set4a_move(Entity *e) {
    s32 hitResult;

    hitResult = func_02083d18(e, data_020d8d00[e->animationState], data_020d8d00[e->animationState + 1]);
    if (hitResult != 0 && (u32)hitResult < 0x20) {
        PutObjWork(e);
        return;
    }
    MoveDir(e);
    UpdateAnimationSingleFrame(e);
    if (frameCounter & 2) {
        e->spriteSettings.b16 = 6;
    } else {
        e->spriteSettings.b16 = 3;
    }
}
