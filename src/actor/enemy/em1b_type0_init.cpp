// em1b_type0_init (0x0202f138): sets up the head of the em1b chain: takes three free objects, makes them its parts
// (ids 0x1b, types 1..3, parent e, each one the child of the one before), registers them in list 4 and starts the
// head itself with a random direction.
#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"
#include "actor/enemy/em1b.h"

void em1b_type0_init(Entity *e) {
    Entity *first;
    Entity *second;
    Entity *third;

    e->statusFlags &= 0x7f;
    first = GetObjWork();
    if (first == NULL) {
        return;
    }
    second = GetObjWork2(first);
    if (second == NULL) {
        return;
    }
    third = GetObjWork2(second);
    if (third == NULL) {
        return;
    }
    e->y.HALF.LO = 3;
    first->objKind = 3;
    second->objKind = 3;
    third->objKind = 3;
    first->objId = 0x1b;
    second->objId = 0x1b;
    third->objId = 0x1b;
    first->type = 1;
    second->type = 2;
    third->type = 3;
    first->parent = e;
    second->parent = e;
    third->parent = e;
    first->child = second;
    second->child = third;
    third->child = NULL;
    ObjPosCopyOfs32(e, first, 0, 2);
    ObjPosCopyOfs32(e, second, 0, 1);
    ObjPosCopyOfs32(e, third, 0, 0);
    RegistObjWork(4, first);
    RegistObjWork(4, second);
    RegistObjWork(4, third);
    e->y.WORD += 3;
    e->child = first;
    e->spriteSettings.b0 = 1;
    e->statusFlags |= 0x80;
    e->hitbox = em1b_hitbox;
    e->action = 1;
    e->timer = 1;
    e->subtimer = 1;
    VARS(Vars_Em1b, e)->child1 = second;
    VARS(Vars_Em1b, e)->child2 = third;
    e->direction = Random() & 0x1f;
    e->animationState = ((e->direction + 4) & 0x1c) >> 2;
    InitAnimationForceUpdate(e, e->animationState);
}
