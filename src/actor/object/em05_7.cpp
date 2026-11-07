#include "engine/functions.h"
#include "global.h"

// Actor field of em05 at 0x7c, past the shared Entity fields: the pose id kept while the boss is hit
typedef struct Vars_em05Damage {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u8 savedPoseId;
} Vars_em05Damage;

extern const EntityFunc em05_actions[];

// em05_damage (0x02038ce8): hit reaction of the em05 boss; the knockback table is em05_actions
void em05_damage(Entity *e) {
    if (e->unk_43 != 0) {
        if (e->action == 2 || (e->type != 3 && e->action == 4)) {
            e->action++;
            e->timer = 0;
        }
        VARS(Vars_em05Damage, e)->savedPoseId = e->poseId;
        e->poseId = 6;
    }
    if (e->subAction == 0xff) {
        e->action = 2;
        e->subAction = 0;
        e->zVelocity = 0x18000;
        e->speed = 0x100;
        e->direction = e->baseDirection;
        e->poseId = 6;
        InitAnimationForceUpdate(e, (u8)(e->animationState + 4));
        EnqueueSFX(0x31);
        return;
    }
    GenericKnockback(e, em05_actions);
}
