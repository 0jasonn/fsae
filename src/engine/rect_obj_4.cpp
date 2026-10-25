#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_obj_f.h"

// rect_obj_4: functions RectObj_setOffset (0x020b7e48), RectObj_setSize (0x020b7e5c), RectObj_setEnabled (0x020b7e70),
// RectObj_updateHitFlag (0x020b7e94), RectObj_calcTopLeft (0x020b7ef8), RectObjLink_init (0x020b7f28),
// RectObjLink_initCopy (0x020b7f50), RectObjLink_setGeometry (0x020b7f78) and RectObjLink_updateAndCall (0x020b7fa0),
// all matching. RectObjLink_callA (0x020b7fec) is parked in scratch/agentF/nonmatching; rect_obj_5.cpp has the rest.
// data_02126d48 is the vtable of the RectObjLink classes.

extern u8 data_02126d48[];

extern "C" void RectObj_init(RectObjF *self);
extern "C" BOOL RectObj_hitTest(RectObjF *self, s16 *pos);
extern "C" void RectObj_calcTopLeft(s16 *out, RectObjF *self);
extern "C" BOOL RectObj_updateBoundsCheck(RectObjF *self, s16 *pos);
extern "C" void func_020bc2d0(void *owner, s32 value, s32 x, s32 y);

// RectObj_setOffset(self, pos) (0x020b7e48, provisional name): the offset is the position
extern "C" void RectObj_setOffset(RectObjF *self, s16 *pos);
ARM void RectObj_setOffset(RectObjF *self, s16 *pos) {
    self->offsetX = pos[0];
    self->offsetY = pos[1];
}

// RectObj_setSize(self, size) (0x020b7e5c, provisional name): stores the size
extern "C" void RectObj_setSize(RectObjF *self, s16 *size);
ARM void RectObj_setSize(RectObjF *self, s16 *size) {
    self->sizeX = size[0];
    self->sizeY = size[1];
}

// RectObj_setEnabled(self, value) (0x020b7e70, provisional name): the frozen bit is set when value is zero
extern "C" void RectObj_setEnabled(RectObjF *self, s32 value);
ARM void RectObj_setEnabled(RectObjF *self, s32 value) {
    ((RectFlagBits *)&self->flags)->frozen = (value == 0);
}

// RectObj_updateHitFlag(self, pos) (0x020b7e94, provisional name): when the bounds are not frozen and bit 1 is clear,
// the hit flag (bit 2) becomes the result of RectObj_hitTest for a copy of pos
extern "C" void RectObj_updateHitFlag(RectObjF *self, s16 *pos);
ARM void RectObj_updateHitFlag(RectObjF *self, s16 *pos) {
    s16 point[2];

    if (((RectFlagBits *)&self->flags)->frozen) {
        return;
    }
    if (((RectFlagBits *)&self->flags)->unk_bit1) {
        return;
    }
    point[0] = pos[0];
    point[1] = pos[1];
    self->flags = (self->flags & ~4) | ((RectObj_hitTest(self, point) & 1) << 2);
}

// RectObj_calcTopLeft(out, self) (0x020b7ef8, provisional name): the top left corner, the bound minus half the size
ARM void RectObj_calcTopLeft(s16 *out, RectObjF *self) {
    s32 sizeY;
    s32 sizeX;
    s32 halfY;
    s32 halfX;
    s32 y;
    s32 x;

    sizeY = self->sizeY;
    sizeX = self->sizeX;
    halfY = sizeY / 2;
    halfX = sizeX / 2;
    y = self->boundY - halfY;
    x = self->boundX - halfX;
    out[0] = x;
    out[1] = y;
}

// RectObjLink_init(self) (0x020b7f28, provisional name): RectObj_init with the vtable data_02126d48 and the field
// at +0x14 set to -1. Returns self.
extern "C" void *RectObjLink_init(RectObjF *self);
ARM void *RectObjLink_init(RectObjF *self) {
    RectObj_init(self);
    self->vtable = data_02126d48;
    self->unk_14 = -1;
    return self;
}

// RectObjLink_initCopy(self) (0x020b7f50, provisional name): the same code as RectObjLink_init (a second copy)
extern "C" void *RectObjLink_initCopy(RectObjF *self);
ARM void *RectObjLink_initCopy(RectObjF *self) {
    RectObj_init(self);
    self->vtable = data_02126d48;
    self->unk_14 = -1;
    return self;
}

// RectObjLink_setGeometry(self, pos, size, value) (0x020b7f78, provisional name): offset from pos, size from size and
// the field at +0x14 from value
extern "C" void RectObjLink_setGeometry(RectObjF *self, s16 *pos, s16 *size, s32 value);
ARM void RectObjLink_setGeometry(RectObjF *self, s16 *pos, s16 *size, s32 value) {
    self->offsetX = pos[0];
    self->offsetY = pos[1];
    self->sizeX = size[0];
    self->sizeY = size[1];
    self->unk_14 = value;
}

// RectObjLink_updateAndCall(self, owner, pos) (0x020b7fa0, provisional name): when RectObj_updateBoundsCheck is TRUE,
// calls func_020bc2d0 with the owner, the field at +0x14 and the bounds in 8.8 fixed point
extern "C" void RectObjLink_updateAndCall(RectObjF *self, void **owner, s16 *pos);
ARM void RectObjLink_updateAndCall(RectObjF *self, void **owner, s16 *pos) {
    s16 point[2];

    point[0] = pos[0];
    point[1] = pos[1];
    if (RectObj_updateBoundsCheck(self, point) == FALSE) {
        return;
    }
    func_020bc2d0(*owner, self->unk_14, self->boundX << 12, self->boundY << 12);
}
