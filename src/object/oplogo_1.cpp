#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Opening logo actors, title and sub title (module oplogo). Address -> name:
//   0x02067d68 oplogo_typeDispatch (per-type handler table data_02115bac indexed by e->type)
//   0x02067d84 oplogo_title (original name, state table data_02115b84 indexed by e->action)
//   0x02067da0 oplogo_title_init (original name)
//   0x02067e14 oplogo_title_appear (original name)
//   0x02067e50 oplogo_title_move (original name)
//   (oplogo_sub_title at 0x02067ed0 is in the next unit)

extern EntityFunc data_02115bac[]; // handler per type
extern EntityFunc data_02115b84[]; // state table indexed by e->action
extern u8 data_0212c4dc; // stage counter, the title moves once it reaches 3

typedef struct Vars_Oplogo {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u16 holdTimer; // frames to wait before the appear step
} Vars_Oplogo;

ARM void oplogo_typeDispatch(Entity *e) {
    data_02115bac[e->type](e);
}

ARM void oplogo_title(Entity *e) {
    data_02115b84[e->action](e);
}

ARM void oplogo_title_init(Entity *e) {
    e->spriteSettings.b0 = 2;
    e->spriteSettings.b14 = (e->type == 0) ? 2 : 1;
    e->spriteSettings.b30 = 1;
    e->action = e->action + 1;
    SPRITE_WORD(e) |= 0x2000;
    e->timer = 7;
    e->x.HALF.HI = 0x80;
    e->y.HALF.HI = 0x60;
    InitAnimationForceUpdate(e, e->type);
}

ARM void oplogo_title_appear(Entity *e) {
    Vars_Oplogo *v = VARS(Vars_Oplogo, e);

    if (*(u16 *)data_0212c594 & 1) {
        return;
    }
    if (e->timer != 0) {
        e->timer = e->timer - 1;
    } else {
        v->holdTimer = 0x32;
        e->action = e->action + 1;
    }
}

ARM void oplogo_title_move(Entity *e) {
    Vars_Oplogo *v = VARS(Vars_Oplogo, e);

    if (data_0212c4dc != 3) {
        return;
    }
    if ((Random() & 0x7f) == 0) {
        GetSetWork(0x28, 9, Random() & 3);
    }
    if (e->subtimer != 0) {
        return;
    }
    v->holdTimer = v->holdTimer - 1;
    if (v->holdTimer != 0) {
        return;
    }
    GetSetWork(0x28, 5, 0);
    v->holdTimer = (Random() & 0xff) + 0x46;
}
