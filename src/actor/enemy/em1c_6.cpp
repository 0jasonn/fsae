#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"
#include "actor/enemy/em1c.h"

// em1c attack state: runs the attack animation while bit 1 of the flags is set and restarts it when the frame flag 0x20
// shows up; when bit 7 is set the attack ends (action 5, direction recalculated by charMove).
void em1c_attack(Entity *e) {
    if (e->subtimer & 0x2) {
        UpdateAnimationSingleFrame(e);
        if (e->frame & 0x20) {
            e->subtimer &= 0xfd;
            e->frame &= 0xf;
        }
    }
    if (e->subtimer & 0x80) {
        e->action = 5;
        e->animationState = 0xff;
        charMove(e, 0);
    }
}
