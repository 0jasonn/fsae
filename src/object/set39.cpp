#include "engine/functions.h"
#include "global.h"
#include "object/set38.h"

// Set39 family (module set39), 0x0206bc60 .. 0x0206bce4.
// Address -> name: 0x0206bc60 Set39, 0x0206bc7c set39_init, 0x0206bcb8 set39_move

extern const EntityFunc set39Table[]; // set39Table, indexed by action

ARM void Set39(Entity *e) {
    set39Table[e->action](e);
}

ARM void set39_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b14 = 3;
    e->action++;
    e->timer = 7;
    InitAnimationForceUpdate(e, 0);
}

ARM void set39_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    PutObjWork(e);
}
