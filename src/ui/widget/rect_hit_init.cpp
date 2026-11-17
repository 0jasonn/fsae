#include "engine/functions.h"
#include "ui/widget/rect_f.h"

extern u8 data_02126e08[];

// Initializes a RectObjLink2-derived object with extra hit-testing state.
void *RectHitObj_init(void *self) {
    RectObjLink2_init(self);
    *(void **)self = data_02126e08;
    *(s16 *)((u8 *)self + 0x1a) = -1;
    *(s16 *)((u8 *)self + 0x1c) = 0;
    *(s16 *)((u8 *)self + 0x1e) = 0;
    *(s16 *)((u8 *)self + 0x20) = 0;
    return self;
}
