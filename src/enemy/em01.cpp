#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"

// Actor em01 (original names from the debug build): Em01, em01_normal, em01_init, em01_wait, em01_move,
// em01_slowdown, em01_stop, dirSeqSet.

extern EntityFunc em01_actions[];
extern EntityFunc em01_normalActions[];
extern const u8 em01_hitbox[];


void dirSeqSet(Entity *e);

ARM void Em01(Entity *e) {
    func_02084700(e);
    em01_actions[func_02084a30(e)](e);
    func_0208ae30(e);
    e->spriteSettings.b30 = 1;
    e->spriteSettings.b14 = 1;
}


ARM void em01_normal(Entity *e) {
    em01_normalActions[e->action](e);
}


ARM void em01_init(Entity *e) {
    u8 nextAction;

    e->spriteSettings.b0 = 1;
    e->spriteSettings.b14 = 1;
    e->unk_2e = 2;
    e->hitbox = em01_hitbox;
    e->animationState = 0;
    InitAnimationForceUpdate(e, 0);
    nextAction = e->action + 1;
    e->timer = 0x3c;
    e->action = nextAction;
}

ARM void em01_wait(Entity *e) {
    u8 direction;
    u8 animState;
    u8 nextAction;

    if (--e->timer != 0) {
        return;
    }
    e->timer = (Random() & 0x70) + 0x4b;
    direction = Random() & 0x1f;
    animState = direction >> 4;
    e->direction = direction;
    e->animationState = animState;
    InitAnimationForceUpdate(e, e->animationState);
    nextAction = e->action + 1;
    e->speed = 0xe0;
    e->action = nextAction;
}

