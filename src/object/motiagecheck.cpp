#include "engine/functions.h"
#include "engine/player.h"
#include "object/set30.h"
#include "global.h"

// One player's contribution to motiagecheck: a player whose bit is in the mask gets a table byte written, and
// counts up or down depending on its status flags and the child entity it is linked to.
#define MOTIA_CHECK_PLAYER(idx, bit)                                        \
    if (mask & (bit)) {                                                     \
        data_0212ceb0[idx].unk_3d[2] = motiaAnimTable[e->animationState];    \
        if (data_0212ceb0[idx].statusFlags & 0x90) {                        \
            count = (u8)(count - 1);                                        \
        } else {                                                            \
            Entity *ent = data_0212ceb0[idx].entity;                        \
            Entity *linked = *(Entity **)ent->unk_6c;                       \
            if (linked != NULL && linked->child->objKind == 1 &&            \
                !(mask & flagBits[linked->child->type])) {             \
                count = (u8)(count + 1);                                    \
            }                                                               \
        }                                                                   \
    }

// motiagecheck (0x020690a0): counts the players and linked children that agree with the actor's animation state.
ARM int motiagecheck(Entity *e) {
    s32 mask;
    s32 count;
    mask = func_02084110(e);
    count = CountBits(mask);
    MOTIA_CHECK_PLAYER(0, 0x1)
    MOTIA_CHECK_PLAYER(1, 0x2)
    MOTIA_CHECK_PLAYER(2, 0x4)
    MOTIA_CHECK_PLAYER(3, 0x8)
    return count;
}
