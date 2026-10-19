#include "engine/functions.h"
#include "global.h"
#include "object/template.h"
#include "object/objdecls_a.h"

// Target position block at data_0212c7c8 + 0x80 (x and y of the heart's target), file-local view.
typedef struct HeartMarkerTarget {
    /* 00 */ u8 unk_00[0x80];
    /* 80 */ s16 targetX;
    /* 82 */ s16 targetY;
} HeartMarkerTarget;
extern HeartMarkerTarget data_0212c7c8;

// light_marker, 0x02069f5c: follows the actor template of its type2 (OBJ_TEMPLATE) and the animation.
ARM void light_marker(Entity *e) {
    u8 action = e->action;
    Entity *target;
    u8 nextAction;
    if (action == 0) {
        nextAction = action + 1;
        e->action = nextAction;
        e->spriteSettings.b0 = 2;
        e->spriteSettings.b16 = e->type2 + 7;
        e->spriteSettings.b14 = 1;
        e->spriteSettings.b30 = 0;
        InitAnimationForceUpdate(e, e->type);
    }
    target = OBJ_TEMPLATE(e->type2);
    e->x.HALF.HI = ((target->x.HALF.HI >> 4) & 0x3f) + 0x58;
    e->y.HALF.HI = ((target->y.HALF.HI >> 4) & 0x3f) + 0x30;
    UpdateAnimationSingleFrame(e);
}

// heart_marker, 0x02069ffc
ARM void heart_marker(Entity *e) {
    u8 action = e->action;
    u8 nextAction;
    if (action == 0) {
        nextAction = action + 1;
        e->action = nextAction;
        e->spriteSettings.b16 = 0;
        e->spriteSettings.b14 = 1;
        e->spriteSettings.b30 = 0;
        e->x.HALF.HI = ((data_0212c7c8.targetX >> 4) & 0x3f) + 0x58;
        e->y.HALF.HI = ((data_0212c7c8.targetY >> 4) & 0x3f) + 0x30;
        InitAnimationForceUpdate(e, e->type);
    }
    if (data_0212c7c8.targetX == 0) {
        e->spriteSettings.b0 = 0;
    } else {
        e->spriteSettings.b0 = 2;
        e->x.HALF.HI = ((data_0212c7c8.targetX >> 4) & 0x3f) + 0x58;
        e->y.HALF.HI = ((data_0212c7c8.targetY >> 4) & 0x3f) + 0x30;
    }
    UpdateAnimationSingleFrame(e);
}
