#include "engine/functions.h"
#include "actor/enemy/em15.h"
#include "global.h"

// Actor fields of em15 past the shared Entity fields.
typedef struct Vars_Em15GetPos {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ s16 spawnX; // x of the position when it was placed
    /* 72 */ s16 spawnY; // y of the position when it was placed
} Vars_Em15GetPos;

// em15_getpos_03cf18 (0x0203cf18, original getpos): places the actor at a random offset from its parent, copies the
// layer and turns towards the parent. Returns FALSE when the new spot is blocked (flag between 1 and 0x1f).
BOOL em15_getpos_03cf18(Entity *e) {
    Entity *parent;
    u32 blockFlag;
    s32 turn;
    s32 facing;
    const s16 *offset;

    offset = &em15_targetOffsets[Random() & 0x1e];
    parent = e->child;
    e->x.HALF.HI = parent->x.HALF.HI + offset[0];
    e->y.HALF.HI = parent->y.HALF.HI + offset[1];
    e->layer = parent->layer;
    func_0208ae30(e);
    blockFlag = func_02083d28(e);
    if (blockFlag != 0 && blockFlag < 0x20) {
        return FALSE;
    }
    VARS(Vars_Em15GetPos, e)->spawnX = e->x.HALF.HI;
    VARS(Vars_Em15GetPos, e)->spawnY = e->y.HALF.HI;
    turn = GetDirectionToEntity(e, e->child) + 4;
    facing = turn & 0x18;
    e->direction = facing;
    e->animationState = facing >> 3;
    InitAnimationForceUpdate(e, e->animationState);
    return TRUE;
}
