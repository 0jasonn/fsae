#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_obj_f.h"

// rect_obj_5: functions RectObjLink_callB (0x020b8004), RectObjLink2_init (0x020b8020) and RectObjLink2_initCopy
// (0x020b804c), all matching. RectObjLink_callA (0x020b7fec) is parked in scratch/agentF/nonmatching.
// data_02126d84 is the vtable of RectObjLink2.

extern u8 data_02126d84[];

extern "C" void RectObj_init(RectObjF *self);
extern "C" void Table_setValueA(void *arg, s32 value, s32 scale);

// RectObjLink_callB(self, arg) (0x020b8004, provisional name): Table_setValueA(arg, field at +0x14, 0x1000)
extern "C" void RectObjLink_callB(RectObjF *self, void *arg);
ARM void RectObjLink_callB(RectObjF *self, void *arg) {
    Table_setValueA(arg, self->unk_14, 0x1000);
}

// RectObjLink2_init(self) (0x020b8020, provisional name): RectObj_init with the vtable data_02126d84, the field at +0x14
// and the halfword at +0x18 cleared. Returns self.
extern "C" void *RectObjLink2_init(RectObjF *self);
ARM void *RectObjLink2_init(RectObjF *self) {
    RectObj_init(self);
    self->vtable = data_02126d84;
    self->unk_14 = 0;
    self->unk_18 = 0;
    return self;
}

// RectObjLink2_initCopy(self) (0x020b804c, provisional name): the same code as RectObjLink2_init (a second copy)
extern "C" void *RectObjLink2_initCopy(RectObjF *self);
ARM void *RectObjLink2_initCopy(RectObjF *self) {
    RectObj_init(self);
    self->vtable = data_02126d84;
    self->unk_14 = 0;
    self->unk_18 = 0;
    return self;
}
