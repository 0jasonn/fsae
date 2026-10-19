#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_a.h"

extern u8 data_021349c0[];

// Three u16 triples in rodata, one per type2 (ROM names lrCursorAnimTable / b8 / c0).
typedef struct LrCursorList {
    u16 v[3];
} LrCursorList;
extern const LrCursorList lrCursorAnimTable; // lrCursorAnimTable: animation per type2
extern const LrCursorList lrCursorYTable;    // lrCursorYTable: y offset per type2
extern const LrCursorList lrCursorXTable;    // lrCursorXTable: x offset per type2

// lr_cursor, 0x02069c20
ARM void lr_cursor(Entity *e) {
    LrCursorList xTable = lrCursorXTable;
    LrCursorList yTable = lrCursorYTable;
    LrCursorList animTable = lrCursorAnimTable;
    u8 nextAction;
    if (e->action == 0) {
        nextAction = e->action + 1;
        e->action = nextAction;
        e->spriteSettings.b30 = 0;
        e->spriteSettings.b14 = 0;
        e->spriteSettings.b0 = 2;
        e->x.HALF.HI = xTable.v[e->type2] + 8;
        e->y.HALF.HI = yTable.v[e->type2] + 0x10;
        InitAnimationForceUpdate(e, animTable.v[e->type2]);
    }
    e->unk_1b = 0xb3;
    e->spriteSettings.b16 = 6;
    e->spriteSettings.b0 = (data_021349c0[2] == e->type2) ? 2 : 0;
    UpdateAnimationSingleFrame(e);
    if (data_021349c0[8] >= 1) {
        PutObjWork(e);
    }
}
