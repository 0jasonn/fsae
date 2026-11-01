#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"
#include "engine/rect_obj.h"

// rect_obj: functions RectObj_init (0x020b7c50), RectObj_noop (0x020b7cd0) and RectObj_updateBounds (0x020b7cd4).
// RectObj_initWithPos (0x020b7c80) is parked in scratch/agentF/nonmatching. data_02126d08 is the vtable of RectObj. Bit 0 of the flag byte at +0x10 freezes the
// bounds (RectObj_updateBounds does nothing while it is set).

extern u8 data_02126d08[];

// RectObj_init(self) (0x020b7c50, provisional name): sets the vtable and clears the record
extern "C" void RectObj_init(RectObj *self);
void RectObj_init(RectObj *self) {
    self->vtable = data_02126d08;
    self->offsetX = 0;
    self->offsetY = 0;
    self->sizeX = 0;
    self->sizeY = 0;
    self->boundX = 0;
    self->boundY = 0;
    self->flags = 0;
}

// RectObj_initWithPos: parked (see scratch/agentF/nonmatching/func_020b7c80.cpp)
