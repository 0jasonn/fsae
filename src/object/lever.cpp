#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_a.h"

extern s16 data_02115c78[];            // shared with door_silver_init, [type][3] flat
extern u8 data_021349c0[];
extern u16 data_0212c594[];

// lever, 0x020699a4
ARM void lever(Entity *e) {
    u8 action = e->action;
    u8 nextAction;
    s16 *pos;
    if (action == 0) {
        nextAction = action + 1;
        e->action = nextAction;
        e->spriteSettings.b30 = 0;
        e->spriteSettings.b14 = 0;
        e->spriteSettings.b0 = 2;
        e->spriteSettings.b16 = 5;
        pos = data_02115c78 + e->type * 3;
        e->x.HALF.HI = pos[0];
        e->y.HALF.HI = pos[1];
        InitAnimationForceUpdate(e, 2);
    }
    UpdateAnimationSingleFrame(e);
    if (data_021349c0[8] >= 1) {
        PutObjWork(e);
    }
}

// abutton, 0x02069a38
ARM void abutton(Entity *e) {
    u8 action = e->action;
    u8 nextAction;
    s16 *pos;
    if (action == 0) {
        nextAction = action + 1;
        e->action = nextAction;
        e->unk_1b = 0x6b;
        e->unk_20 = 0x40;
        e->spriteSettings.b30 = 0;
        e->spriteSettings.b14 = 0;
        e->spriteSettings.b0 = 2;
        e->spriteSettings.b6 = 2;
        e->spriteSettings.b16 = 5;
        pos = data_02115c78 + e->type * 3;
        e->x.HALF.HI = pos[0];
        e->y.HALF.HI = pos[1];
        InitAnimationForceUpdate(e, 0);
    }
    UpdateAnimationSingleFrame(e);
    if (data_021349c0[8] >= 1) {
        PutObjWork(e);
    }
}

// pwait, 0x02069ae4
ARM void pwait(Entity *e) {
    u8 action = e->action;
    u8 nextAction;
    s16 *pos;
    if (action == 0) {
        nextAction = action + 1;
        e->action = nextAction;
        e->unk_5e.b0 = 3;
        e->unk_1b = 0x4e;
        e->unk_20 = 0x80;
        e->spriteSettings.b30 = 0;
        e->spriteSettings.b14 = 0;
        e->spriteSettings.b6 = 3;
        e->spriteSettings.b16 = 1;
        pos = data_02115c78 + e->type * 3;
        e->x.HALF.HI = pos[0];
        e->y.HALF.HI = pos[1];
    }
    e->spriteSettings.b0 = (data_0212c594[0] & 0x10) ? 2 : 0;
    if (data_021349c0[8] >= 1) {
        PutObjWork(e);
    }
}

// breturn, 0x02069bac
ARM void breturn(Entity *e) {
    u8 action = e->action;
    u8 nextAction;
    if (action == 0) {
        nextAction = action + 1;
        e->action = nextAction;
        e->spriteSettings.b30 = 0;
        e->spriteSettings.b14 = 0;
        e->spriteSettings.b0 = 2;
        e->x.HALF.HI = 8;
        e->y.HALF.HI = 0xa0;
    }
    e->unk_1b = 0xb2;
    e->spriteSettings.b16 = 8;
    if (data_021349c0[8] >= 1) {
        PutObjWork(e);
    }
}
