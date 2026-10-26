#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// slider_index: functions Slider_setIndex (0x020b9424) and Slider_setPositionFromIndex (0x020b9478), provisional names.
// Slider_setupItems (0x020b9380) is parked in scratch/agentF/nonmatching.

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

// Slider_setIndex(self, value) (0x020b9424, provisional name): returns 0 when value is already the index and the flag is
// set; otherwise sets the flag, updates both sides through func_020b9774 around the new index and returns 1
ARM s32 Slider_setIndex(void *selfv, s32 value) {
    SliderIndex *self = (SliderIndex *)selfv;
    if (self->index == value) {
        if (self->flag != 0) {
            return 0;
        }
    }
    self->flag = 1;
    func_020b9774(self, 0);
    self->index = value;
    func_020b9774(self, 1);
    return 1;
}

// Slider_setPositionFromIndex(self) (0x020b9478, provisional name): returns 0 while the index is -1, otherwise sets the
// position from the index divided by the count
ARM s32 Slider_setPositionFromIndex(void *selfv) {
    SliderIndex *self = (SliderIndex *)selfv;
    if (self->index == -1) {
        return 0;
    }
    return Slider_setPositionChecked(self, (s16)_s32_div_f(self->index, self->count));
}
