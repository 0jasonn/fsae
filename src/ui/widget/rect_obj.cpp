#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/pane.h"
#include "ui/widget/rect_obj.h"

// RectObj constructors at 0x020b7c50 and 0x020b7c80. Bit 0 of the flag byte freezes the bounds.

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

// Clears the rectangle before reading the supplied position and size, in the original access order.
RectObj *RectObj_initWithPos(RectObj *self, const s16 *pos, const s16 *size) {
    volatile RectObj *target;
    volatile const s16 *position;
    volatile const s16 *dimensions;

    target = self;
    position = pos;
    dimensions = size;
    target->vtable = data_02126d08;
    target->offsetX = 0;
    target->offsetY = 0;
    target->sizeX = 0;
    target->sizeY = 0;
    target->boundX = 0;
    target->boundY = 0;
    target->flags = 0;
    target->offsetX = position[0];
    target->offsetY = position[1];
    target->sizeX = dimensions[0];
    target->sizeY = dimensions[1];
    return self;
}
