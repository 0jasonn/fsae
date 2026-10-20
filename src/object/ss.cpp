#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"

// ss family (module ss), 0x0206d898 .. 0x0206da58.
// Address -> name: 0x0206d898 ss_panel, 0x0206d8f0 ss_cursor, 0x0206d90c ss_cur_init, 0x0206d9a8 ss_cur_move

ARM void ss_panel(Entity *e) {
    if (e->action == 0) {
        u8 nextAction = e->action + 1;

        e->action = nextAction;
        e->spriteSettings.b0 = 2;
        e->spriteSettings.b14 = 1;
        e->spriteSettings.b30 = 1;
        set_pos(e);
        InitAnimationForceUpdate(e, e->type);
    } else {
        UpdateAnimationSingleFrame(e);
    }
}

ARM void ss_cursor(Entity *e) {
    ssCursorTable[e->action](e);
}

ARM void ss_cur_init(Entity *e) {
    u8 nextAction = e->action + 1;

    e->action = nextAction;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b14 = 1;
    e->spriteSettings.b30 = 1;
    e->unk_16 = KNIFE_CURSOR_INDEX();
    set_pos(e);
    InitAnimationForceUpdate(e, e->type);
    ObjAnimMoveSet(e, &ssCurAnimBoundsA[KNIFE_CURSOR_INDEX() * 2], 1);
    e->spriteSettings.b0 = 0;
    e->child = GetSetWork(0x46, 0x14, 0);
    e->child->parent = e;
}

ARM void ss_cur_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    e->spriteSettings.b0 = 1;
    if (e->unk_16 != KNIFE_CURSOR_INDEX()) {
        e->unk_16 = KNIFE_CURSOR_INDEX();
        ObjAnimMoveSet(e, &ssCurAnimBoundsB[KNIFE_CURSOR_INDEX() * 2], 0x18);
        e->child->spriteSettings.b0 = 0;
    }
    if (ObjAnimMoveLine(e) == 0) {
        return;
    }
    if (KNIFE_CURSOR_INDEX() == 0) {
        return;
    }
    if (KNIFE_CURSOR_INDEX() < 6) {
        e->child->spriteSettings.b0 = 1;
    }
}
