#include "engine/functions.h"
#include "global.h"
#include "actor/object/pot.h"

// Functions in this file (original names from the debug build):
//   zelda_disp (0x0205fb9c)

// zelda_disp(e) (0x0205fb9c): picks the animation frame from the linked object's frame number (plus half the facing
// state while it is below 8) and restarts the animation when it changed
void zelda_disp(Entity *e) {
    u8 frame = (u8)(*(u16 *)e->linkedEntity & 0xff);

    if (frame < 8) {
        frame += (e->animationState / 2);
    }
    if (e->unk_23 == frame) {
        return;
    }
    InitAnimationForceUpdate(e, frame);
}
