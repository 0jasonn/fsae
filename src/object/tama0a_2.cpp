#include "engine/functions.h"
#include "game/stageseldecls.h"

// Tama0a actor family, second unit. Address -> name (original names from symbols.txt):
//   0x0207cd40 tama0a_type1_move, 0x0207cd98 Tama0c

// tama0a_type1_move, 0x0207cd40. Once the shot hits a wall (wall flags nonzero) it counts the timer down; when the
// timer ends or the wall is the 0xffff kind, it leaves a smoke puff and removes itself.
ARM void tama0a_type1_move(Entity *e) {
    s32 timer;
    UpdateAnimationSingleFrame(e);
    func_0208b628(e);
    if (e->wallFlags == 0) {
        return;
    }
    timer = e->timer - 1;
    e->timer = timer;
    if (e->wallFlags != 0xffff) {
        if ((timer & 0xff) != 0) {
            return;
        }
    }
    SKemuriSet(e);
    PutObjWork(e);
}

extern const EntityFunc data_020dcabc[]; // Tama0c action table, indexed by e->action

// Tama0c, 0x0207cd98. Runs the action of the current state.
ARM void Tama0c(Entity *e) {
    data_020dcabc[e->action](e);
}
