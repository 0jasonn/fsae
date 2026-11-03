#include "engine/functions.h"
#include "global.h"
#include "actor/object/ss.h"
#include "actor/object/effectdecls.h"

// effect_particle family (module effect_particle), 0x0206e93c .. 0x0206e9ac (dispatcher and init).
// Address -> name: 0x0206e93c effect_particle, 0x0206e958 effect_particle_init

// Action table of effect_particle, effectParticleTable
extern const EntityFunc effectParticleTable[];

void effect_particle(Entity *e) {
    effectParticleTable[e->action](e);
}

void effect_particle_init(Entity *e) {
    u8 action = e->action;

    e->action = action + 1;
    e->spriteSettings.b14 = 3;
    e->spriteSettings.b30 = 1;
    e->timer = 0;
    e->subtimer = 0;
    InitAnimationForceUpdate(e, e->type);
    effectPhaseTable[e->type2] = 0;
}

// effect_particle family (module effect_particle), 0x0206e9ac: the per-frame move of one particle.

typedef struct ParticleTab8 { s32 v[8]; } ParticleTab8;
typedef struct ParticleTab10 { s32 v[10]; } ParticleTab10;
typedef struct ParticleTab12 { s32 v[12]; } ParticleTab12;
extern const ParticleTab8 particleSpeedTable;     // particleSpeedTable
extern const ParticleTab10 particleXDivTable;     // particleXDivTable
extern const ParticleTab10 particleYDivTable;     // particleYDivTable
extern const ParticleTab12 particleXBaseTable;    // particleXBaseTable
extern const ParticleTab12 particleYBaseTable;    // particleYBaseTable
extern const s16 data_020c91fc[];

void effect_particle_move(Entity *e) {
    int kind;
    int kindForY;
    int off;
    e->unk_1b = 0xb0;
    e->spriteSettings.b20 = 6;
    e->spriteSettings.b16 = e->spriteSettings.b20;
    ParticleTab8 speedTab = particleSpeedTable;
    kind = e->type2;
    e->timer = e->timer + (u8)speedTab.v[kind];
    off = ((u16)(e->timer * 255) >> 4) * 2;
    ParticleTab12 xBaseTab = particleXBaseTable;
    ParticleTab12 yBaseTab = particleYBaseTable;
    ParticleTab10 xDivTab = particleXDivTable;
    ParticleTab10 yDivTab = particleYDivTable;

    e->x.HALF.HI = xBaseTab.v[kind] + 0x12 + data_020c91fc[off + 1] / xDivTab.v[kind];
    kindForY = e->type2;
    e->y.HALF.HI = yBaseTab.v[kindForY] + 8 + data_020c91fc[off] / yDivTab.v[kindForY];
    e->spriteSettings.b0 = 1;
    e->y.HALF.HI += 9;
    UpdateAnimationSingleFrame(e);
    if (effectPhaseTable[e->type2]++ > 0x400) {
        PutObjWork(e);
    }
}
