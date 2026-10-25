#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_obj_f.h"

// rect_obj_3: functions RectObj_isOnScreen (0x020b7d08) and RectObj_updateBoundsCheck (0x020b7d74), both matching.
// They follow RectObj_updateBounds (rect_obj_2.cpp). RectObj_calcTopLeft (0x020b7ef8) is in rect_obj_4.cpp.
// RectObj_hitTest (0x020b7db4) is parked in scratch/agentF/nonmatching.

extern "C" void RectObj_calcTopLeft(s16 *out, RectObjF *self);

// RectObj_isOnScreen(self) (0x020b7d08, provisional name): the top left corner is left of 0x100 and above 0xc0, and the
// rectangle extends past the top left corner (its far corner is positive)
extern "C" BOOL RectObj_isOnScreen(RectObjF *self);
ARM BOOL RectObj_isOnScreen(RectObjF *self) {
    BOOL inX;
    BOOL inside;
    s32 x;
    BOOL result;
    s16 topLeft[2];

    RectObj_calcTopLeft(topLeft, self);
    x = topLeft[0];
    result = 0;
    inside = 0;
    inX = 0;
    if (x < 0x100 && topLeft[1] < 0xc0) {
        inside = 1;
    }
    if (inside != 0) {
        if (x + self->sizeX > 0) {
            inX = 1;
        }
    }
    if (inX != 0) {
        if (topLeft[1] + self->sizeY > 0) {
            result = 1;
        }
    }
    return result;
}

// RectObj_updateBoundsCheck(self, pos) (0x020b7d74, provisional name): RectObj_updateBounds, then returns whether the
// rectangle is on the screen (nothing is done and FALSE returned while the bounds are frozen)
extern "C" BOOL RectObj_updateBoundsCheck(RectObjF *self, const s16 *pos);
ARM BOOL RectObj_updateBoundsCheck(RectObjF *self, const s16 *pos) {
    if (((RectFlagBits *)&self->flags)->frozen) {
        return FALSE;
    }
    self->boundY = pos[1] + self->offsetY;
    self->boundX = pos[0] + self->offsetX;
    return RectObj_isOnScreen(self);
}
