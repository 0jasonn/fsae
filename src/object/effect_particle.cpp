#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"
#include "object/effectdecls.h"

// effect_particle family (module effect_particle), 0x0206e93c .. 0x0206e9ac (dispatcher and init).
// Address -> name: 0x0206e93c effect_particle, 0x0206e958 effect_particle_init

// Action table of effect_particle, effectParticleTable
extern const EntityFunc effectParticleTable[];

ARM void effect_particle(Entity *e) {
    effectParticleTable[e->action](e);
}

ARM void effect_particle_init(Entity *e) {
    u8 action = e->action;

    e->action = action + 1;
    e->spriteSettings.b14 = 3;
    e->spriteSettings.b30 = 1;
    e->timer = 0;
    e->subtimer = 0;
    InitAnimationForceUpdate(e, e->type);
    effectPhaseTable[e->type2] = 0;
}
