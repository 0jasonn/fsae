#include "object/option.h"

// Option panel screen, fourth unit (module option). Address -> name:
//   0x0205c54c change_panel, 0x0205c618 entry_cursor, 0x0205c6a8 star_cursor, 0x0205c6fc langStar
//   0x0205c770 star_adjust

ARM void change_panel(Entity *e) {
    u8 layer;

    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 2;
        if (data_021348d8 == 0) {
            e->unk_21 = 9;
            e->unk_20 = e->type2 << 3;
        } else {
            if (e->type2 == 4) {
                PutObjWork(e);
                return;
            }
            e->unk_21 = 10;
            e->x.HALF.HI += e->type2 * 13;
            e->unk_20 = e->type2 * 10;
        }
    }
    if (data_021349c0[NP_CURSOR_ROW] == 5 && data_021349c0[NP_CURSOR_TYPE] == e->type2) {
        layer = 5;
    } else {
        layer = 6;
    }
    e->spriteSettings.b16 = layer;
}

ARM void entry_cursor(Entity *e) {
    u8 offset;
    int x;

    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 2;
        e->spriteSettings.b30 = 0;
        e->spriteSettings.b14 = 0;
        InitAnimationForceUpdate(e, 1);
    }
    if (data_021349c0[0x22] >= 6) {
        x = 0x4c;
    } else {
        x = (data_021349c0[0x22] << 3) + 0x24;
    }
    e->y.HALF.HI = 0xd;
    e->x.HALF.HI = x;
    offset = data_0212c594 >> 2 & 7;
    e->z.HALF.HI = entry_z_table[offset];
    UpdateAnimationSingleFrame(e);
}

ARM void star_cursor(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b14 = 2;
        e->spriteSettings.b30 = 2;
        InitAnimationForceUpdate(e, 2);
        NP_ENTITY_PTR(8) = e;
    }
    UpdateAnimationSingleFrame(e);
}

ARM void langStar(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 2;
        e->x.HALF.HI = e->type2 * 0xb0 + 0x20;
        InitAnimationForceUpdate(e, 2);
    }
    e->y.HALF.HI = (data_021348d8 - 1) * 0x1c - 2;
    UpdateAnimationSingleFrame(e);
}

ARM void star_adjust(Entity *e, s16 a, s16 b) {
    Entity *star = NP_ENTITY_PTR(8);

    if (star == NULL) {
        return;
    }
    star->x.HALF.HI = e->x.HALF.HI + a;
    star->y.HALF.HI = e->y.HALF.HI + b;
    star->spriteSettings.b0 = 2;
}
