#include "engine/functions.h"
#include "global.h"
#include "object/template.h"

// Tame actor (module tame). Address -> name:
//   0x020701b8 tame_dispatch (provisional, runs the action table of the actor)
//   0x020701d4 tame_init, 0x020702c8 tame_move (original names)

typedef struct Vars_Tame {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u16 unk_64;
    /* 66 */ u8 unk_66[4];
    /* 6a */ u16 unk_6a;
} Vars_Tame;

extern const EntityFunc tame_actions[]; // indexed by e->action
void tame_move(Entity *e);

ARM void tame_dispatch(Entity *e) {
    tame_actions[e->action](e);
}

ARM void tame_init(Entity *e) {
    Entity *tmpl;

    tmpl = OBJ_TEMPLATE(e->type);
    e->unk_5e.b0 = 3;
    e->spriteSettings.b30 = tmpl->spriteSettings.b30;
    e->action++;
    e->animationState = tmpl->animationState >> 1;
    e->direction = ((e->animationState + 1) & 3) << 3;
    e->subtimer = 6;
    VARS(Vars_Tame, e)->unk_64 = 0;
    VARS(Vars_Tame, e)->unk_6a = 0;
    e->speed = 0x140;
    e->unk_20 = 0x3c;
    e->spriteSettings.b6 = 3;
    e->spriteSettings.b16 = 6;
    e->unk_1b = 0x2a;
    InitAnimationForceUpdate(e, 7);
    if (e->type2 != 0) {
        e->timer = 0x46;
        return;
    }
    e->spriteSettings.b0 = 1;
    e->timer = 0x28;
    tame_move(e);
}
