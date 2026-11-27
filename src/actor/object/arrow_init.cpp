#include "engine/functions.h"
#include "engine/player.h"
#include "actor/object/arrow.h"

// Arrow (module arrow): arrow_init.

// Arrow init. The owner is the entity of the player that shot it (playerWork[type]). With subtimer 0 this is the arrow
// held on the bow: it becomes the owner's weapon and spawns the bow effect. Otherwise it is a flying arrow that takes
// its direction, position, layer and hitbox from the owner.
void arrow_init(Entity *e) {
    Entity *effect;
    Entity *owner;
    u16 layer;

    owner = playerWork[e->type].entity;
    e->spriteSettings.b16 = 0;
    e->action++;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b14 = owner->spriteSettings.b14;
    e->unk_5e.b0 = owner->unk_5e.b0;
    e->animationState = owner->animationState;

    if (e->subtimer != 0) {
        e->attackKnockback = 0xf;
        e->unk_40 = 0x15;
        e->poseId = 4;
        VARS(ArrowVars, e)->lifetime = 0x6a;
        e->unk_1b = 9;
        if (e->attackDamage > 3) {
            e->speed = 0x400;
        } else {
            e->speed = 0x300;
        }
        e->direction = (owner->animationState & 0xe) << 2;
        e->unk_20 = 0xc0;
        e->spriteSettings.b6 = 3;
        e->x.HALF.HI = owner->x.HALF.HI + arrow_spawnOffsets[e->animationState];
        e->y.HALF.HI = owner->y.HALF.HI + arrow_spawnOffsets[1 + e->animationState];
        layer = owner->layer;
        if ((layer & 0xc000) == 0x8000) {
            e->type2 = 1;
        }
        e->layer = layer;
        e->spriteSettings.b30 = owner->spriteSettings.b30;
        if (e->animationState == 2) {
            VARS(ArrowVars, e)->hitOffsetX = 5;
            e->spriteSettings.flipX = 1;
        } else if (e->animationState == 0) {
            VARS(ArrowVars, e)->hitOffsetY = -5;
        } else if (e->animationState == 4) {
            e->spriteSettings.b3 = 1;
            VARS(ArrowVars, e)->hitOffsetY = 5;
        } else {
            VARS(ArrowVars, e)->hitOffsetX = -5;
        }
        if (e->animationState == 2 || 6 == e->animationState) {
            e->hitbox = arrow_hitboxSideways;
            e->unk_23 = 1;
        } else {
            e->hitbox = arrow_hitboxUpDown;
            e->unk_23 = 2;
        }
        func_02084180(e);
        if (e->attackDamage > 3) {
            e->unk_23 += 0xd;
        }
        InitAnimationForceUpdate(e, e->unk_23);
        func_02085f98(playerWork[e->type].entity, 2);
        e->statusFlags = owner->statusFlags + 1;
        e->unk_5c = owner->unk_5c;
    } else {
        playerWork[e->type].weapon = e;
        func_0208ab14(e, owner);
        e->attackDamage = 3;
        e->unk_1b = 0x62;
        e->unk_20 = owner->unk_20;
        e->spriteSettings.b6 = owner->spriteSettings.b6;
        if ((owner->animationState >> 1) == 1) {
            e->spriteSettings.flipX = 1;
        }
        effect = GetSetWork(0x52, e->type, 1);
        if (effect != NULL) {
            effect->x.WORD = e->x.WORD;
            effect->y.WORD = e->y.WORD;
        }
    }
}
