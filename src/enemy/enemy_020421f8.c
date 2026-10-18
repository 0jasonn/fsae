#include "enemy/actor_0204112c.h"
#include "global.h"

extern const EntityFunc data_020d351c[];
extern const s8 data_020d34c4[];
extern const EntityFunc data_020d358c[];
extern const s16 data_020d7e58[];

// Enemy_SetDefaultAuxBytes (0x020421f8): fills the eight bytes at 0x78 with 0x88.
ARM void Enemy_SetDefaultAuxBytes(Entity *e) {
    e->unk_6c[0x0c] = 0x88;
    e->unk_6c[0x0d] = 0x88;
    e->unk_6c[0x0e] = 0x88;
    e->unk_6c[0x0f] = 0x88;
    e->unk_6c[0x10] = 0x88;
    e->unk_6c[0x11] = 0x88;
    e->unk_6c[0x12] = 0x88;
    e->unk_6c[0x13] = 0x88;
}

// Enemy_FollowParentState (0x02042220): runs the handler for this type, copies the parent's state, and removes
// this entity once the parent is gone.
ARM void Enemy_FollowParentState(Entity *e) {
    data_020d351c[e->type](e);
    if (e->parent->unk_6c[4] == 0xff) {
        DeleteEntity(e);
    } else {
        e->z.HALF.HI = data_020d34c4[(e->parent->frame & 0x70) >> 4];
        if (e->parent->contactFlags == 0xff) {
            e->iframes = e->parent->iframes;
        }
    }
    if (e->parent->health != 0) {
        return;
    }
    func_02076930(e);
    DeleteEntity(e);
}

// Enemy_FollowParentOffset (0x020422a8): runs the handler for this action, then places the entity at a fixed offset
// from its parent, using the direction to index a table.
ARM void Enemy_FollowParentOffset(Entity *e) {
    data_020d358c[e->action](e);
    int dir = e->direction;
    e->x.HALF.HI = e->parent->x.HALF.HI + ((data_020d7e58[dir] * 0x2c) >> 8);
    e->y.HALF.HI = e->parent->y.HALF.HI - ((data_020d7e58[dir + 0x40] * 0x24) >> 8) - 4;
}
