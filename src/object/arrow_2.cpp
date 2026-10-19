#include "engine/functions.h"
#include "global.h"
#include "object/arrow.h"

// Arrow and beam helpers (module arrow, second unit). Original names from the debug build; Beam is the beam main
// (named Beam).
//   arrow_wait, arrow_kokin, Beam

extern const EntityFunc beam_stateTable[];
extern u8 data_0212c4b8;

// Arrow waiting for its timer: animates, and removes the object when the timer runs out.
ARM void arrow_wait(Entity *e) {
    if (e->timer < 0xf) {
        InitAnimationForceUpdate(e, e->unk_23);
    } else {
        UpdateAnimationSingleFrame(e);
    }
    if (e->timer-- == 0) {
        PutObjWork(e);
    }
}

// Arrow in flight after its release: moves, applies gravity 0x2000 and removes itself once grounded.
ARM void arrow_kokin(Entity *e) {
    UpdateAnimationSingleFrame(e);
    MoveDir(e);
    if (UpdateGravity(e, 0x2000) != 0) {
        return;
    }
    PutObjWork(e);
}

// Beam main: same as Arrow but with the beam state table.
ARM void Beam(Entity *e) {
    if (data_0212c4b8 == 0) {
        beam_stateTable[e->action](e);
    }
    func_020857c8(e);
}

