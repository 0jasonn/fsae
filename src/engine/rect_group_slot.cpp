#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// rect_group_slot: function RectGroup_setSlot (0x020b9d30), provisional name.

// Group record: the pointer array at +0x14 and the count at +0x24
typedef struct RectGroupSlot {
    u8 unk_00[0x14];
    void **items;      // 0x14
    u8 unk_18[0xc];
    u16 count;         // 0x24
} RectGroupSlot;

// RectGroup_setSlot(self, index, value) (0x020b9d30, provisional name): stores value in the pointer array at
// index + count + 5 (the sum is taken as 16 bits)
extern "C" void RectGroup_setSlot(RectGroupSlot *self, s32 index, void *value);
ARM void RectGroup_setSlot(RectGroupSlot *self, s32 index, void *value) {
    u16 slot;

    slot = self->count + 1;
    slot += 4;
    self->items[index + slot] = value;
}
