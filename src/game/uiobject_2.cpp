#include "engine/functions.h"
#include "global.h"
#include "game/uiobject.h"

// Functions in this file (original names from the debug build):
//   UIObject::getDurationRatio (0x020acd74)

// UIObject::getDurationRatio (0x020acd74): progress of the move as 0..0x1000, or 0x1000 when no move is running
ARM s32 UIObject_getDurationRatio(const UIObject *self) {
    if (self->durationFP == 0) {
        return 0x1000;
    }
    return _s32_div_f(self->elapsed, self->durationFP >> 12);
}
