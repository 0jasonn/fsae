#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Pot actor, hold check (module pot). Address -> name:
//   0x0205f0b4 throw_hold (original name)
//   (throw_holdoff at 0x0205f0e0 is in pot_4.cpp; pot_push at 0x0205f0f4 is parked)

ARM void throw_hold(Entity *e) {
    // PlayerData byte at 0x05 (unk_03[2]) of the player that holds the pot: nonzero means it is still held
    if (data_0212ceb0[e->type2].unk_03[2] != 0) {
        return;
    }
    throw_holdoff(e);
}
