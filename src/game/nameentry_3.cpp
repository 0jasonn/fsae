#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/uiobject.h"

// Functions in this file (original names from the debug build):
//   nameEntryUIView::getPosFromSelIndex() const (0x020ae830), nameEntryUIView::getPosFromNameIndex() const (0x020ae8c0),
//   nameEntryUIView::getTextFromIndex(long) const (0x020ae908), nameEntryUIView_getSelectedText (0x020ae954, provisional name
//   nameEntryUIView_getSelectedText: the text of the entry at the cursor index in offset 0x4a)

extern u8 data_020deba8[];
extern u8 data_020debac[];
extern u8 data_02125560[];

extern "C" {
UIPos2 nameEntryUIView_getPosFromSelIndex(void *self);
UIPos2 nameEntryUIView_getPosFromNameIndex(void *self);
u16 nameEntryUIView_getTextFromIndex(void *self, s32 index);
const void *Knife_Comm_selectDataTable(s32 unused, s32 flag);
}

// nameEntryUIView::getPosFromSelIndex (0x020ae830): position of the selected entry; the index is at offset 0x46 when set,
// otherwise the entry at offset 0x4a
ARM UIPos2 nameEntryUIView_getPosFromSelIndex(void *self) {
    u8 *obj;
    s32 sel;
    s32 idx;
    UIPos2 pos;

    obj = (u8 *)self;
    sel = (s8)obj[0x46];
    if (sel != 0) {
        idx = sel - 1;
        pos.x = *(s32 *)(data_020deba8 + idx * 8) + 0x14;
        pos.y = *(s32 *)(data_020debac + idx * 8) + 8;
    } else {
        idx = (s16)*(s16 *)(obj + 0x4a) + 6;
        pos.x = *(s32 *)(data_02125560 + 0x10 + idx * 0x34) * 8 + 6;
        pos.y = *(s32 *)(data_02125560 + 0x14 + idx * 0x34) * 8 + 6;
    }
    return pos;
}

// nameEntryUIView::getPosFromNameIndex (0x020ae8c0): screen position of the name entry at the index in offset 0x42
ARM UIPos2 nameEntryUIView_getPosFromNameIndex(void *self) {
    u8 *obj;
    u8 *item;
    UIPos2 pos;

    obj = (u8 *)self;
    item = data_02125560 + (s32)(s8)obj[0x42] * 0x34;
    pos.x = *(s32 *)(item + 0x10) * 8 + 8;
    pos.y = *(s32 *)(item + 0x14) * 8 + 8;
    return pos;
}

// nameEntryUIView::getTextFromIndex (0x020ae908): the character of the entry; the first six are in the view, the others
// come from the table of the language flag
ARM u16 nameEntryUIView_getTextFromIndex(void *self, s32 index) {
    u8 *obj;
    s32 id;
    const void *table;

    obj = (u8 *)self;
    id = *(s32 *)(data_02125560 + index * 0x34) - 0x2328;
    if (index < 6) {
        return *(u16 *)(obj + 0x34 + index * 2);
    }
    table = Knife_Comm_selectDataTable((s32)self, (s8)obj[0x47]);
    return *(u16 *)((u8 *)table + (id - 6) * 2);
}

// nameEntryUIView_getSelectedText (0x020ae954): the character at the cursor (offset 0x4a, biased by 6)
ARM u16 nameEntryUIView_getSelectedText(void *self) {
    return nameEntryUIView_getTextFromIndex(self, (s16)*(s16 *)((u8 *)self + 0x4a) + 6);
}
