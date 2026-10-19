#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_a.h"

extern EntityFunc cursorTable[];       // cursorTable
extern u8 cursorInitTable[][3];        // cursorInitTable: start x, start y, animation per type2
extern u8 data_021349c0[];

// Actor fields of the cursor, file-local.
typedef struct Vars_Cursor {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u16 circleRadius; // grows by 4 per frame while the circle window opens
} Vars_Cursor;

ARM void door_cursor(Entity *e) {
    cursorTable[e->action](e);
}

ARM void cursor_init(Entity *e) {
    u8 nextAction = e->action + 1;
    u8 *init;
    e->action = nextAction;
    e->spriteSettings.b30 = 0;
    e->spriteSettings.b14 = 0;
    init = cursorInitTable[e->type2];
    e->x.HALF.HI = init[0];
    e->y.HALF.HI = init[1];
    InitAnimationForceUpdate(e, init[2]);
}

ARM void cursor_move(Entity *e) {
    u32 flag;
    if (data_021349c0[2] == e->type2) {
        flag = 2;
    } else {
        flag = 0;
    }
    *(u32 *)&e->spriteSettings = (*(u32 *)&e->spriteSettings & ~3) | (flag & 3);
    UpdateAnimationSingleFrame(e);
    if (data_021349c0[8] == 1) {
        PutObjWork(e);
    }
}

ARM void cursor_effect(Entity *e) {
    Vars_Cursor *v = VARS(Vars_Cursor, e);
    UpdateAnimationSingleFrame(e);
    switch (e->subAction) {
    case 0:
        InitCircleWindow(0x1f, 0x3f);
        MakeCircleWindow(e->x.HALF.HI, e->y.HALF.HI, 0);
        v->circleRadius = 0;
        FadeSet(2, 8);
        e->subAction++;
        break;
    case 1:
        if (v->circleRadius < 0x12c) {
            v->circleRadius += 4;
            MakeCircleWindow(e->x.HALF.HI, e->y.HALF.HI, v->circleRadius);
        } else {
            u8 nextAction = e->action + 1;
            e->subAction = 0;
            e->action = nextAction;
            StopEffectWindow();
        }
        break;
    }
}

ARM void cursor_wait(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (data_021349c0[8] < 2) {
        return;
    }
    PutObjWork(e);
}
