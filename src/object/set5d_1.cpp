#include "engine/functions.h"
#include "global.h"

// Set5d actor, first unit (module set5d). Address -> name:
//   0x0205fbd4 set5d_init (original name)
//   0x0205fc3c set5d_wait (original name)
//   0x0205fca4 set5d_walk (original name, state table set5d_walk_states indexed by e->subAction)
//   0x0205fcc0 set5d_walk_init (original name walk_init)
//   0x0205fcf8 set5d_walk_move (original name walk_move)
//   0x0205fd2c set5d_NoOp1 and 0x0205fd30 set5d_NoOp2 (empty state handlers)

void ObjSetTargetWord(Entity *e, u16 value); // defined in src/game/npc.cpp, not yet in functions.h

extern const EntityFunc set5d_walk_states[]; // walk state table indexed by e->subAction

ARM void set5d_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b14 = 2;
    e->spriteSettings.b30 = 2;
    e->unk_2e = 3;
    e->speed = 0x100;
    e->unk_5e.b2 = 1;
    e->animationState = 4;
    ObjSetTargetWord(e, 0);
    e->action++;
}

ARM void set5d_wait(Entity *e) {
    if (e->subAction == 0) {
        ObjSetTargetWord(e, 0);
        e->subAction++;
        e->linkedEntity->unk_00[2] = 0;
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    InitAnimationForceUpdate(e, e->unk_23);
    e->unk_28 = (Random() & 0xf0) + 1;
}

ARM void set5d_walk(Entity *e) {
    set5d_walk_states[e->subAction](e);
}

ARM void set5d_walk_init(Entity *e) {
    e->subAction++;
    e->timer = e->linkedEntity->unk_00[5];
    e->direction = e->linkedEntity->unk_00[6];
    e->linkedEntity->unk_00[2] = 2;
    ObjSetTargetWord(e, 4);
}

ARM void set5d_walk_move(Entity *e) {
    MoveDir(e);
    UpdateAnimationSingleFrame(e);
    e->timer--;
    if (e->timer == 0) {
        e->linkedEntity->unk_00[4] = 1;
    }
}

ARM void set5d_NoOp1(Entity *e) {
}

ARM void set5d_NoOp2(Entity *e) {
}
