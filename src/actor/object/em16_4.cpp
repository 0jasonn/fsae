#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em16.h"
// em16_damage (0x0203cffc): hit reaction of em16; a hit in action 1 or 2 stops the actor, releases its child and turns it
// away from the hit before the generic knockback runs.
void em16_damage(Entity *e) {
    if (e->action - 1 <= 1 && e->contactFlags > 0x83) {
        e->action = 5;
        e->timer = 0x10;
        if (e->child != NULL) {
            e->child->parent = NULL;
        }
        e->direction = ((e->baseDirection ^ 0x10) + 4) & 0x18;
        e->animationState = e->direction >> 3;
        InitAnimationForceUpdate(e, em16_animTable[e->animationState]);
    }
    GenericKnockback(e, em16_stateTable);
}
