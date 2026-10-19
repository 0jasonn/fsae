#include "enemy/actor_0204112c.h"
#include "global.h"

extern const u32 data_020cf9b8[];

// Enemy_CheckFlagThenFinish (0x02042424): on an odd frame, finishes when Enemy_SpawnPartPairWithSfx succeeds.
ARM void Enemy_CheckFlagThenFinish(Entity *e) {
    if (e->frame & 1) {
        if (Enemy_SpawnPartPairWithSfx(e) == 0) {
            return;
        }
        e->action = 3;
        e->timer = 0xf;
        e->unk_2e = 0;
        return;
    }
    UpdateAnimationSingleFrame(e);
}

// Enemy_UpdateParts (0x02042468): advances the two parts and this entity; when the timer runs out, sets
// the parts to their next animations.
ARM void Enemy_UpdateParts(Entity *e) {
    UpdateAnimationSingleFrame(VP(e)->partA);
    UpdateAnimationSingleFrame(VP(e)->partB);
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 4;
    InitAnimationForceUpdate(e, 1);
    InitAnimationForceUpdate(VP(e)->partA, 4);
    InitAnimationForceUpdate(VP(e)->partB, 5);
}

// Enemy_EndPartsOnFlag (0x020424cc): advances the parts; when the frame flag is set, clears the parent's flag and
// deletes both parts.
ARM void Enemy_EndPartsOnFlag(Entity *e) {
    UpdateAnimationSingleFrame(VP(e)->partA);
    UpdateAnimationSingleFrame(VP(e)->partB);
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 5;
    e->unk_2e = 8;
    e->parent->unk_6c[4] = 0;
    InitAnimationForceUpdate(e, 0);
    DeleteEntity(VP(e)->partA);
    DeleteEntity(VP(e)->partB);
}

// Enemy_StepDirectionWithParent (0x02042530): once the parent's low flags are 3, steps the direction; at a
// multiple of 0x40 it sets action 6 and marks the parent with a bit from data_020cf9b8.
ARM void Enemy_StepDirectionWithParent(Entity *e) {
    Entity *parent = e->parent;
    if ((parent->unk_6c[4] & 3) != 3) {
        return;
    }
    e->direction += (u8)(s8)e->unk_6c[5];
    if ((e->direction & 0x3f) != 0) {
        return;
    }
    e->action = 6;
    e->unk_6c[6] &= 0xfe;
    parent->unk_6c[4] |= (u8)data_020cf9b8[e->type2 + 2];
}

// Enemy_ActivateWhenParentClear (0x020425a4): when the parent's flag byte is clear, switches to action 7 and sets
// the sprite bits (b30 copied into b14).
ARM void Enemy_ActivateWhenParentClear(Entity *e) {
    if (e->parent->unk_6c[4] != 0) {
        return;
    }
    e->action = 7;
    e->spriteSettings.b30 = 1;
    e->spriteSettings.b14 = e->spriteSettings.b30;
    e->unk_6c[5] = 2;
}

// Enemy_SnapToCardinalTurn (0x020425e8): steps the direction; when it reaches 0xc0 or 0x40 with the parent
// flag set, switches to action 8 and toggles the parent's bit from data_020cf9b8.
ARM void Enemy_SnapToCardinalTurn(Entity *e) {
    Entity *parent = e->parent;
    e->direction += (u8)(s8)e->unk_6c[5];
    if (parent->unk_6c[4] == 0) {
        return;
    }
    if ((u8)e->direction == 0xc0) {
        e->action = 8;
        e->unk_6c[5] = 0xff;
        e->unk_6c[6] |= 1;
        parent->unk_6c[4] ^= (u8)data_020cf9b8[e->type2];
        e->spriteSettings.b30 = 2;
        e->spriteSettings.b14 = e->spriteSettings.b30;
        return;
    }
    if ((u8)e->direction == 0x40) {
        e->action = 8;
        e->unk_6c[5] = 1;
        e->unk_6c[6] |= 1;
        parent->unk_6c[4] ^= (u8)data_020cf9b8[e->type2];
        e->spriteSettings.b30 = 2;
        e->spriteSettings.b14 = e->spriteSettings.b30;
    }
}
