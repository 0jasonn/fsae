#include "engine/functions.h"
#include "global.h"
#include "actor/object/tama11.h"

// throw module, 0x02080b54 to 0x02080ca4 (the throwinit actor state and its dispatcher).
//   tama11_putObjWorkThunk (0x02080b54): tail call to PutObjWork.
//   throwinit (0x02080b60): sets up the throw from the child's position and copies the child's and player's pose.

// tama11_putObjWorkThunk (0x02080b54)
void tama11_putObjWorkThunk(Entity *e) {
    ((void (*)(Entity *))PutObjWork)(e);
}

// throwinit (0x02080b60): starts the flight of a thrown object. If the child still has the kind and id that throw_init
// copied, the object takes the player's pose (sprite bits, position, layer, status flags), the speed and z velocity
// for its direction, the child's hitbox and height, and sets its attack values. Otherwise the object is removed.
void throwinit(Entity *e) {
    Entity *player;
    Entity *other;
    u8 idx;
    Entity *child;

    player = playerWork[e->type].entity;
    idx = e->unk_1a >> 4;
    child = e->child;
    *(u32 *)&player->unk_6c[0] = 0;
    if (VARS(Tama11Vars, e)->copiedKind == child->objKind && VARS(Tama11Vars, e)->copiedId == child->objId) {
        other = e->child;
        if (other != e) {
            other->subAction = 2;
            child = other;
        } else {
            e->unk_2e = 4;
        }
        e->spriteSettings.b14 = player->spriteSettings.b14;
        e->spriteSettings.b30 = player->spriteSettings.b30;
        e->hitbox = child->hitbox;
        e->speed = tama11_speedTable[idx];
        e->zVelocity = tama11_zVelTable[idx];
        e->z.HALF.HI = child->z.HALF.HI;
        e->y.HALF.HI = player->y.HALF.HI;
        e->x.HALF.HI = player->x.HALF.HI;
        e->layer = player->layer;
        e->attackDamage = 3;
        e->attackKnockback = 0xc;
        e->unk_40 = 0x17;
        e->statusFlags = player->statusFlags;
        e->poseId = 1;
        func_02084180(e);
    } else {
        func_02089988(&playerWork[e->type]);
        PutObjWork(e);
    }
}
