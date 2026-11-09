#include "engine/functions.h"
#include "ui/widget/uiobj_init.h"

// Obj_initVtableC (0x020b7218): initialises the 0x108-byte embedded object, installing the vtable of data_02126bb4.

extern u8 data_02126bb4[];

typedef struct ObjC {
    void *vtable;      // 0x00
    u8 unk_04[0x100 - 0x04];
    u16 unk_100;       // 0x100
    u16 unk_102;       // 0x102
    u8 unk_104;        // 0x104
} ObjC;

void *Obj_initVtableC(void *selfv) {
    ObjC *self = (ObjC *)selfv;

    Obj_initVtableB(self);
    self->vtable = data_02126bb4;
    self->unk_102 = 0;
    self->unk_104 = 0;
    return self;
}
