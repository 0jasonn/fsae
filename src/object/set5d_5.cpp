#include "engine/functions.h"
#include "global.h"

// Set5d actor, bikkuri (surprise mark) unit (module set5d). Address -> name:
//   0x0205ff38 set5d_bikkuri (original name, state table set5d_bikkuri_states indexed by e->subAction)
//   0x0205ff54 bikkuri_init (original name)
//   0x0205ffb0 bikkuri_move (original name)

void ObjSetTargetWord(Entity *e, u16 value); // defined in src/game/npc.cpp, not yet in functions.h

extern const EntityFunc set5d_bikkuri_states[]; // bikkuri state table indexed by e->subAction

ARM void set5d_bikkuri(Entity *e) {
    set5d_bikkuri_states[e->subAction](e);
}

ARM void bikkuri_init(Entity *e) {
    Entity *mark;

    e->subAction++;
    e->zVelocity = 0x18000;
    e->linkedEntity->unk_00[2] = 2;
    ObjSetTargetWord(e, 4);
    mark = GetSetWork(0x5a, 1, 0x1e);
    mark->x.HALF.HI = 0x98;
    mark->y.HALF.HI = 0xf0;
    SoundReq(0x1f7);
}

ARM void bikkuri_move(Entity *e) {
    if (UpdateGravity(e, 0x2400) == 0) {
        e->linkedEntity->unk_00[4] = 1;
    }
}
