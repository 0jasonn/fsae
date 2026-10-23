#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"
#include "enemy/em1c.h"

// Actor em1c (original names from the debug build for em1c_normal, em1c_init, em1c_waitSet, charMove).
// Em1c and em1c_damage are the main and damage wrappers, named through scratch/agentE/renames.txt.

ARM void Em1c(Entity *e) {
    EnemyFunctionHandler(e, em1c_actions);
}

ARM void em1c_normal(Entity *e) {
    if (e->action != 0) {
        EmMagneMove(e, 0x80);
    }
    em1c_normalActions[e->action](e);
}

ARM void em1c_damage(Entity *e) {
    GenericKnockback(e, em1c_actions);
}

ARM void em1c_init(Entity *e) {
    Vars_Em1c *vars = VARS(Vars_Em1c, e);
    Entity *tama;

    tama = EmGetTama(e, 6, 0);
    if (tama == NULL) {
        return;
    }
    tama->parent = e;
    e->child = tama;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 5;
    e->statusFlags |= 0x80;
    e->hitbox = em1c_hitbox;
    em1c_waitSet(e);
    e->animationState = 0xff;
    e->direction = Random() & 0x18;
    vars->grabbed = NULL;
    em1c_sharedState.timer = 0;
    em1c_sharedState.unk_00 = 0;
}
