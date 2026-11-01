#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_links.h"

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
// with flag set, calls func_020b9774 (item, 0) on both items and clears their state bytes, and otherwise sets both
// state bytes and calls func_020b9774 (item, 1) on both items
extern "C" void RectFlagPair_setFlag(RectFlagPair *self, u8 flag);
ARM void RectFlagPair_setFlag(RectFlagPair *self, u8 flag) {
    self->flag = flag;
    self->record[0x29] = flag;
    if (self->flag) {
        func_020b9774(self->itemA, 0);
        self->itemA->state = 0;
        func_020b9774(self->itemB, 0);
        self->itemB->state = 0;
    } else {
        self->itemA->state = 1;
        func_020b9774(self->itemA, 1);
        self->itemB->state = 1;
        func_020b9774(self->itemB, 1);
    }
}
