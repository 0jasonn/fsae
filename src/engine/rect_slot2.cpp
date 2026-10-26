#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// rect_slot2: function RectSlot2_init (0x020bba00), provisional name.

extern u8 data_02126f38[];

// Record of the list family with the vtable data_02126f38: the two words at +0x20 and +0x24, the bytes at +0x28 and +0x29
typedef struct RectSlot2 {
    void *vtable;      // 0x00
    u8 unk_04[0x1c];
    s32 unk_20;        // 0x20
    s32 unk_24;        // 0x24
    u8 unk_28;         // 0x28
    u8 unk_29;         // 0x29
} RectSlot2;

// RectSlot2_init(self) (0x020bba00, provisional name): RectObjList_init, the vtable data_02126f38, the words -1 at +0x20
// and +0x24 and the bytes at +0x28 and +0x29 cleared. Returns self.
extern "C" void *RectSlot2_init(RectSlot2 *self);
ARM void *RectSlot2_init(RectSlot2 *self) {
    RectObjList_init(self);
    self->vtable = data_02126f38;
    self->unk_20 = -1;
    self->unk_24 = -1;
    self->unk_28 = 0;
    self->unk_29 = 0;
    return self;
}
