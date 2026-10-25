#include "engine/functions.h"
#include "global.h"
#include "enemy/em18_units.h"
// Actor em18 (module em18), unit 4. Address -> name:
//   0x0203dc04 Em18

// Entry of the actor: type 0 runs its own handler, the other types pick the state from the dispatch table and set
// the sprite bits b30 and b14.
ARM void Em18(Entity *e) {
    if (e->type != 0) {
        func_02084700(e);
        data_020d2968[func_02084a30(e)](e);
        func_0208ae30(e);
        e->spriteSettings.b30 = 1;
        e->spriteSettings.b14 = 1;
    } else {
        em18_type0(e);
    }
}
