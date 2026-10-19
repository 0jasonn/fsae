#include "engine/functions.h"
#include "enemy/em09.h"
#include "global.h"

// Function names (dsd -> name), also in scratch/agentA/renames.txt:
// em10_damage em10_damage, em10_init em10_init, Boss_NoOp Boss_NoOp,
// em10_awake em10_awake, em10_move em10_move, em10_endmove0 em10_endmove0,
// em10_endmove1 em10_endmove1, em10_sleep em10_sleep

ARM void em10_damage(Entity *e) {
    if (e->action == 1) {
        e->action = 2;
        if (e->contactedEntity->objKind == 1) {
            VBP(e)->target = e->contactedEntity;
        } else if (e->contactedEntity->type < data_0212c7c8.unk_0) {
            VBP(e)->target = data_0212ceb0[e->contactedEntity->type].entity;
        } else {
            VBP(e)->target = EmGetAimPl();
        }
        e->direction = GetFacingDirection(e, e->contactedEntity);
        EnqueueSFX(0x30);
    }
    GenericKnockback(e, em10_actions);
}

ARM void em10_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->hitbox = em10_hitbox;
    InitAnimationForceUpdate(e, 4);
    e->action = 1;
    e->animationState = 0xff;
    attset(e);
}

ARM void Boss_NoOp(Entity *e) {
}

ARM void em10_awake(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 1) {
        u8 wobbleTimer = ++e->timer;
        if ((wobbleTimer & 1) != 0) {
            e->x.HALF.HI += em10_awakeSway[(wobbleTimer & 6) >> 1];
        }
        return;
    }
    if (e->frame == 2) {
        e->frame = 0;
        e->unk_5c = 0x21ff;
        e->poseId = 0x1c;
        e->hitbox = em10_awakeHitbox;
        attreset(e);
        return;
    }
    if ((e->frame & 0x80) != 0) {
        e->action = 3;
        e->subtimer = 0x10;
        VBH(e)->moveTimer = 0x258;
        {
            int targetDir = func_02084fd0(e, VBP(e)->target);
            int facing = (targetDir + 4) & 0x18;
            e->direction = facing;
            e->animationState = facing >> 3;
            InitAnimationForceUpdate(e, e->animationState);
        }
    }
}

ARM void em10_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    func_020847a0(e);
    if (--e->subtimer == 0) {
        e->subtimer = 0x10;
        dirSet(e);
        {
            u8 anim = e->direction >> 3;
            if (anim != e->animationState) {
                e->animationState = anim;
                InitAnimationForceUpdate(e, anim);
            }
        }
    }
    if (--VBH(e)->moveTimer == 0) {
        e->action = 4;
    }
}

ARM void em10_endmove0(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (poscheck(e) != 0) {
        nextendmoveset(e);
        return;
    }
    if (func_020847a0(e) != 0) {
        return;
    }
    if (func_02083d28(e) == 0xf) {
        e->health = 0;
        return;
    }
    {
        int reversedDir = e->direction ^ 0x10;
        e->direction = reversedDir;
        InitAnimationForceUpdate(e, (reversedDir & 0xff) >> 3);
    }
}

ARM void em10_endmove1(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (poscheck(e) != 0) {
        sleepSet(e);
        return;
    }
    if (func_020847a0(e) != 0) {
        return;
    }
    if (func_02083d28(e) == 0xf) {
        e->health = 0;
        return;
    }
    {
        int reversedDir = e->direction ^ 0x10;
        e->direction = reversedDir;
        InitAnimationForceUpdate(e, (reversedDir & 0xff) >> 3);
    }
}

ARM void em10_sleep(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 1) {
        if (func_02083d28(e) == 0xf) {
            e->health = 0;
            return;
        }
        e->frame = 0;
        e->unk_5c = 0x2055;
        e->poseId = 1;
        e->hitbox = em10_hitbox;
        attset(e);
        return;
    }
    if ((e->frame & 0x80) != 0) {
        e->action = 1;
        InitAnimationForceUpdate(e, 4);
    }
}
