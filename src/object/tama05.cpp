#include "engine/functions.h"
#include "object/tama05.h"

// tama05 family, address -> name (original names from symbols.txt):
//   0x0207e834 tama05_init, 0x0207e8e4 tama05_wait, 0x0207e984 tama05_move
//   (prtInfoDel 0x0207ea14 and hasshaSet 0x0207ea54 are parked in scratch/agentC/nonmatching)

// tama05_init, 0x0207e834. Sets the sprite, the animation from the direction, and the hitbox; a type 3 actor gets
// its own speed and damage; type2 0 starts the wait state, anything else runs hasshaSet.
ARM void tama05_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->animationState = ((e->direction + 4) & 0x18) >> 3;
    e->hitbox = data_020dccc4;
    if (e->type == 3) {
        e->unk_2e = 6;
        e->z.HALF.HI = -4;
        e->attackDamage = 4;
    }
    if (e->type2 == 0) {
        e->action = 1;
        ObjPosCopyOfs32(e->parent, e, 0, data_020dccb8[e->animationState] << 16);
        InitAnimationForceUpdate(e, e->animationState);
    } else {
        hasshaSet(e);
    }
}

// tama05_wait, 0x0207e8e4. Follows the parent; on the parent's odd frames a type 3 actor spawns the matching
// item at the parent's position, and then the actor is cleaned up.
ARM void tama05_wait(Entity *e) {
    Entity *tama;
    UpdateAnimationSingleFrame(e);
    ObjPosCopyOfs32(e->parent, e, 0, data_020dccb8[e->animationState] << 16);
    if ((e->parent->frame & 1) == 0) {
        return;
    }
    if (e->type == 3) {
        tama = GetTamaWork(5);
        if (tama != 0) {
            tama->type = 3;
            tama->type2 = 1;
            tama->direction = (e->direction + 6) & 0x1f;
            tama->parent = e->parent;
            ObjPosCopy(e, tama);
        }
    }
    prtInfoDel(e);
    hasshaSet(e);
}

// tama05_move, 0x0207e984. Animates the actor and tests the walls: a type 3 actor copies its position to an object
// when it touched a wall, the others are removed when the wall mask of their direction is hit.
ARM void tama05_move(Entity *e) {
    Entity *target;
    UpdateAnimationSingleFrame(e);
    func_0208b644(e);
    func_0208af0c(e);
    if (e->type != 3) {
        if ((e->wallFlags & data_02117ba8[e->direction >> 3]) != 0) {
            PutObjWork(e);
        }
        return;
    }
    if (e->wallFlags != 0) {
        target = GetSetWork(0xf, 0xd, 0);
        if (target != 0) {
            ObjPosCopy(e, target);
        }
        PutObjWork(e);
    }
}
