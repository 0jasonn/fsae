#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// packed_set: functions Packed_noop (0x020b70fc), Obj_initVtableB (0x020b7100), Packed_setU32BE (0x020b7110) and
// Packed_setS16 (0x020b713c), all matching. data_02126b88 is the vtable that Obj_initVtableB stores.

extern u8 data_02126b88[];

// Packed_noop(self) (0x020b70fc, provisional name): does nothing
extern "C" void Packed_noop(void *self);
ARM void Packed_noop(void *self) {
}

// Obj_initVtableB(self) (0x020b7100, provisional name): stores the vtable data_02126b88 in the first word
extern "C" void Obj_initVtableB(void *self);
ARM void Obj_initVtableB(void *self) {
    *(void **)self = data_02126b88;
}

// Packed_setU32BE(self, value) (0x020b7110, provisional name): writes the four bytes of value from the top and a zero byte
extern "C" void Packed_setU32BE(void *self, u32 value);
ARM void Packed_setU32BE(void *self, u32 value) {
    u8 *bytes;

    bytes = (u8 *)self;
    bytes[0] = value >> 24;
    bytes[1] = value >> 16;
    bytes[2] = value >> 8;
    bytes[3] = value;
    bytes[4] = 0;
}

// Packed_setS16(self, value) (0x020b713c, provisional name): writes the high byte of the signed value, its low byte and a zero byte
extern "C" void Packed_setS16(void *self, s32 value);
ARM void Packed_setS16(void *self, s32 value) {
    u8 *bytes;

    bytes = (u8 *)self;
    bytes[0] = value >> 8;
    bytes[1] = value;
    bytes[2] = 0;
}
