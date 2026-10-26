#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// rect_slot3: functions RectSlot2_setFlag (0x020bbb70), RectSlot3_init (0x020bbb78) and RectSlot3_setGeometry
// (0x020bbba0), provisional names.

extern u8 data_02126f60[];

// Record of the list family with the vtable data_02126f60: the word at +0x20 and the flag byte at +0x28
typedef struct RectSlot3 {
    void *vtable;      // 0x00
    u8 unk_04[0x1c];
    s32 unk_20;        // 0x20
    u8 unk_24[4];
    s32 unk_28;        // 0x28 (byte access in RectSlot2_setFlag)
    s32 unk_2c;
    s32 unk_30;
    s32 unk_34;
} RectSlot3;

// RectSlot2_setFlag(self, flag) (0x020bbb70, provisional name): stores the flag byte at +0x28
extern "C" void RectSlot2_setFlag(void *self, s32 flag);
ARM void RectSlot2_setFlag(void *self, s32 flag) {
    ((u8 *)self)[0x28] = (u8)flag;
}

// RectSlot3_init(self) (0x020bbb78, provisional name): RectObjLink_init, the vtable data_02126f60 and the word at +0x20
// cleared. Returns self.
extern "C" void *RectSlot3_init(RectSlot3 *self);
ARM void *RectSlot3_init(RectSlot3 *self) {
    RectObjLink_init(self);
    self->vtable = data_02126f60;
    self->unk_20 = 0;
    return self;
}

// RectSlot3_setGeometry(self, owner, value) (0x020bbba0, provisional name): sets the geometry of self through
// RectObjLink_setGeometry with the position (0x80, 9), the size (0x100, 0x12) and the value of func_020bc200 (owner, 0,
// value); stores value at +0x1c
extern "C" void RectSlot3_setGeometry(RectSlot3 *self, void *owner, s32 value);
ARM void RectSlot3_setGeometry(RectSlot3 *self, void *owner, s32 value) {
    s16 pos[2];
    s16 size[2];
    s32 geomValue;

    size[0] = 0x100;
    size[1] = 0x12;
    pos[0] = 0x80;
    pos[1] = 9;
    geomValue = func_020bc200(owner, 0, value);
    RectObjLink_setGeometry(self, pos, size, geomValue);
    ((s32 *)self)[0x1c / 4] = value;
}
