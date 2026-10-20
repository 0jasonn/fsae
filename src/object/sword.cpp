#include "engine/functions.h"
#include "game/stageseldecls.h"

// Sword, 0x0207af58. Sword actor: runs the action of the current state while data_0212c4b8 is zero, then the
// common update.
ARM void Sword(Entity *e) {
    if (data_0212c4b8 == 0) {
        data_020dc71c[e->action](e);
    }
    func_020857c8(e);
}
