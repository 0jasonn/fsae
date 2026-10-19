#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_a.h"

extern EntityFunc set35Table[];        // set35Table, indexed by action
extern const u8 set35Hitbox[];         // set35Hitbox

// Actor fields of the Set35 family, file-local.
typedef struct Vars_Set35 {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ s32 savedX;
    /* 64 */ s32 savedY;
    /* 68 */ s32 unk_68;
} Vars_Set35;

// set35 (dispatcher), 0x0206b068: runs the state function for the current action.
ARM void set35(Entity *e) {
    set35Table[e->action](e);
}

// set35_init, 0x0206b084
ARM void set35_init(Entity *e) {
    Vars_Set35 *v = VARS(Vars_Set35, e);
    u8 nextAction = e->action + 1;
    e->action = nextAction;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 0;
    e->hitbox = set35Hitbox;
    e->unk_40 = 0x38;
    e->poseId = 0x1f;
    e->statusFlags = 0xc9;
    e->unk_5c = 0x55;
    e->attackKnockback = -0x10 - (Random() & 7);
    v->savedX = e->x.HALF.HI;
    v->savedY = e->y.HALF.HI;
    v->unk_68 = e->type2 * 5 + 10;
    e->type2 = 0;
    InitAnimationForceUpdate(e, e->type);
}
