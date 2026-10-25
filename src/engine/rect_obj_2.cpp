#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// rect_obj: functions RectObj_init (0x020b7c50), RectObj_noop (0x020b7cd0) and RectObj_updateBounds (0x020b7cd4).
// RectObj_initWithPos (0x020b7c80) is parked in scratch/agentF/nonmatching. data_02126d08 is the vtable of RectObj. Bit 0 of the flag byte at +0x10 freezes the
// bounds (RectObj_updateBounds does nothing while it is set).

extern u8 data_02126d08[];

// The flag byte as bits: bit 0 freezes the bounds
typedef struct RectFlagBits {
    u8 frozen : 1;
    u8 rest : 7;
} RectFlagBits;

// RectObj record: offsets at +4 and +6 (the position), the size at +8 and +0xa, the bounds at +0xc and +0xe
typedef struct RectObj {
    void *vtable;      // 0x00
    s16 offsetX;       // 0x04
    s16 offsetY;       // 0x06
    s16 sizeX;         // 0x08
    s16 sizeY;         // 0x0a
    s16 boundX;        // 0x0c
    s16 boundY;        // 0x0e
    u8 flags;          // 0x10
} RectObj;

// RectObj_noop(self) (0x020b7cd0, provisional name): does nothing
extern "C" void RectObj_noop(RectObj *self);
ARM void RectObj_noop(RectObj *self) {
}

// RectObj_updateBounds(self, pos) (0x020b7cd4, provisional name): unless the flag bit 0 is set, the bounds are the position
// plus the offset
extern "C" void RectObj_updateBounds(RectObj *self, void *unused, const s16 *pos);
ARM void RectObj_updateBounds(RectObj *self, void *unused, const s16 *pos) {
    if (((RectFlagBits *)&self->flags)->frozen) {
        return;
    }
    self->boundY = pos[1] + self->offsetY;
    self->boundX = pos[0] + self->offsetX;
}
