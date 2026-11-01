#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"
#include "engine/rect_obj.h"

// rect_obj: functions RectObj_init (0x020b7c50), RectObj_noop (0x020b7cd0) and RectObj_updateBounds (0x020b7cd4).
// RectObj_initWithPos (0x020b7c80) is parked in scratch/agentF/nonmatching. data_02126d08 is the vtable of RectObj. Bit 0 of the flag byte at +0x10 freezes the
// bounds (RectObj_updateBounds does nothing while it is set).

extern u8 data_02126d08[];

// RectObj_noop(self) (0x020b7cd0, provisional name): does nothing
extern "C" void RectObj_noop(RectObj *self);
void RectObj_noop(RectObj *self) {
}

// RectObj_updateBounds(self, pos) (0x020b7cd4, provisional name): unless the flag bit 0 is set, the bounds are the position
// plus the offset
extern "C" void RectObj_updateBounds(RectObj *self, void *unused, const s16 *pos);
void RectObj_updateBounds(RectObj *self, void *unused, const s16 *pos) {
    if (((RectFlagBits *)&self->flags)->frozen) {
        return;
    }
    self->boundY = pos[1] + self->offsetY;
    self->boundX = pos[0] + self->offsetX;
}
