#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/em00.h"

// Functions in this file (actor em00):
//   em00_main -> em00_main, em00_normal -> em00_normal, em00_knockback -> em00_knockback,
//   em00_init -> em00_init, em00_move -> em00_move, em00_wait -> em00_wait, em00_attack -> em00_attack,
//   getmoveinfo getmoveinfo, Em0a, em0a_normal, em0a_damage, em0a_init (original names where listed)

// Main of the actor: runs the state table for the entity.
ARM void em00_main(Entity *e) {
    EnemyFunctionHandler(e, data_020cfd14);
}

// Normal state: runs the handler of the current action.
ARM void em00_normal(Entity *e) {
    data_020cfcac[e->action](e);
}

// Knockback: runs the generic knockback with the actor table.
ARM void em00_knockback(Entity *e) {
    GenericKnockback(e, data_020cfd14);
}

// Starts the actor: random subtimer, sprite bits, hitbox, first animation and the move info.
ARM void em00_init(Entity *e) {
    e->action = 1;
    e->subtimer = (Random() & 0x3f) + 0xb4;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->hitbox = data_020cfc74;
    InitAnimationForceUpdate(e, 0);
    getmoveinfo(e);
}

// Moves the actor: the subtimer ends the movement phase, the timer picks the next movement.
ARM void em00_move(Entity *e) {
    e->subtimer -= 1;
    if (e->subtimer == 0) {
        e->action = 3;
        InitAnimationForceUpdate(e, (u8)(e->animationState + 4));
        return;
    }
    e->timer -= 1;
    if (e->timer == 0) {
        e->action = 2;
        e->timer = data_020cfc6c[Random() & 3];
        InitAnimationForceUpdate(e, (u8)(e->animationState + 4));
    }
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
}

// Waits for the timer and then asks for the move info again.
ARM void em00_wait(Entity *e) {
    e->timer -= 1;
    if (e->timer != 0) {
        return;
    }
    e->action = 1;
    getmoveinfo(e);
}

// Attack: when the frame is 1 an effect object follows the actor; when the frame has bit 7 the actor goes back to wait.
ARM void em00_attack(Entity *e) {
    Entity *effect;

    UpdateAnimationSingleFrame(e);
    if (e->frame == 1) {
        e->frame = 0;
        effect = EmGetTama(e, 4, 0);
        if (effect == 0) {
            return;
        }
        effect->x.HALF.HI += data_020cfc7c[e->animationState * 2];
        effect->y.HALF.HI += data_020cfc7c[e->animationState * 2 + 1];
        effect->direction = e->direction;
        EnqueueSFX(0x2a);
        return;
    }
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action = 2;
    e->timer = 0x1e;
    e->subtimer = (Random() & 0x3f) + 0xb4;
    InitAnimationForceUpdate(e, (u8)(e->animationState + 4));
}

// Picks a random direction and animation for the move and starts the animation.
ARM void getmoveinfo(Entity *e) {
    s32 dirBits;

    e->timer = data_020cfc70[Random() & 3];
    dirBits = Random() & 0x18;
    e->direction = dirBits;
    e->animationState = dirBits >> 3;
    InitAnimationForceUpdate(e, e->animationState);
}

// Actor main of the em0a unit: a check of the counter, then the handler for the state of the entity.
ARM void Em0a(Entity *e) {
    if (*(u16 *)(data_0212c540 + 2) > 1) {
        func_02084700(e);
    }
    data_020cfd70[func_02084a30(e)](e);
}

// Normal state of em0a: runs the handler of the current action.
ARM void em0a_normal(Entity *e) {
    data_020cfd5c[e->action](e);
}

// Damage of em0a: when the attached work exists its position is copied and the hit sound plays.
ARM void em0a_damage(Entity *e) {
    Entity *work;

    work = GetSetWork(0xf, 5, 0x40);
    if (work != 0) {
        ObjPosCopy(e, work);
        func_02085f98(e, 0x221);
    }
    PutObjWork(e);
}

// Starts em0a: sprite bits, the hitbox and the animation of the first state.
ARM void em0a_init(Entity *e) {
    u32 sprite;

    sprite = e->spriteSettings.b0; // the original reads the sprite bits before it writes the action
    e->spriteSettings.b0 = 1;
    e->unk_2e = 3;
    e->hitbox = data_020cfd54;
    e->action = e->action + 1;
    e->timer = 0x40;
    e->subtimer = 0x10;
    e->child = 0;
    if (data_0212c7c8[0x8e] == 3 || data_0212c7c8[0x8e] == 5) {
        e->spriteSettings.b20 = 5;
        e->spriteSettings.b16 = e->spriteSettings.b20;
    }
    InitAnimationForceUpdate(e, 0);
}
