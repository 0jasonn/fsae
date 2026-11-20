#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/slider_index_api.h"

// TODO(headers): declared in ui/widget/slider.h, which this file cannot include (its types clash with the
// ones used here); see the header restructure report.
extern "C" void SliderRing_setSelectedChild(void *self, s32 selected);

// TODO(headers): this declaration of RectGroup_updateItems differs from the shared one;
// see the header restructure report.
extern "C" void RectGroup_updateItems(void *self);
// TODO(headers): this declaration of Slider_setPosition differs from the shared one; see the header restructure report.
extern "C" void Slider_setPosition(void *self, s16 position);
// TODO(headers): this declaration of Slider_setPositionChecked differs from the shared one;
// see the header restructure report.
extern "C" s32 Slider_setPositionChecked(void *self, s16 position);

// Slider setup and selection helpers (0x020b9380 through 0x020b94ac); names and record types are provisional.

// Item of a slider: the vtable (slot 4 is called with the index) and the index byte at +0x29
typedef struct SliderItem {
    void *vtable;      // 0x00
    u8 unk_04[0x25];
    u8 index;          // 0x29
} SliderItem;

#define SLIDER_ITEM_CALL(item, i) ((void (*)(void *, s32))(((void **)((item)->vtable))[4]))((item), (i))

// Slider record: the first value at +0x20, the count at +0x24, the index at +0x2a (-1 when unset), the item array at +0x30
// and the flag byte at +0x3c
typedef struct SliderIndex {
    u8 unk_00[0x20];
    u16 unk_20;        // 0x20
    s16 unk_22;        // 0x22
    u16 count;         // 0x24
    s16 unk_26;        // 0x26
    s16 unk_28;        // 0x28
    s16 index;         // 0x2a
    s16 unk_2c;        // 0x2c
    u8 unk_2e[2];
    SliderItem **items;  // 0x30
    u8 unk_34[6];
    s16 unk_3a;        // 0x3a
    u8 flag;           // 0x3c
} SliderIndex;

// Set the item count, reset the page and selection state, and initialize each visible row.
void Slider_setupItems(void *selfv, s32 value) {
    SliderIndex *self = (SliderIndex *)selfv;
    s32 i;

    self->unk_20 = value;
    self->unk_28 = (s16)_s32_div_f(self->unk_20 + self->count - 1, self->count);
    RectGroup_updateItems(self);
    Slider_setPosition(self, 0);
    self->index = -1;
    self->unk_2c = -1;
    for (i = 0; i < (u16)(self->count + 1); i++) {
        self->items[i]->index = 0;
        SLIDER_ITEM_CALL(self->items[i], 0);
    }
}

// Slider_setIndex(self, value) (0x020b9424, provisional name): returns 0 when value is already the index and the flag is
// set; otherwise sets the flag, updates both sides through SliderRing_setSelectedChild around the new index and returns 1
s32 Slider_setIndex(void *selfv, s32 value) {
    SliderIndex *self = (SliderIndex *)selfv;
    if (self->index == value) {
        if (self->flag != 0) {
            return 0;
        }
    }
    self->flag = 1;
    SliderRing_setSelectedChild(self, 0);
    self->index = value;
    SliderRing_setSelectedChild(self, 1);
    return 1;
}

// Slider_setPositionFromIndex(self) (0x020b9478, provisional name): returns 0 while the index is -1, otherwise sets the
// position from the index divided by the count
s32 Slider_setPositionFromIndex(void *selfv) {
    SliderIndex *self = (SliderIndex *)selfv;
    if (self->index == -1) {
        return 0;
    }
    return Slider_setPositionChecked(self, (s16)_s32_div_f(self->index, self->count));
}
