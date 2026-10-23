#include "engine/functions.h"
#include "global.h"
#include "object/protos.h"

// Set4a actor, second unit (module set4a). Address -> name:
//   0x0205e204 set4a_move (original name)
//   (set4a_init at 0x0205e1a8 is in scratch/agentF/nonmatching)

extern const s8 data_020d8d00[]; // (dx, dy) pairs for the four directions, indexed by animation state
extern u16 frameCounter;

ARM void set4a_move(Entity *e) {
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
