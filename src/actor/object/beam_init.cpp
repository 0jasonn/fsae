#include "engine/functions.h"
#include "engine/player.h"
#include "actor/object/beam.h"

// Beam (module beam): beam_init, the sword beam a player shoots at full health.

// Beam init: copies the owner's position, layer and facing, sets the beam's stats, hitbox and animation, then moves it
// once with beam_move.
void beam_init(Entity *e) {
    Entity *owner;
    u16 layer;

    owner = playerWork[e->type].entity;
    ObjPosCopy(owner, e);
    e->spriteSettings.b0 = 1;
    e->attackKnockback = 0xc;
    e->statusFlags = owner->statusFlags + 1;
    e->unk_5c = owner->unk_5c;
    e->hitbox = beam_hitbox;
    e->unk_40 = 0x23;
    e->poseId = 0x46;
    e->action++;
    e->speed = 0x380;
    e->unk_20 = 0;
    e->spriteSettings.b6 = 3;
    e->spriteSettings.b16 = 1;
    layer = e->layer;
    e->unk_1b = 0x7f;
    if ((layer & 0xc000) == 0x8000) {
        e->type2 = 1;
    }
    e->animationState = owner->animationState;
    e->direction = owner->animationState << 2;
    e->attackDamage = 4;
    VARS(BeamVars, e)->lifetime = 0x3c;
    InitAnimationForceUpdate(e, (e->animationState >> 1) + 0xc);
    func_02084180(e);
    MoveDir(e);
    EnqueueSFX(0x45);
    beam_move(e);
}
