#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// rect_pair_init: function RectObjPair_init (0x020b8440), provisional name.

// Table of two entries (data_020deee0): the x position and the halfword w of each child
typedef struct RectPairInitEntry {
    s16 x;             // 0x00
    u16 w;             // 0x02
} RectPairInitEntry;
extern const RectPairInitEntry data_020deee0[2];

// Pair record: the value at +0x1e (see rect_item.cpp for the whole layout)
typedef struct RectPairInit {
    u8 unk_00[0x1e];
    s16 value;         // 0x1e
} RectPairInit;

// RectObjPair_init(self, holder, owner, pos, value) (0x020b8440, provisional name): creates the two children
// (RectObjList_create), gives each its geometry from data_020deee0 and the value of func_020bc200, sets the group items
// from pos and the fixed size 0x65 x 0x14, then stores value at +0x1e
extern "C" void RectObjPair_init(RectPairInit *self, void *holder, void *owner, s16 *pos, s16 value);
ARM void RectObjPair_init(RectPairInit *self, void *holder, void *owner, s16 *pos, s16 value) {
    void *items[2];
    s16 childPos[2];
    s16 childSize[2];
    s16 groupPos[2];
    s16 groupSize[2];
    void *child;
    s32 geomValue;
    s32 i;

    for (i = 0; i < 2; i++) {
        child = RectObjList_create(holder);
        childSize[0] = 0x33;
        childSize[1] = 0x14;
        childPos[1] = 0;
        childPos[0] = data_020deee0[i].x;
        geomValue = func_020bc200(owner, data_020deee0[i].w, data_020deee0[i].x);
        RectObjList_setGeometry(child, childPos, childSize, geomValue);
        items[i] = child;
    }
    groupSize[0] = 0x65;
    groupSize[1] = 0x14;
    groupPos[0] = pos[0];
    groupPos[1] = pos[1];
    RectObjList_setItems(self, holder, items, 2, groupPos, groupSize);
    self->value = value;
}
