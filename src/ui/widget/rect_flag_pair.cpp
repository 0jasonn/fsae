#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/rect_links.h"

// TODO(headers): declared in ui/widget/slider.h, which this file cannot include (its types clash with the
// ones used here); see the header restructure report.
extern "C" void SliderRing_setSelectedChild(void *self, s32 selected);
// rect_flag_pair: function RectFlagPair_setFlag (0x020bb980), provisional name.

// Pair of items at +0x5c and +0x60 (each with a flag byte at +0x3c), and a record at +0x64 (flag byte at +0x29)
typedef struct RectFlagItem {
    u8 unk_00[0x3c];   // 0x00
    u8 state;          // 0x3c
} RectFlagItem;

typedef struct RectFlagPair {
    u8 unk_00[0x5c];   // 0x00
    RectFlagItem *itemA; // 0x5c
    RectFlagItem *itemB; // 0x60
    u8 *record;        // 0x64
    u8 unk_68[0x44];   // 0x68
    u8 flag;           // 0xac
} RectFlagPair;

// RectFlagPair_setFlag(self, flag) (0x020bb980, provisional name): stores flag in self and in the record at +0x64, then
// with flag set, clears both items' selected-row flags and state bytes, and otherwise sets them.
extern "C" void RectFlagPair_setFlag(RectFlagPair *self, u8 flag);
void RectFlagPair_setFlag(RectFlagPair *self, u8 flag) {
    self->flag = flag;
    self->record[0x29] = flag;
    if (self->flag) {
        SliderRing_setSelectedChild(self->itemA, 0);
        self->itemA->state = 0;
        SliderRing_setSelectedChild(self->itemB, 0);
        self->itemB->state = 0;
    } else {
        self->itemA->state = 1;
        SliderRing_setSelectedChild(self->itemA, 1);
        self->itemB->state = 1;
        SliderRing_setSelectedChild(self->itemB, 1);
    }
}
