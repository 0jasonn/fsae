#include "engine/functions.h"
#include "global.h"
#include "object/set43.h"

// Set43 family (module set43), 0x0206cac8 .. 0x0206cb1c.
// Address -> name: 0x0206cac8 set43_move

ARM void set43_move(Entity *e) {
    if ((frameCounter & 0x3f) == 0) {
        setwind(e);
    }
    if (e->linkedEntity != NULL) {
        if (switchcheck(e) == 0) {
            e->action = 4;
        }
    }
    plmove(e);
    UpdateAnimationSingleFrame(e);
}
