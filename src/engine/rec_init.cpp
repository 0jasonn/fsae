#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// rec_init: function Rec_setName (0x020b7248), matching. data_02126bb4 is the vtable
// of the record, the name is a 0x7f byte string copied to +4, and flags are at +0x102 (halfword) and +0x104 (byte).

extern u8 data_02126bb4[];
extern "C" void Obj_initVtableB(void *self);
extern "C" void STD_CopyLString(void *dst, const void *src, s32 size);

// Rec_setName(self, name) (0x020b7248, provisional name): marks the record at +0x104 and copies up to 0x7f bytes of the
// name to +4
extern "C" s32 Rec_setName(void *self, const void *name);
ARM s32 Rec_setName(void *self, const void *name) {
    *(u8 *)((u8 *)self + 0x104) = 1;
    STD_CopyLString((u8 *)self + 4, name, 0x7f);
    return 1;
}
