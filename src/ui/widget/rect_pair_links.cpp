#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/rect_links.h"

// rect_pair_links: function RectObjPair_initWithLinks (0x020b87b4), provisional name.

// Pair of RectObjList records: the group geometry at +0x4 to +0xa, the items at +0x14 and their count at +0x18, the
// offset at +0x1c and two halfwords at +0x20
typedef struct RectLinkPair {
    void *vtable;      // 0x00
    s16 offsetX;       // 0x04
    s16 offsetY;       // 0x06
    s16 sizeX;         // 0x08
    s16 sizeY;         // 0x0a
    u8 unk_0c[8];      // 0x0c
    void **items;      // 0x14
    u16 count;         // 0x18
    u8 unk_1a[2];      // 0x1a
    s16 offset;        // 0x1c
    s16 unk_1e;        // 0x1e
    s16 unk_20[2];     // 0x20
} RectLinkPair;

// RectObjPair_initWithLinks(self, holder, owner, pos, value, offset, widths) (0x020b87b4, provisional name): creates two
// RectObjLink children (func_020b88b0) with the position (0, 0) and the size (0xd, 8), gives each the value of
// func_020bc200 (owner, widths[i]), sets the group items from pos and the size (0xd, value), calls
// RectObjPair_setOffsets with value, stores offset at +0x1c and 8 into both halfwords at +0x20
extern "C" void RectObjPair_initWithLinks(RectLinkPair *self, void *holder, void *owner, s16 *pos, s16 value, s16 offset,
                                          u16 *widths);
void RectObjPair_initWithLinks(RectLinkPair *self, void *holder, void *owner, s16 *pos, s16 value, s16 offset,
                                   u16 *widths) {
    void *items[2];
    s16 childPos[2];
    s16 childSize[2];
    s16 groupPos[2];
    s16 groupSize[2];
    void *child;
    s32 geomValue;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        child = func_020b88b0(holder);
        childSize[0] = 0xd;
        childSize[1] = 8;
        childPos[0] = 0;
        childPos[1] = 0;
        geomValue = func_020bc200(owner, widths[i]);
        RectObjLink_setGeometry(child, childPos, childSize, geomValue);
        items[i] = child;
    }
    groupSize[0] = 0xd;
    groupSize[1] = value;
    groupPos[0] = pos[0];
    groupPos[1] = pos[1];
    RectObjList_setItems(self, holder, items, 2, groupPos, groupSize);
    RectObjPair_setOffsets(self, value);
    self->offset = offset;
    for (j = 0; j < 2; j++) {
        self->unk_20[j] = 8;
    }
}
