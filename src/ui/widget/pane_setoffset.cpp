#include "engine/functions.h"
#include "ui/widget/pane_setoffset.h"

// Pane_setOffset (0x020b57c8): moves the offset of the children to the position plus delta. Called through slot 2 of
// the pane vtable; ctx is unused here.
void Pane_setOffset(void *selfv, s32 ctx, s16 *delta) {
    Pane *self = (Pane *)selfv;
    s16 dx;
    s16 dy;

    self->ofsX = self->posX;
    self->ofsY = self->posY;
    dx = delta[0];
    dy = delta[1];
    self->ofsX = self->posX + dx;
    self->ofsY = self->posY + dy;
}
