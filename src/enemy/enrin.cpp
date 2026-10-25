#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
// Actor enrin (module enrin), unit 1. Address -> name:
//   0x0203fcd8 enrinMove

// Field of the child entity (a player, its index is child->type) that enrin follows.
typedef struct Vars_enrinChild {
    /* 00 */ u8 unk_00[0x72];
    /* 72 */ u16 followTimer; // frames the child is still followed, 0 when it is gone
} Vars_enrinChild;

#define CHILD_VARS(e) VARS(Vars_enrinChild, e)

// Follows the child: copies its position, sprite bits and the timer-based flag, drops the child's status bit 0x4000
// and removes itself when the child's timer is out.
ARM void enrinMove(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->statusFlags = 0;
        e->unk_5e.b0 = 3;
        InitAnimationForceUpdate(e, 1);
    }
    ObjPosCopy(e->child, e);
    e->z.HALF.HI -= 4;
    UpdateAnimationSingleFrame(e);
    if (CHILD_VARS(e->child)->followTimer != 0) {
        if (e->child->action != 2) {
            e->spriteSettings.b30 = e->child->spriteSettings.b30;
            e->spriteSettings.b14 = e->child->spriteSettings.b14;
        } else {
            e->spriteSettings.b30 = 1;
            e->spriteSettings.b14 = 1;
        }
        if (CHILD_VARS(e->child)->followTimer >= 0x3c) {
            e->spriteSettings.b0 = 1;
            return;
        }
        e->spriteSettings.b0 ^= 1;
    } else {
        data_0212ceb0[e->child->type].statusFlags &= 0xbfff;
        PutObjWork(e);
    }
}
