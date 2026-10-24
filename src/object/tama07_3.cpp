#include "engine/functions.h"
#include "global.h"
#include "object/tama07_3.h"

// tama07 unit 3 (module tama07), address -> name:
//   0x0207f5ec tama07_move
// tama07_2.cpp (tama07_remove) follows at 0x0207f830. tama07_guruguru (0x0207f670) is parked in scratch/agentC/nonmatching.

// tama07_move, 0x0207f5ec. Counts the timer down; while the child is alive and the timer runs, it toggles bit 0 of
// the sprite settings and clears bit 7 of the status flags at 0x1e. Otherwise the actor is removed.
ARM void tama07_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    e->timer = e->timer - 1;
    if (func_0208b644(e) == 0 || e->timer == 0) {
        tama07_remove(e);
        return;
    }
    func_0208af0c(e);
    if (e->timer == 0x1e) {
        e->statusFlags = e->statusFlags & 0x7f;
    }
    if (e->timer < 0x1e) {
        e->spriteSettings.b0 = e->spriteSettings.b0 ^ 1;
    }
}
