#include "engine/functions.h"
#include "global.h"

extern EntityFunc set30StateTable[];

// Set30 (0x02068dd0): counts the subtimer down and restarts the animation at zero, then runs the state function.
ARM void Set30(Entity *e) {
    if (e->subtimer != 0) {
        e->subtimer--;
        if (e->subtimer == 0) {
            InitAnimationForceUpdate(e, e->animationState);
        }
    }
    set30StateTable[e->action](e);
}
