#include "ui/widget/uiobject.h"

// The interpolation functions return the two coordinates by value (see their matching definitions in uiobject_3.cpp).
BOOL UIObject_updateMovePos(UIObject *self, s32 step) {
    BOOL finished;
    s32 ratio;

    finished = UIObject_updateTime(self, step);
    ratio = UIObject_getDurationRatio(self);
    UIPos2 result = self->calcFunc(&self->fromX, &self->toX, ratio);
    self->pos = result;
    return finished;
}
