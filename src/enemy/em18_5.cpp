#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "enemy/em18_units.h"
// Actor em18 (module em18), unit 5. Address -> name:
//   0x0203dce4 em18_type0_init, 0x0203de10 type0_rockon, 0x0203dea8 em18_type0_move

// Setup of type 0: takes four free objects as its children (types 0 to 3), links them to the actor, registers them
// in list 4 and starts the rock-on state.
ARM void em18_type0_init(Entity *e) {
    Entity *c0;
    Entity *c1;
    Entity *c2;
    Entity *c3;

    c0 = GetObjWork();
    if (c0 == NULL) {
        return;
    }
    c1 = GetObjWork2(c0);
    if (c1 == NULL) {
        return;
    }
    c2 = GetObjWork2(c1);
    if (c2 == NULL) {
        return;
    }
    c3 = GetObjWork2(c2);
    if (c3 == NULL) {
        return;
    }
    e->type2 = 0xf;
    e->layer |= 0xc000;
    e->hitbox = em06_hitbox;
    c0->objKind = 3;
    c1->objKind = 3;
    c2->objKind = 3;
    c3->objKind = 3;
    c0->objId = 0x18;
    c1->objId = 0x18;
    c2->objId = 0x18;
    c3->objId = 0x18;
    c0->type = 1;
    c1->type = 1;
    c2->type = 1;
    c3->type = 1;
    c0->type2 = 0;
    c1->type2 = 1;
    c2->type2 = 2;
    c3->type2 = 3;
    c0->parent = e;
    c1->parent = e;
    c2->parent = e;
    c3->parent = e;
    EmPalamCopy(e, c0);
    EmPalamCopy(e, c1);
    EmPalamCopy(e, c2);
    EmPalamCopy(e, c3);
    RegistObjWork(4, c0);
    RegistObjWork(4, c1);
    RegistObjWork(4, c2);
    RegistObjWork(4, c3);
    type0rockonSet(e);
}

// Rock-on state of type 0: keeps a child (from the free slots of the players when none is set) and turns the actor
// to face it, then moves on to the state of em18_type0_move after the timer.
ARM void type0_rockon(Entity *e) {
    e->child = func_02084f98(e, 0x50, 0x40);
    e->timer--;
    if (e->timer != 0) {
        if (e->child == NULL) {
            return;
        }
    }
    if (e->child == NULL) {
        e->child = data_0212ceb0[Random() % data_0212c7c8.unk_0].entity;
    }
    e->action = 2;
    e->timer = 0xf;
    e->subtimer = 0x3c;
    e->direction = GetFacingDirection(e, e->child);
}

// Move of type 0: counts the sub timer down (rock-on state again at zero), drops the actor when its type2 is 0, and
// turns the child towards the actor every 0xf frames.
ARM void em18_type0_move(Entity *e) {
    e->subtimer--;
    if (e->subtimer != 0) {
        if (e->type2 != 0) {
            e->timer--;
            if (e->timer == 0) {
                e->timer = 0xf;
                e->direction = func_02084fd0(e, e->child);
            }
            func_020847f8(e);
        } else {
            PutObjWork(e);
        }
    } else {
        type0rockonSet(e);
    }
}
