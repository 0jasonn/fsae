#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Opening logo actors, sub title and sword (module oplogo). Address -> name:
//   0x02067ed0 oplogo_sub_title (original name, state table data_02115b60 indexed by e->action)
//   0x02067eec oplogo_sub_title_init (original name)
//   0x02067f48 oplogo_sub_title_appear (original name)
//   0x02067f74 oplogo_NoOp (empty state)
//   0x02067f78 oplogo_sword (original name, state table data_02115b90 indexed by e->action)
//   0x02067f94 oplogo_sword_init (original name)
//   0x02067ff0 oplogo_sword_move (original name)

extern EntityFunc data_02115b60[]; // state table indexed by e->action
extern EntityFunc data_02115b90[]; // state table indexed by e->action

ARM void oplogo_sub_title(Entity *e) {
    data_02115b60[e->action](e);
}

ARM void oplogo_sub_title_init(Entity *e) {
    e->spriteSettings.b0 = 2;
    e->spriteSettings.b14 = 0;
    e->spriteSettings.b30 = 1;
    SPRITE_WORD(e) |= 0x2000;
    e->action = e->action + 1;
    e->x.HALF.HI = 0x100;
    e->y.HALF.HI = 0x60;
    e->direction = 0x18;
    e->speed = 0x810;
    InitAnimationForceUpdate(e, e->type);
}

ARM void oplogo_sub_title_appear(Entity *e) {
    MoveDir(e);
    if (e->x.HALF.HI < 0x80) {
        e->x.HALF.HI = 0x80;
        e->action = e->action + 1;
    }
}

ARM void oplogo_NoOp(Entity *e) {
}

ARM void oplogo_sword(Entity *e) {
    data_02115b90[e->action](e);
}

ARM void oplogo_sword_init(Entity *e) {
    e->spriteSettings.b0 = 2;
    e->spriteSettings.b14 = 0;
    e->spriteSettings.b30 = 1;
    e->action = e->action + 1;
    SPRITE_WORD(e) |= 0x2000;
    e->x.HALF.HI = 0x108;
    e->y.HALF.HI = 0x118;
    e->speed = 0xc00;
    e->direction = 0x1d;
    InitAnimationForceUpdate(e, e->type);
}

ARM void oplogo_sword_move(Entity *e) {
    MoveDir(e);
    if (e->y.HALF.HI > 0x60) {
        return;
    }
    e->y.HALF.HI = 0x60;
    GetSetWork(0x28, 5, 1);
    e->timer = 0x3a;
    e->action = e->action + 1;
    SoundReq(0x223);
}
