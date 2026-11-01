#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/rect_links.h"
#include "ui/widget/rect_group.h"

// rect_group_update: function RectGroup_updateItems (0x020b9688), provisional name.

// Calls through slot n of the vtable of an object (slot 0 is at +0), with a 32-bit argument
typedef void (*RectGroupSlotFn)(void *self, s32 arg);
#define RECT_GROUP_SLOT(obj, n) (((RectGroupSlotFn *)(*(void **)(obj)))[n])

// Item of a group: the flag byte at +0x10 (bit 1 is set by the second loop)
typedef struct RectGroupItem {
    u8 unk_00[0x10];   // 0x00
    u8 flags;          // 0x10
} RectGroupItem;

// RectGroup_updateItems(self) (0x020b9688, provisional name): calls slot 4 of the first two items with the flag (count
// >= 2), then calls slot 4 of the items 2 and 3 with the same flag and sets bit 1 of their flags
extern "C" void RectGroup_updateItems(RectGroup *self);
void RectGroup_updateItems(RectGroup *self) {
    s32 flag;
    u16 i;

    i = 0;
    flag = self->count >= 2;
    for (; i < 2; i++) {
        RECT_GROUP_SLOT(self->items[i], 4)(self->items[i], flag);
    }
    for (i = 0; i < 2; i++) {
        RECT_GROUP_SLOT(self->items[i + 2], 4)(self->items[i + 2], flag);
        ((RectGroupItem *)self->items[i + 2])->flags |= 2;
    }
}
